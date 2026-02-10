
#include <iostream>

int *insert(const int *a, size_t s, size_t ind, int v)
{
  int *newA = new int[s + 1];
  for (size_t i = 0; i < ind; ++i)
  {
    newA[i] = a[i]; // exception <T>
  }
  newA[ind] = v; // exception  <T>
  for (size_t i = s; i > ind; --i)
  {
    newA[i] = a[i - 1]; // exception  <T>
  }
  return newA;
}

void insert(int **a, size_t s, size_t i, int v)
{
  int *newA = insert(*a, s, i, v); // exception
  delete[] *a;
  *a = newA;
}

void printArray(const int *a, size_t s)
{
  for (size_t i = 0; i < s; ++i)
  {
    if (i)
    {
      std::cout << " ";
    }
    std::cout << a[i];
  }
  std::cout << "\n";
}

int *remove(int *a, size_t s, size_t i)
{
  int torm = std::move(a[i]);
  for (size_t k = i; k < s - 1; ++k)
  {
    a[k] = std::move(a[k + 1]);
  }
  a[s - 1] = std::move(torm);
  return a + s - 1;
}

int *remove(int *a, size_t s, int v)
{
  for (size_t k = 0; k < s; ++k)
  {
    if (a[k] == v)
    {
      remove(a, s--, k--);
    }
  }
  return a + s;
}

int *cut(const int *a, size_t s)
{
  int *t = new int[s];
  for (size_t i = 0; i < s; ++i)
  {
    t[i] = a[i];
  }
  return t;
}

size_t erase(int **a, size_t s, int v)
{
  size_t upd = remove(*a, s, v) - *a;
  int *t = cut(*a, upd);
  delete[] (*a);
  (*a) = t;
  return upd;
}

int *partition(int *a, size_t s, bool (*cond)(int))
{
  size_t boundary = s - 1;
  for (size_t i = 0; i < boundary + 1; ++i)
  {
    if (!cond(a[i]))
    {
      std::swap(a[i], a[boundary]);
      --boundary;
      --i;
    }
  }
  return a + boundary + 1;
}

int *stable_partition(int *a, size_t s, bool (*cond)(int))
{
  size_t old_size = s;
  for (size_t i = 0; i < s; ++i)
  {
    if (!cond(a[i]))
    {
      for (size_t j = i; j < old_size - 1; ++j)
      {
        std::swap(a[j], a[j + 1]);
      }
      --s;
      --i;
    }
  }
  return a + s;
}

bool moreFive(int a)
{
  return a < 11;
}

int main()
{

  int *boundary;
  int B1[17] = {11, 12, 5, 2, 1, 12, 5, -10, 15, 5, 2, 3, 4, 25, 25, 1, 100};
  printArray(B1, 17);
  boundary = partition(B1, 17, moreFive);
  std::cout << boundary - B1 << "\n";
  printArray(B1, 17);

  int B2[17] = {11, 12, 5, 2, 1, 12, 5, -10, 15, 5, 2, 3, 4, 25, 25, 1, 100};
  boundary = stable_partition(B2, 17, moreFive);
  std::cout << boundary - B2 << "\n";
  printArray(B2, 17);
}
