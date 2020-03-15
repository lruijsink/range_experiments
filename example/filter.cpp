#include "lt3/range/test_range.h"
#include "lt3/range/filter.h"

int main()
{
  auto is_odd = [] (auto x) { return x%2 == 1; };
  auto range = lt3::range::test_range();
  auto view = range | lt3::range::filter(is_odd);
}
