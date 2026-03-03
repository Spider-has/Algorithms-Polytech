template <class T> struct List
{
  T val;
  List<T> *next;
};

template <class T> struct Vec
{
  T *val;
  size_t size;
};

template <class T> bool is_equal(List<Vec<T>> *lhs, Vec<List<T> *> rhs);