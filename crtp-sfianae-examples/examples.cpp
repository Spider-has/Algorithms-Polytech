#include <iostream>

class Base
{
public:
  void baseMethod() const
  {
    std::cout << "base\n";
  }
};

class Child : public Base
{
public:
  void childMethod() const
  {
    std::cout << "child " << a << "\n";
  }

private:
  int a = 5;
};

int main()
{
  Child ch;
  ch.baseMethod();
  ch.childMethod();

  Base *basePtr = &ch;

  Child *childPtr = static_cast< Child * >(basePtr);
  childPtr->childMethod();

  Base base2;
  Child *ch3 = static_cast< Child * >(&base2);
  ch3->childMethod();
}
