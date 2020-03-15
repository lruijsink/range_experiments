#pragma once

#include <utility>

#include "defines.h"

namespace LT3_NAMESPACE { namespace range {

template<class RangeT>
struct range_wrapper
{
  using range_type = std::remove_reference_t<RangeT>;
  using range_store_type = std::conditional_t<
    std::is_rvalue_reference_v<RangeT>,
    range_type,
    range_type&
  >;

  range_store_type range;

  using iterator = decltype(std::declval<range_type>().begin());
  using sentinel = decltype(std::declval<range_type>().end());
  using value_type = decltype(std::declval<iterator>().operator*());

  iterator begin() { return range.begin(); }
  sentinel end() { return range.end(); }
};

template<class RangeT>
auto wrap_range(RangeT&& range)
{
  return range_wrapper<decltype(range)>{ std::forward<RangeT>(range) };
}

}}
