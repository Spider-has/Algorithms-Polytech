#include <iostream>
#include <utility>

template <class T> T *insert(const T *a, size_t s, size_t i, T v)
{
  T *r = new T[s + 1]; // T::T()
  try
  {
    for (size_t k = 0; k < i; ++k)
    {
      r[k] = a[k]; // T::operator(T)
    }
    r[i] = v;
    for (size_t k = i + 1; i < s; ++i)
    {
      r[k] = a[k - 1];
    }
  }
  catch (...)
  {
    delete[] r;
    throw;
  }

  return r;
}

template <class T> T *reverse(const T *a, size_t s)
{
  T *r = new T[s]; // T::T();
  try
  {
    for (size_t i = 0; i < s; ++i)
    {
      r[i] = a[s - i - 1]; // T::operator=(T);
    }
  }
  catch (...)
  {
    delete[] r;
    throw;
  }
  return r;
}

template <class T> void reverse(T *a, size_t s, size_t &z)
{
  z = 0;
  for (size_t i = 0; i < s / 2; ++i)
  {
    std::swap(a[i], a[s - i - 1]); // В общем случае std::swap использовать нельзя
    ++z;
  }
}

// Деконструктор -- Корней

template <class T, class C> T *remove(T *a, size_t s, C cond)
{
  for (size_t i = 0; i < s; ++i)
  {
    if (cond(a[i])) // a[i] == v T::operator==()
    {
      //...
    }
  }
}

template <class T> T *erase(size_t &valid, const T *a, size_t s, const size_t *eids, size_t toerase)
{
  T *arr = nullptr;
  valid = 0;
  try
  {
    arr = new T[s - toerase];
    size_t curr_erase_i = 0;
    for (size_t i = 0; i < s; ++i)
    {
      if (curr_erase_i < toerase && i == eids[curr_erase_i])
      {
        ++curr_erase_i;
      }
      else
      {
        arr[valid] = a[i];
        ++valid;
      }
    }
  }
  catch (...)
  {
  }
  return arr;
}

int main()
{
}
