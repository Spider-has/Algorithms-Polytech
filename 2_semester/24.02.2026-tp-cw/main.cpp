#include <iostream>

template <class T> struct Vec
{
  T *data;
  size_t s;
};

template <class T> struct VecIt
{
  T *data;
  size_t s;
};

template <class T> VecIt<T> begin(Vec<T> vec)
{
  return VecIt<T>{vec.data, vec.s};
}

template <class T> bool hasNext(VecIt<T> it)
{
  return it.s;
}

template <class T> VecIt<T> next(VecIt<T> it)
{
  return VecIt<T>{it.data + 1, it.s - 1};
}

template <class T> T &value(VecIt<T> it)
{
  return *(it.data);
}

template <class T> VecIt<T> end(Vec<T> v)
{
  return VecIt<T>{v.data + v.s, 0};
}

template <class T> struct VecRIt
{
  T *data;
  size_t s, i;
};

template <class T> VecRIt<T> rbegin(Vec<T> v)
{
  return {v.data, v.s, v.s};
}

template <class T> T &value(VecRIt<T> it)
{
  return it.data[it.i - 1];
}

template <class T> bool hasPrev(VecRIt<T> it)
{
  return it.i;
}

template <class T> VecRIt<T> prev(VecRIt<T> it)
{
  return VecRIt<T>{it.data, it.s, it.i - 1};
}

template <class T> struct List
{
  T val;
  List<T> *next;
};

template <class T> struct Vec2
{
  T *data;
  size_t s;
};

template <class T> struct ListOfVecIt
{
  List<Vec<T>> *curr;
  size_t i;
};

template <class T> using l_v = List<Vec2<T>> *;
template <class T> using l_v_it = ListOfVecIt<T>;

template <class T> l_v<T> getNearestNotEmpty(l_v<T> v)
{
  while (v && (!v->val.s))
  {
    v = v->next;
  }
  return v;
}

template <class T> l_v_it<T> begin(l_v<T> v)
{
  return l_v_it<T>{getNearestNotEmpty(v), 0};
}

template <class T> bool hasNext(l_v_it<T> it)
{
  return it.curr;
}

template <class T> l_v_it<T> next(l_v_it<T> it)
{
  if (it.i + 1 < it.curr->val.s)
  {
    return {it.curr, it.i + 1};
  }
  return begin(it.curr->next);
}

template <class T> T &value(l_v_it<T> it)
{
  return it.curr->val.data[it.i];
}

template <class T> void print_all(const char *testName, l_v<T> list)
{
  std::cout << testName << ": [ ";
  auto it = begin(list);
  while (hasNext(it))
  {
    std::cout << value(it) << " ";
    it = next(it);
  }
  std::cout << "]\n";
}

int main()
{
  int d1[] = {1, 2};
  int d2[] = {3, 4, 5};
  int d3[] = {6};

  List<Vec2<int>> node2 = {{d2, 3}, nullptr};
  List<Vec2<int>> node1 = {{d1, 2}, &node2};
  print_all("Normal List", &node1);
}
