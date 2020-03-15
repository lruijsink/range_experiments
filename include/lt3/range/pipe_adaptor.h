#pragma once

#include "defines.h"

namespace LT3_NAMESPACE { namespace range {

template<class AccepterT>
struct pipe_adaptor
{
  AccepterT accepter;

  template<class RangeT>
  friend auto operator|(RangeT&& range, const pipe_adaptor& adaptor)
  {
    return adaptor.accepter(std::move(range));
  }
};

template<class ViewMakerT>
auto make_adaptor(ViewMakerT view_maker)
{
  return [&] (auto&& ... args)
  {
    auto accepter = [&] (auto&& range)
    {
        return view_maker(
          std::move(range),
          std::move(args)...
        );
    };
    return pipe_adaptor<decltype(accepter)>{ accepter };
  };
}

}}
