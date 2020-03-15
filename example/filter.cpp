#include "lt3/range/test_range.h"
#include "lt3/range/filter.h"

int main()
{
  auto range = lt3::range::test_range();
  auto view = range | lt3::range::filter(1);
}
