#include "lt3/range/with_lambdas.h"
#include "lt3/range/test_range.h"

using namespace lt3::range;
using namespace lt3::range::with_lambdas;

int main()
{
  auto is_odd = [] (auto x) {
    return x%2 == 1;
  };
  auto range = test_range();
  range.range.push_back(1);
  auto wrapper = wrap_range(range);
  auto view = filter_view<decltype(wrapper), decltype(is_odd)>{ is_odd };
  auto adapter = view_adapter<decltype(wrapper), decltype(view)>{ wrapper, view };
  auto begin = adapter.begin();
  auto end = adapter.end();
}
