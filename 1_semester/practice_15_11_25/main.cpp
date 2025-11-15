#include <cstddef>
#include <iostream>
#include <iterator>

void sum(size_t n, size_t m, int *c, const int *a, const int *b)
{
  for (size_t i = 0; i < n * m; i++)
  {
    c[i] = a[i] + b[i];
  }
}

int *sum(size_t n, size_t m, const int *a, const int *b)
{
  int *c = new int[n * m];
  sum(n, m, c, a, b);
  return c;
}

void add(size_t n, size_t m, int *a, const int *b)
{
  sum(n, m, a, a, b);
}

void mul(int *c, const int *a, size_t n1, size_t m1, const int *b, size_t n2, size_t m2)
{
  for (size_t i = 0; i < n1; i++)
  {
    for (size_t j = 0; j < m2; j++)
    {
      int sum = 0;
      const int *colB = b + j;
      const int *rowA = a + i * m1;
      for (size_t k = 0; k < n1; k++)
      {
        sum += rowA[k] * colB[k * m2];
      }
      int *rowC = c + i * m2;
      rowC[j] = sum;
    }
  }
}

int *mul(const int *a, size_t n1, size_t m1, const int *b, size_t m2)
{
  int *c = new int[n1 * m2];
  mul(c, a, n1, m1, b, n1, m2);
  return c;
}

void print_matrix(size_t n, size_t m, const int *a)
{
  for (size_t i = 0; i < n; i++)
  {
    for (size_t j = 0; j < m; j++)
    {
      std::cout << a[i * m + j] << " ";
    }
    std::cout << "\n";
  }
}

void mul_sum(size_t n, int *c, const int *a, const int *const *b, size_t s)
{
  if (s > 1)
  {
    int *temp_sum = sum(n, n, b[0], b[1]);
    for (size_t i = 2; i < s; i++)
    {
      sum(n, n, temp_sum, temp_sum, b[i]);
    }
    mul(c, a, n, n, temp_sum, n, n);
    delete[] temp_sum;
  }
  else
  {
    mul(c, a, n, n, b[0], n, n);
  }
}

int *mul_sum(size_t n, const int *a, const int *const *b, size_t s)
{
  int *c = new int[n * n];
  mul_sum(n, c, a, b, s);
  return c;
}

void mul_mul(size_t n, int *c, const int *a, const int *const *b, size_t s)
{
  mul(c, a, n, n, b[0], n, n);
  print_matrix(n, n, c);
  std::cout << "\n";
  int *temp_mul = new int[n * n];
  for (size_t i = 1; i < s; i++)
  {
    mul(temp_mul, c, n, n, a, n, n);

    mul(c, temp_mul, n, n, b[i], n, n);
  }
  delete[] temp_mul;
}

void sum_mul(size_t n, int *c, const int *a, const int *const *b, size_t s)
{
  mul(c, a, n, n, b[0], n, n);
  int *temp_mul = new int[n * n];
  for (size_t i = 1; i < s; i++)
  {
    mul(temp_mul, a, n, n, b[i], n, n);
    sum(n, n, c, c, temp_mul);
  }
  delete[] temp_mul;
}

void sum_sum(size_t n, int *c, const int *a, const int *const *b, size_t s)
{
  sum(n, n, c, a, b[0]);
  for (size_t i = 1; i < s; i++)
  {
    sum(n, n, c, c, a);
    sum(n, n, c, c, b[i]);
  }
}

int main()
{
  int a[4] = {1, 2, 3, 4};
  int b[4] = {1, 1, 1, 1};
  int c[4] = {};

  int b1[4] = {1, 1, 1, 1};
  int b2[4] = {2, 2, 2, 2};
  int b3[4] = {3, 3, 3, 3};

  mul(c, a, 2, 2, b, 2, 2);

  print_matrix(2, 2, c);
  std::cout << "\n";
  print_matrix(2, 2, mul(a, 2, 2, b, 2));
  std::cout << "\n";

  int **b_arr = new int *[3];
  b_arr[0] = b1;
  b_arr[1] = b2;
  b_arr[2] = b3;

  // mul_sum(2, c, a, b_arr, 3);
  // print_matrix(2, 2, c);

  // print_matrix(2, 2, mul_sum(2, a, b_arr, 3));

  sum_mul(2, c, a, b_arr, 3);
  print_matrix(2, 2, c);

  sum_sum(2, c, a, b_arr, 3);
  print_matrix(2, 2, c);

  // mul_mul(2, c, a, b_arr, 3);
  // print_matrix(2, 2, c);
  //  sum(2, 2, c, a, b);

  // print_matrix(2, 2, c);

  // int *c2 = nullptr;
  // c2 = sum(2, 2, a, c);

  // print_matrix(2, 2, c2);

  // add(2, 2, c, a);

  // print_matrix(2, 2, c);
}
