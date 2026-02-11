#include <climits>
#include <iostream>
#include <limits>

void reverse(int *a, size_t s)
{
  for (size_t i = 0; i < s / 2; ++i)
  {
    std::swap(a[i], a[s - i - 1]);
  }
}

void copy(int *from, int *to, size_t s)
{
}

int *reverse(const int *a, size_t s)
{
  int *newA = new int[s];
  for (size_t i = 0; i < s; ++i)
  {
    newA[s - i - 1] = a[i];
  }
  return newA;
}

void reverse(const int *a, size_t s, int *b)
{
  for (size_t i = 0; i < s; ++i)
  {
    b[i] = a[s - i - 1];
  }
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

void quad_partition(int *a, size_t s, bool (*c1)(int), bool (*c2)(int), int **pts)
{
  pts[1] = partition(a, s, c1);
  pts[0] = partition(a, pts[1] - a, c2);
  pts[2] = partition(pts[1], a + s - pts[1], c2);
}

int *uniq(int *a, size_t s)
{
  size_t last_uniq = 0;
  for (size_t i = 1; i < s; ++i)
  {
    if (a[last_uniq] != a[i])
    {
      a[++last_uniq] = a[i];
    }
  }
  return a + last_uniq;
}

int *merge(const int *const *a, size_t sa, const size_t *sai, int *c)
{
  size_t *i_arr = new size_t[sa];
  size_t totalSize = 0;
  for (size_t i = 0; i < sa; ++i)
  {
    i_arr[i] = 0;
    totalSize += sai[i];
  }

  for (size_t j = 0; j < totalSize; ++j)
  {
    int min = std::numeric_limits<int>::max();
    size_t minI = 0;
    for (size_t i = 0; i < sa; ++i)
    {
      if (i_arr[i] < sai[i] && min > a[i][i_arr[i]])
      {
        min = a[i][i_arr[i]];
        minI = i;
      }
    }
    i_arr[minI]++;
    c[j] = min;
  }

  delete[] i_arr;
  return c + totalSize;
}

void printArray(int *a, size_t s)
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

bool isEven(int a)
{
  return a % 2 == 0;
}

bool moreThan4(int a)
{
  return a <= 4;
}

int main()
{
  int A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
  int B[] = {1, 2, 3, 4, 5};
  int C[] = {13, 14, 15, 16};
  int *K[] = {A, B, C};
  size_t sizes[] = {13, 5, 4};
  int newC[22] = {};
  int *end = merge(K, 3, sizes, newC);
  printArray(newC, end - newC);
}
