#pragma once

#include <utility>

#include "defines.h"

namespace LT3_NAMESPACE { namespace range {

template<class SourceRangeT, class PredicateT>
struct filter_view
{
  using source_range_type = SourceRangeT;
  using source_iterator = decltype(std::declval<SourceRangeT>().begin());
  using source_sentinel = decltype(std::declval<SourceRangeT>().end());
  using predicate_type = PredicateT;

  struct sentinel
  {
    source_sentinel st;

    bool operator!=(sentinel rh) const
    {
      return st != rh.st;
    }
  };

  struct iterator
  {
    source_iterator it;
    filter_view const& view;

    void operator++()
    {
      it++;

      while (it != view.source_range.end() && !view.predicate(*it))
        it++;
    }

    auto operator*() const
    {
      return *it;
    }

    auto operator!=(sentinel rh) const
    {
      return it != rh.st;
    }
  };

  source_range_type& source_range;
  const predicate_type predicate;

  auto begin() const
  {
    auto it = source_range.begin();
    while (it != source_range.end() && !predicate(*it))
      it++;

    return iterator{ it, *this };
  }

  auto end() const
  {
    return sentinel{ source_range.end() };
  }
};

template<class PredicateT>
struct filter_piper
{
  using predicate_type = PredicateT;

  predicate_type const& predicate;

  template<class SourceRangeT>
  friend auto operator|(SourceRangeT& source_range, filter_piper piper)
  {
    return filter_view<SourceRangeT, PredicateT>{
      source_range,
      piper.predicate
    };
  }
};

template<class PredicateT>
constexpr auto filter(PredicateT const& predicate)
{
  return filter_piper<PredicateT>{ predicate };
}

}}
