#pragma once

#include "defines.h"
#include "range_wrapper.h"

namespace LT3_NAMESPACE { namespace range { namespace pure_lambdas { 

template<class InputRangeT, class BeginT, class DerefT, class IncT, class TestSntT>
struct view_maker
{
  using input_range_type = InputRangeT;
  using input_range_iterator = typename input_range_type::iterator;
  using input_range_sentinel = typename input_range_type::sentinel;

  struct sentinel
  {
    input_range_sentinel input_st;
  };

  struct iterator
  {
    input_range_iterator input_it;
    view_maker& maker;

    auto operator*()
    {
      return maker.deref_impl(maker.input_range, input_it);
    }

    auto operator++()
    {
      maker.inc_impl(maker.input_range, input_it);
    }

    auto operator!=(sentinel& st)
    {
      return maker.test_snt_impl(input_it, st.input_st);
    }
  };

  input_range_type input_range;
  BeginT begin_impl;
  DerefT deref_impl;
  IncT inc_impl;
  TestSntT test_snt_impl;

  auto begin()
  {
    return iterator{ begin_impl(input_range), *this };
  }

  auto end()
  {
    return sentinel{ input_range.end() };
  }
};

template<class AccepterT>
struct view_piper
{
  AccepterT accepter;

  template<class InputRangeT>
  friend auto operator|(InputRangeT& input_range, view_piper const& piper)
  {
    return piper.accepter(wrap_range(input_range));
  }
};

auto make_view = [] (auto begin, auto deref, auto inc, auto test_snt)
{
  auto accepter = [&] (auto source) {
    return view_maker
      <
      decltype(source),
      decltype(begin),
      decltype(deref),
      decltype(inc),
      decltype(test_snt)
      >
    {
      source, begin, deref, inc, test_snt
    };
  };
  return view_piper<decltype(accepter)>{ accepter };
};

auto bypass = [] () {
  return make_view(
    [&] (auto& source)           { return source.begin(); },
    [&] (auto& source, auto it)  { return *it; },
    [&] (auto& source, auto& it) { ++it; },
    [&] (auto it,      auto st)  { return it != st; }
  );
};

auto filter = [] (auto predicate)
{
  auto to_next = [&] (auto& source, auto& it) {
    while (it != source.end() && !predicate(*it))
      ++it;
  };

  return make_view(
    [=] (auto& source)           { auto it = source.begin(); to_next(source, it); return it; },
    [=] (auto& source, auto it)  { return *it; },
    [=] (auto& source, auto& it) { to_next(source, ++it); },
    [=] (auto  it,     auto st)  { return it != st; }
  );
};

}}}
