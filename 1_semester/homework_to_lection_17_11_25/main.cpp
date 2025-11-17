#include <cstddef>
#include <iostream>

const int &min(const int &lhs, const int &rhs)
{
  if (lhs < rhs)
  {
    return lhs;
  }
  else
  {
    return rhs;
  }
}

const int *min(const int *a, size_t size)
{
  const int *min_a = a;
  for (size_t i = 1; i < size; i++)
  {
    min_a = &min(*min_a, a[i]);
  }
  return min_a;
}

const int *min(const int *a, size_t n, size_t m)
{
  return min(a, n * m);
}

const int *min(const int *const *a, size_t n, size_t m)
{
  const int *min_a = min(a[0], m);
  for (size_t i = 1; i < n; i++)
  {
    const int *row_min = min(a[i], m);
    min_a = &min(*min_a, *row_min);
  }
  return min_a;
}

const int *min(const int *const *const *a, size_t n, size_t m, size_t k)
{
  const int *min_a = min(a[0], m, k);
  for (size_t i = 1; i < n; i++)
  {
    const int *min_matrix2d = min(a[i], m, k);
    min_a = &min(*min_a, *min_matrix2d);
  }
  return min_a;
}

int main()
{
  std::cout << "=== Тесты для функций min ===\n\n";

  // --- Тест 1: min(const int &, const int &) ---
  std::cout << "1. min(const int &, const int &):\n";
  int a1 = 10, b1 = 5;
  std::cout << "min(" << a1 << ", " << b1 << ") = " << min(a1, b1) << "\n";
  int a2 = -3, b2 = 7;
  std::cout << "min(" << a2 << ", " << b2 << ") = " << min(a2, b2) << "\n\n";

  // --- Тест 2: min(const int *a, size_t size) ---
  std::cout << "2. min(const int *a, size_t size):\n";
  int arr1[] = {3, 1, 4, 1, 5};
  const int *res1 = min(arr1, 5);
  std::cout << "Array: {3, 1, 4, 1, 5} -> min = " << *res1 << "\n\n";

  // --- Тест 3: min(const int *a, size_t n, size_t m) ---
  std::cout << "3. min(const int *a, size_t n, size_t m) (1D как 2D):\n";
  int arr2d_1d[] = {9, 2, 7, 1};
  const int *res2 = min(arr2d_1d, 2, 2); // 2 строки, 2 столбца
  std::cout << "Array (2x2): {9, 2; 7, 1} -> min = " << *res2 << "\n\n";

  // --- Тест 4: min(const int *const *a, size_t n, size_t m) ---
  std::cout << "4. min(const int *const *a, size_t n, size_t m):\n";
  int row1[] = {100, 99, 101};
  int row2[] = {98, 5, 97};
  int row3[] = {96, 95, 1};
  int *matrix2d[] = {row1, row2, row3};
  const int *res3 = min(matrix2d, 3, 3); // 3 строки, 3 столбца
  std::cout << "Matrix (3x3):\n";
  std::cout << "  {100, 99, 101}\n";
  std::cout << "  {98,  5,  97}\n";
  std::cout << "  {96, 95,   1}\n";
  std::cout << "  -> min = " << *res3 << " (ожидается 1)\n\n";

  // --- Тест 5: min(const int *const *const *a, size_t n, size_t m, size_t k) ---
  std::cout << "5. min(const int *const *const *a, size_t n, size_t m, size_t k):\n";
  int plane1_row1[] = {10, 20};
  int plane1_row2[] = {30, 40};
  int plane2_row1[] = {5, 15};
  int plane2_row2[] = {25, 1}; // Минимум 1

  int *plane1[] = {plane1_row1, plane1_row2};
  int *plane2[] = {plane2_row1, plane2_row2};
  int **matrix3d[] = {plane1, plane2};

  const int *res4 = min(matrix3d, 2, 2, 2); // 2 "слоя", 2 строки, 2 столбца
  std::cout << "3D Matrix (2x2x2):\n";
  std::cout << "  Plane 0:\n";
  std::cout << "    {10, 20}\n";
  std::cout << "    {30, 40}\n";
  std::cout << "  Plane 1:\n";
  std::cout << "    {5,  15}\n";
  std::cout << "    {25, 1}\n";
  std::cout << "  -> min = " << *res4 << " (ожидается 1)\n\n";

  std::cout << "4. min(const int *const *a, size_t n, size_t m):\n";
  int row0[] = {100};
  int *matrix2d2[] = {row0};
  const int *res6 = min(matrix2d2, 1, 1); // 3 строки, 3 столбца
  std::cout << "  -> min = " << *res6 << " (ожидается 100)\n\n";

  std::cout << "4. min(const int *const *a, size_t n, size_t m):\n";
  int row00[] = {1};
  int *matrix2d22[] = {row00};
  int **matrix3d2[] = {matrix2d22};
  const int *res7 = min(matrix3d2, 1, 1, 1); // 3 строки, 3 столбца
  std::cout << "  -> min = " << *res7 << " (ожидается 100)\n\n";
  return 0;
}
