#include <iostream>

#include "foo.hpp"

extern template class A<int>;

int main()
{
  A<int> b;
  b.set(10);
  std::cout << b.get() << "\n";
  foo();
}
