#ifndef FOO_HPP
#define FOO_HPP

template <class T> struct A
{
  T val_;
  T get()
  {
    return val_;
  };
  void set(T val)
  {
    val_ = val;
  };
};
void foo();

#endif
