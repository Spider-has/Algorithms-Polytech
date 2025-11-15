#include <cstddef>
#include <iostream>

void swap(int &a, int &b)
{
  int temp = b;
  b = a;
  a = temp;
}

size_t calc_new_size(size_t n, size_t m)
{
  return 0;
}

size_t min(size_t a, size_t b)
{
  return a < b ? a : b;
}
void print_matrix(const int *a, size_t n, size_t m)
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

void transpose(int *a, int *b, size_t n, size_t m)
{
  size_t col = m;
  for (int i = col - 1; i >= 0; i--)
  {
    for (int j = n - 1; j >= 0; j--)
    {
      int curr = a[j * col + i];
      size_t currI = j * col + i;
      size_t neededI = col * n - (n - j);
      while (currI != neededI)
      {
        swap(a[currI], a[currI + 1]);
        currI++;
      }
    }
    col--;
  }
}

void transpose(int *a, size_t n, size_t m)
{
  size_t newSize = calc_new_size(n, m);
  int *b = new int[newSize];
  transpose(a, b, n, m);
}

int *simple_transpose(const int *a, size_t n, size_t m)
{
  int *newA = new int[n * m];
  for (size_t i = 0; i < n; i++)
  {
    for (size_t j = 0; j < m; j++)
    {
      newA[j * n + i] = a[i * m + j];
    }
  }
  return newA;
}

int main()
{
  int a1[] = {1, 2, 3, 4};
  int a2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  int a3[] = {1, 4, 7, 10, 13, 2, 5, 8, 11, 14, 3, 6, 9, 12, 15};
  int a4[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  int a5[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  int a6[] = {0, 1, 0, 1, 0, 1, 0, 1, 0};
  int a7[] = {1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18,
              19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
  int *a = a7;

  size_t n = 5;
  size_t m = 7;

  print_matrix(a, n, m);
  std::cout << "\n\n";

  int *tA = simple_transpose(a, n, m);
  transpose(a, n, m);

  print_matrix(a, m, n);
  std::cout << "\n\n";
  print_matrix(tA, m, n);
}
