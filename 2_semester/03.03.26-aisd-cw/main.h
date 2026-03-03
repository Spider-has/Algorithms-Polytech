#ifndef MAIN_H
#define MAIN_H

#include <iostream>

template < class T > struct List
{
  T val;
  List< T > *next;
};

template < class T > struct Vec
{
  T *data;
  size_t s;
};

template < class T > void clear(List< Vec< T > > *h)
{
  while (h)
  {
    if (h->val.s)
    {
      delete[] h->val.data;
    }
    List< Vec< T > > *n = h->next;
    delete h;
    h = n;
  }
}

template < class T > Vec< T > copy(const Vec< T > vec)
{
  Vec< T > new_vec{nullptr, vec.s};

  if (new_vec.s)
  {
    T *arr = new T[new_vec.s];
    new_vec.data = arr;
  }
  try
  {
    for (size_t i = 0; i < new_vec.s; ++i)
    {
      new_vec.data[i] = vec.data[i];
    }
  }
  catch (...)
  {
    delete[] new_vec.data;
    throw;
  }
  return new_vec;
}

template < class T > List< Vec< T > > *copy(const List< Vec< T > > *h)
{
  List< Vec< T > > *new_h = nullptr;
  List< Vec< T > > *new_tail = nullptr;
  try
  {
    while (h)
    {
      List< Vec< T > > *item = new List< Vec< T > >{copy< T >(h->val), nullptr};
      if (!new_h)
      {
        new_h = item;
        new_tail = new_h;
      }
      else
      {
        new_tail->next = item;
        new_tail = item;
      }
      h = h->next;
    }
  }
  catch (...)
  {
    clear(new_h);
    throw;
  }
  return new_h;
}

#endif