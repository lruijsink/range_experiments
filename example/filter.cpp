#include "lt3/range.h"
using namespace lt3::range;

template<class ElementT>
struct array_view
{
  using value_type = ElementT;
  using pointer = value_type*;

  pointer ptr_begin;
  pointer ptr_end;

  struct iterator
  {
    pointer ptr;
    void operator++()
    {
      ptr++;
    }

    value_type operator*() const
    {
      return *ptr;
    }

    bool operator!=(iterator rhs) const
    {
      return ptr != rhs.ptr;
    }
  };

  using const_iterator = iterator;

  auto begin() const
  {
    return iterator{ ptr_begin };
  }

  auto end() const
  {
    return iterator{ ptr_end };
  }
};

auto is_big = [] (auto x) { return x > 3; };
int values[] = { 1, 2, 3, 4, 5 };

/*
int f()
{
  auto view = array_view<int>{ values, values + 5 };

  int sum = 0;
  auto end = view.end();
  for (auto it = view.begin(); it != end; ++it)
    if (*it > 3)
        sum += *it;

  return sum;
}

int f()
{
  auto view = array_view<int>{ values, values + 5 }
            | filter(is_big);

  int sum = 0;
  for (auto v : view)
    sum += v;

  return sum;
}

int f()
{
  int sum = 0;
  for (auto it = values; it < values + 5; it++)
    if (*it > 3)
      sum += *it;

  return sum;
}
*/

int main()
{
  auto view = array_view<int>{ values, values + 5 }
            | filter(is_big);

  int sum = 0;
  for (auto v : view)
    sum += v;

  return sum;
}
