#pragma once

#include <utility>

#include "defines.h"
#include "range_wrapper.h"

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
  };

  struct iterator
  {
    source_iterator it;
    filter_view& view;

    void operator++() noexcept
    {
      it++;

      while (it != view.source_range.end() && !view.predicate(*it))
        it++;
    }

    auto operator*() noexcept
    {
      return *it;
    }

    auto operator!=(sentinel& rh) noexcept
    {
      return it != rh.st;
    }
  };

  source_range_type source_range;
  const predicate_type predicate;

  auto begin() noexcept
  {
    auto it = source_range.begin();
    while (it != source_range.end() && !predicate(*it))
      it++;

    return iterator{ it, *this };
  }

  auto end() noexcept
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
  friend auto operator|(SourceRangeT& source_range, filter_piper piper) noexcept
  {
    return filter_view<decltype(wrap_range(source_range)), PredicateT>{
      wrap_range(source_range),
      piper.predicate
    };
  }
};

template<class PredicateT>
constexpr auto filter(PredicateT const& predicate) noexcept
{
  return filter_piper<PredicateT>{ predicate };
}

}}
