#pragma once

#include <utility>
#include <vector>
#include <iostream>
#include <cassert>

#include "defines.h"

namespace LT3_NAMESPACE {
namespace range {

class test_range
{
  bool constructed;

public:
  test_range()
  {
    constructed = true;
    std::cout << "test_range()\n";
  }

  test_range(const test_range& obj)
  {
    assert(obj.constructed);
    constructed = true;
    std::cout << "test_range(const test_range&)\n";
  }

  test_range(test_range&& obj)
  {
    assert(obj.constructed);
    constructed = true;
    std::cout << "test_range(test_range&&)\n";
  }

  ~test_range()
  {
    assert(constructed);
    constructed = false;
    std::cout << "~test_range()\n";
  }

  test_range& operator=(const test_range& obj)
  {
    assert(obj.constructed);
    std::cout << "test_range.operator=(const_test_range&)\n";
    return *this;
  }

  test_range& operator=(test_range&& obj)
  {
    assert(obj.constructed);
    std::cout << "test_range.operator=(const_test_range&)\n";
    return *this;
  }

  std::vector<int> range;

  auto begin()
  {
    assert(obj.constructed);
    return range.begin();
  }

  auto end()
  {
    assert(obj.constructed);
    return range.end();
  }
};

}}
