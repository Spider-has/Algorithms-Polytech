#include "foo.hpp"

#include <iostream>

template class A<int>;

void foo()
{
  A<int> b;
  b.set(10);
  std::cout << b.get() << "\n";
}
