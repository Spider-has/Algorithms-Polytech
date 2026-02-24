#include <iostream>
template <class T> struct List
{
  T val;
  List<T> *next;
};

template <class T> struct Vec
{
  T *data;
  size_t s;
};

template <class T> struct ListOfVecIt
{
  List<Vec<T>> *curr;
  size_t i;
};

template <class T> using l_v = List<Vec<T>> *;
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

  List<Vec<int>> e5 = {{nullptr, 0}, nullptr};
  List<Vec<int>> e4 = {{d3, 1}, &e5};
  List<Vec<int>> e3 = {{nullptr, 0}, &e4};
  List<Vec<int>> e2 = {{d1, 2}, &e3};
  List<Vec<int>> e1 = {{nullptr, 0}, &e2};
  print_all("Mixed Empty", &e1);

  l_v<int> emptyList = nullptr;
  print_all("Nullptr List", emptyList);

  // Тест 4: Список из только пустых векторов
  List<Vec<int>> onlyEmpty = {{nullptr, 0}, nullptr};
  print_all("Only Empty Vecs", &onlyEmpty);
}
