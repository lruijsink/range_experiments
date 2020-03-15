#pragma once

#include <utility>

#include "defines.h"
#include "range_wrapper.h"

namespace LT3_NAMESPACE { namespace range { namespace with_lambdas {

template<class RangeT, class ViewT>
struct view_adapter
{
  using range_type = RangeT;
  using value_type = typename range_type::value_type;
  using range_iterator = typename range_type::iterator;
  using range_sentinel = typename range_type::sentinel;
  using view_type = ViewT;

  range_type range;
  view_type view;

  struct sentinel
  {
    range_sentinel st;
  };

  struct iterator
  {
    range_iterator it;
    range_type& range;
    view_type& view;

    auto operator*()
    {
      return view.val(range, it);
    }

    auto operator++()
    {
      return view.inc(range, it);
    }

    auto operator!=(sentinel& st)
    {
      return !view.snt(it, st.st);
    }
  };

  auto begin()
  {
    return iterator{ view.begin(range), range, view };
  }

  auto end()
  {
    return sentinel{ range.end() };
  }
};

template<class SourceT, class PredicateT>
struct filter_view
{
  using source_type = SourceT;
  using iterator = typename source_type::iterator;
  using sentinel = typename source_type::sentinel;
  using predicate_type = PredicateT;
  using value_type = typename source_type::value_type;

  predicate_type predicate;

  auto begin(source_type& src)
  {
    auto it = src.begin();
    while (it != src.end() && !predicate(*it))
      it++;
    return it;
  }

  auto inc(source_type& src, iterator& it)
  {
    it++;
    while (it != src.end() && !predicate(*it))
      it++;
    return it;
  }

  auto val(source_type& src, iterator& it)
  {
    return *it;
  }

  auto snt(iterator& it, sentinel& st)
  {
    return it == st;
  }
};

}}}
