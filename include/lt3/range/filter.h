#pragma once

#include <utility>

#include "defines.h"

namespace LT3_NAMESPACE { namespace range {

template<class SourceRangeT, class PredicateT>
struct filter_view
{
  using source_range_type = SourceRangeT;
  using source_iterator = typename source_range_type::iterator;
  using predicate_type = PredicateT;

  struct iterator
  {
    source_iterator it;
    filter_view const& view;

    void operator++()
    {
      if (it == view.source_end)
        return;

      it++;

      if (view.predicate(*it))
        return;

      operator++();
    }

    auto operator*() const
    {
      return *it;
    }

    auto operator!=(iterator rh) const
    {
      return it != rh.it;
    }
  };

  source_iterator source_begin;
  source_iterator source_end;
  predicate_type predicate;

  auto begin()
  {
    auto it = source_begin;
    while (it != source_end && !predicate(*it))
      it++;
    return iterator{ it, *this };
  }

  auto end()
  {
    return iterator{ source_end, *this };
  }
};

template<class PredicateT>
struct filter_piper
{
  using predicate_type = PredicateT;

  predicate_type predicate;

  template<class SourceRangeT>
  friend auto operator|(SourceRangeT& source_range, filter_piper& piper)
  {
    return filter_view<SourceRangeT, PredicateT>{
      source_range.begin(),
      source_range.end(),
      piper.predicate
    };
  }
};

template<class PredicateT>
auto filter(PredicateT predicate)
{
  return filter_piper<PredicateT>{ predicate };
}

}}
