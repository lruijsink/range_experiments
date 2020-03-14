#pragma once

#include "defines.h"

namespace LT3_NAMESPACE { namespace range {

template<class InputRangeT, class PredicateT>
struct filter_view
{
  using input_range_type = InputRangeT;
  using input_range_iterator = typename input_range_type::const_iterator;
  using value_type = typename input_range_type::value_type;
  using predicate_type = PredicateT;

  input_range_type const& input_range;
  predicate_type const& predicate;

  struct iterator
  {
    input_range_iterator input_iterator;
    filter_view const& view;
    void operator++()
    {
      ++input_iterator;
      while (input_iterator != view.input_range.end() && !view.predicate(*input_iterator))
      {
        ++input_iterator;
      }
    }

    value_type operator*() const
    {
      return *input_iterator;
    }

    bool operator!=(iterator const& rhs) const
    {
      return input_iterator != rhs.input_iterator;
    }
  };

  using const_iterator = iterator;

  auto begin()
  {
    return iterator{input_range.begin(), *this};
  }

  auto end()
  {
    return iterator{input_range.end(), *this};
  }
};

template<class PredicateT>
struct filter_coupler
{
  using predicate_type = PredicateT;

  predicate_type predicate;

  template<class InputRangeT>
  friend auto operator|(InputRangeT const& input_range,
                        filter_coupler const& coupler)
  {
    return filter_view<InputRangeT, PredicateT>{input_range, coupler.predicate};
  }
};

template<class PredicateT>
auto filter(PredicateT predicate)
{
  return filter_coupler<PredicateT>{predicate};
}

}}
