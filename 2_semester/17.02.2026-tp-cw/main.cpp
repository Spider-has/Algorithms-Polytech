#include <iostream>

template <size_t N> struct Factorial
{
  enum
  {
    value = N * Factorial<N - 1>::value
  };
};

template <> struct Factorial<0>
{
  enum
  {
    value = 1
  };
};

template <class T> void Foo(T a);

template <class T, class U> struct A
{
  static U foo(T val);
};

template <size_t N> struct Fibonacci
{
  enum
  {
    value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value
  };
};

template <> struct Fibonacci<0>
{
  enum
  {
    value = 0
  };
};

template <> struct Fibonacci<1>
{
  enum
  {
    value = 1
  };
};

int main()
{
  std::cout << Fibonacci<0>::value << "\n";
  std::cout << Fibonacci<1>::value << "\n";
  std::cout << Fibonacci<2>::value << "\n";
  std::cout << Fibonacci<3>::value << "\n";
  std::cout << Fibonacci<4>::value << "\n";
  std::cout << Fibonacci<5>::value << "\n";
  std::cout << Fibonacci<6>::value << "\n";
}
