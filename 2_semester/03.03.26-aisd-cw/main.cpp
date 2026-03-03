#include "main.h"

template < class T > List< T > *next(List< T > *node)
{
  return node->next;
}

template < class T > bool hasNext(List< T > *node)
{
  return node->next != nullptr;
}

template < class T > void move(Vec< List< T > * > to, Vec< Vec< List< T > * > > from)
{
  size_t curr_i = 0;
  for (size_t i = 0; i < from.s; ++i)
  {
    for (size_t j = 0;)
  }
}

template < class T > void clear(List< T > *h)
{
  while (h)
  {
    List< T > *n = h->next;
    delete h;
    h = n;
  }
}

template < class T > void clearVec(Vec< List< T > * > vec)
{
  for (size_t i = 0; i < vec.s; ++i)
  {
    clear(vec.data[i]);
  }
  delete[] vec.data;
}

template < class T > Vec< List< T > * > balanced_copy(Vec< List< T > * > v, size_t k)
{
  size_t count = 0;
  for (size_t i = 0; i < v.s; i++)
  {
    List< T > *item = v.data[i];
    while (item)
    {
      item = item->next;
      count++;
    }
  }

  size_t new_size = count % k ? count / k + 1 : count / k;

  Vec< List< T > * > new_vec = {nullptr, new_size};
  if (new_size)
  {
    new_vec.data = new List< T > *[new_size] {};
  }

  size_t curr_i = 0;
  List< T > *tail = nullptr;
  size_t curr_l_len = 0;
  try
  {
    for (size_t i = 0; i < v.s; i++)
    {
      List< T > *item = v.data[i];
      while (item)
      {
        List< T > *newItem = new List< T >{item->val, nullptr};
        if (!new_vec.data[curr_i])
        {
          new_vec.data[curr_i] = newItem;
          tail = new_vec.data[curr_i];
        }
        else
        {
          tail->next = newItem;
          tail = newItem;
        }
        curr_l_len++;
        if (curr_l_len == k)
        {
          curr_l_len = 0;
          curr_i++;
          tail = nullptr;
        }
        item = item->next;
      }
    }
  }
  catch (...)
  {
    clearVec(new_vec);
    throw;
  }

  return new_vec;
}

template < class T > Vec< List< T > * > balanced_move(Vec< List< T > * > v, size_t k)
{
  size_t count = 0;
  for (size_t i = 0; i < v.s; i++)
  {
    List< T > *item = v.data[i];
    while (item)
    {
      item = item->next;
      count++;
    }
  }
  size_t new_size = count % k ? count / k + 1 : count / k;

  Vec< List< T > * > new_vec = {nullptr, new_size};
  if (new_size)
  {
    new_vec.data = new List< T > *[new_size] {};
  }

  size_t curr_i = 0;
  List< T > *tail = nullptr;
  size_t curr_l_len = 0;

  for (size_t i = 0; i < v.s; i++)
  {
    List< T > *item = v.data[i];
    while (item)
    {
      List< T > *next_node = item->next;

      if (!new_vec.data[curr_i])
      {
        new_vec.data[curr_i] = item;
        tail = new_vec.data[curr_i];
      }
      else
      {
        tail->next = item;
        tail = item;
      }
      tail->next = nullptr;
      curr_l_len++;
      if (curr_l_len == k)
      {
        curr_l_len = 0;
        curr_i++;
        tail = nullptr;
      }
      item = next_node;
    }
  }

  return new_vec;
}