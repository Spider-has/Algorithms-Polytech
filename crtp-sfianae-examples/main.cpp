

#include <iostream>

template < class Child > class Base
{
public:
  void doSmth() const
  {
    static_cast< const Child * >(this)->impl();
  }
};

class Child_A : public Base< Child_A >
{
public:
  void impl() const
  {
    std::cout << "Child_A\n";
    Base< Child_A >::doSmth();
  }
};

class Child_B : public Base< Child_B >
{
public:
  void impl() const
  {
    std::cout << "Child_B\n";
  }
};

class K
{
public:
  void smth();
};

class B : public K
{
public:
  void impl()
  {
    std::cout << "class B\n";
  }
};

void K::smth()
{
  static_cast< B * >(this)->impl();
}

int main()
{
  Child_A a;
  Child_B b;
  a.doSmth();
  b.doSmth();

  int c = 5;
}
