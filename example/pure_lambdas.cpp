#include "lt3/range/test_range.h"
#include "lt3/range/pure_lambdas.h"

using namespace lt3::range;
using namespace lt3::range::pure_lambdas;

int main()
{
  auto is_odd = [] (auto x) { return x%2 == 1; };
  auto range = test_range();
  auto view = range | filter(is_odd);
}
