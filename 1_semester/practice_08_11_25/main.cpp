#include <iostream>
#include <new>

void rm(int **p, size_t n)
{
  for (size_t i = 0; i < n; ++i)
  {
    delete[] p[i];
  }
  delete[] p;
}

int max(int n1, int n2)
{
  return n1 > n2 ? n1 : n2;
}

int min(int n1, int n2)
{
  return n1 > n2 ? n2 : n1;
}

size_t detSize(size_t n1, size_t m1, size_t n2, size_t m2, size_t i)
{
  return i < min(n1, n2) ? m1 + m2 : n1 > n2 ? m1 : m2;
}

int **ct(size_t n1, size_t m1, size_t n2, size_t m2)
{
  size_t n = max(n1, n2);
  int **c = new int *[n];
  size_t i = 0;
  try
  {
    for (; i < n; i++)
    {
      size_t m = detSize(n1, m1, n2, m2, i);
      c[i] = new int[m];
    }
  }
  catch (...)
  {
    rm(c, i);
    throw;
  }
  return c;
}

int **make_matrix(size_t n, size_t m)
{
  int **mtx = new int *[n];
  size_t i = 0;
  try
  {
    for (; i < n; ++i)
    {
      mtx[i] = new int[m];
    }
  }
  catch (...)
  {
    rm(mtx, i);
    throw;
  }
  return mtx;
}

int *copy(const int *v, size_t k, int *w)
{
  for (size_t i = 0; i < k; i++)
  {
    w[i] = v[i];
  }
  return w + k;
}

int **concat_rows(const int *const *a, size_t n1, size_t m1, const int *const *b, size_t n2, size_t m2)
{
  size_t n = min(n1, n2);
  int **c = make_matrix(n, m1 + m2);
  for (int i = 0; i < n; i++)
  {
    const int *rowa = a[i];
    const int *rowb = b[i];
    int *rowc = c[i];
    rowc = copy(rowa, m1, rowc);
    copy(rowb, m2, rowc);
  }

  return c;
}

int *make_minor(size_t n)
{
  int *minor = new int[n * n];
  return minor;
}

void fill_minor(const int *parent, int *minor, size_t currI, size_t n)
{
  size_t mI = 0;
  for (size_t j = n; j < n * n; j++)
  {
    if (j % n != currI)
    {
      minor[mI] = parent[j];
      mI++;
    }
  }
}

int det(const int *a, size_t n)
{
  if (n == 2)
  {
    return a[0] * a[3] - a[1] * a[2];
  }
  else if (n == 0)
  {
    return 0;
  }
  else if (n == 1)
  {
    return *a;
  }
  int total_det = 0;
  for (size_t i = 0; i < n; i++)
  {
    int current = a[i];
    int *minor = make_minor(n - 1);
    fill_minor(a, minor, i, n);
    try
    {
      if (i % 2)
      {
        total_det -= current * det(minor, n - 1);
      }
      else
      {
        total_det += current * det(minor, n - 1);
      }
      delete[] minor;
    }
    catch (...)
    {
      delete[] minor;
      throw;
    }
  }
  return total_det;
}

int main()
{
  int d[25] = {1, 2, 3, 4, 5, 9, 8, 7, 6, 5, -10, -11, -12, 13, 14, -15, -18, 17, -16, 15, 20, -5, -1, -3, -4};
  int a[9] = {1, 2, 3, 4, 5, 6, 11, 9, 10};
  int b[4] = {5, 0, 7, 9};
  int c[1] = {1};

  try
  {
    std::cout << det(c, 1) << "\n";
    std::cout << det(b, 2) << "\n";
    std::cout << det(a, 3) << "\n";
    std::cout << det(d, 5) << "\n";
  }
  catch (...)
  {
    return 2;
  }
}
