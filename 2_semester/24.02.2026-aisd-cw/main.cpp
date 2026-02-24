#include <iostream>

// template <class T> struct List
// {
//   T val;
//   List<T> *next;
// };

// template <class T> size_t size(const List<T> *h)
// {
//   size_t count = 0;
//   while (h)
//   {
//     count += h->val ? 1 : 0;
//     h = h->next;
//   }
//   return count;
// }

// template <class T> void clear(List<T> *h)
// {
//   while (h)
//   {
//     List<T *> *n = h->next;
//     delete h->val;
//     delete h;
//     h = n;
//   }
// }

// template <class T> size_t size(const List<const List<T> *> *h)
// {
//   size_t count = 0;
//   while (h)
//   {
//     count += size<T>(h->val);
//     h = h->next;
//   }
//   return count;
// }

// template <class T> void clear(const List<const List<T> *> *h)
// {
//   while (h)
//   {
//     clear<T>(h->val);
//     List<List<T> *> *n = h->next;
//     delete h;
//     h = n;
//   }
// }

// template <class T> struct Vec
// {
//   T *data;
//   size_t size;
// };

// template <class T> size_t size(Vec<const List<T> *> v)
// {
//   size_t count = 0;
//   for (size_t i = 0; i < v.size; ++i)
//   {
//     count += size<T>(v.data[i]);
//   }
//   return count;
// }

// template <class T> void clear(Vec<List<T> *> v)
// {
//   for (size_t i = 0; i < v.size; ++i)
//   {
//     clear<T>(v.data[i]);
//   }
//   delete[] v.data;
// }

template <class T> struct List
{
  T val;
  List<T> *next;
};

template <class T> struct Vec
{
  T *data;
  size_t size;
};

// Список указателей на векторы

template <class T> size_t size(const List<Vec<T> *> *h)
{
  size_t count = 0;
  while (h)
  {
    count += h->val ? h->val->size : 0;
    h = h->next;
  }
  return count;
}

template <class T> void clear(List<Vec<T> *> *h)
{
  while (h)
  {
    if (h->val)
    {
      delete[] h->val->data;
      delete h->val;
    }
    const List<Vec<T> *> *n = h->next;
    delete h;
    h = n;
  }
}

int main()
{
  const List<const List<int> *> *l = nullptr;
  size_t count = size(l);
  std::cout << count << "\n";
}
