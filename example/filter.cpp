#include<vector>
#include "lt3/range.h"
using namespace lt3::range;

auto is_big = [] (auto x) { return x > 3; };

int main()
{
  auto vals = std::vector<int>{ 1, 2, 3, 4, 5 };
  auto view = vals | filter(is_big);

  int sum = 0;
  for (auto v : view)
  {
    sum += v;
  }

  return sum;
}
