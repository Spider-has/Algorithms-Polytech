#include <iostream>

template <class T> struct List
{
  T val;
  List<T> *next;
};

template <class T> List<T> *clear(List<T> *head, List<T> *tail) noexcept
{
  while (head != tail)
  {
    // List<T> *copy = head;
    // head = head->next;
    // delete copy;
    List<T> *n = head->next;
    delete head;
    head = n;
  }
  return tail;
}

template <class T> List<T> *convert(const T *data, size_t s, List<T> **tail)
{
  List<T> *h = s ? new List<T>{data[0], nullptr} : nullptr; // T::T(const T&)
  List<T> *t = h;
  try
  {
    for (size_t i = 1; i < s; ++i)
    {
      List<T> *node = new List<T>{data[i], nullptr};
      t->next = node;
      t = node;
    }
  }
  catch (...)
  {
    clear<T>(h, nullptr);
    throw;
  }
  *tail = t;
  return h;
}

template <class T, class C> List<T> *remove_if(List<T> **head, C cond)
{
  List<T> *new_head = nullptr, *tail = *head;
  if (cond(tail->val))
  {
    new_head = tail;
    *head = new_head->next;
    new_head->next = nullptr;
    tail = *head;
    if (cond(tail->val))
    {
      while (tail->next && cond(tail->next->val))
      {
        tail = tail->next;
      }
      new_head->next = *head;
      *head = tail->next;
      tail->next = nullptr;
      tail = *head;
    }
  }
  else
  {
    while (tail->next != nullptr && !cond(tail->next->val))
    {
      tail = tail->next;
    }
    if (!tail->next)
    {
      return nullptr;
    }
    new_head = tail->next;
    tail->next = new_head->next;
    new_head->next = nullptr;
  }
  return new_head;
}

template <class T> class Equal_to
{
  T eq;

public:
  Equal_to(T n):
      eq(n)
  {
  }
  bool operator()(const T &val) const
  {
    return eq == val;
  }
};

template <class T, class C> size_t count(const List<T> *head, C cond)
{
  size_t result = 0;
  while (head)
  {
    result += cond(head->val) ? 1 : 0;
    head = head->next;
  }
  return result;
}

template <class T> using C_L_T = const List<T>;

template <class T, class C> size_t count(C_L_T<T> *h, C cond, List<C_L_T<T> *> **chead, List<C_L_T<T> *> **ctail)
{
  const List<T> *tail = h;
  size_t result = 0;
  while (tail && !cond(tail->val))
  {
    tail = tail->next;
  }
  List<C_L_T<T> *> *new_head = nullptr;
  List<C_L_T<T> *> *new_tail = new_head;
  if (tail)
  {
    new_head = new List<C_L_T<T> *>{tail, nullptr};
    new_tail = new_head;
    result++;
    tail = tail->next;
    try
    {
      while (tail)
      {
        if (cond(tail->val))
        {
          List<C_L_T<T> *> *new_elem = new List<C_L_T<T> *>{tail, nullptr};
          new_tail->next = new_elem;
          new_tail = new_elem;
          result++;
        }
        tail = tail->next;
      }
    }
    catch (...)
    {
      clear(new_head, nullptr);
      throw;
    }
  }
  *chead = new_head;
  *ctail = new_tail;
  return result;
}

int main()
{
  int b[] = {1, 2, 3, 4};
  List<int> *tail = nullptr;
  List<int> *a = convert<int>(b, 4, &tail);
  clear<int>(a, nullptr);

  Equal_to eq(3);
  remove_if(&a, eq);
}
