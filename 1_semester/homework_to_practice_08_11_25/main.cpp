#include <fstream>
#include <iostream>

size_t readMatrixFromFile(std::ifstream &file, int *matrix, size_t n, size_t m)
{
  size_t total = n * m;
  size_t i = 0;
  while (i < total && file >> matrix[i])
  {
    ++i;
  }
  return i;
}

void printMatrix(const int *arr, size_t n, size_t m)
{
  for (size_t i = 0; i < n; i++)
  {
    for (size_t j = 0; j < m; j++)
    {
      std::cout << arr[i * m + j] << " ";
    }
    std::cout << "\n";
  }
}

void addColumn(int *newA, size_t colPos, int fill, const int *a, size_t n, size_t m)
{
  size_t new_m = m + 1;
  for (size_t i = 0; i < n; i++)
  {
    size_t old_j = 0;
    for (size_t j = 0; j < new_m; j++)
    {
      if (colPos == j)
      {
        newA[i * new_m + colPos] = fill;
      }
      else
      {
        newA[i * new_m + j] = a[i * m + old_j];
        old_j++;
      }
    }
  }
}

void addRow(int *newA, size_t rowPos, int fill, const int *a, size_t n, size_t m)
{
  size_t new_i = n + 1, old_i = 0;
  for (size_t i = 0; i < new_i; i++)
  {
    if (rowPos == i)
    {
      for (size_t j = 0; j < m; j++)
      {
        newA[i * m + j] = fill;
      }
    }
    else
    {
      for (size_t j = 0; j < m; j++)
      {
        newA[i * m + j] = a[old_i * m + j];
      }
      old_i++;
    }
  }
}

void processAddColumn(int *&a, size_t n, size_t &m, size_t arg2, size_t arg3)
{
  int *newA = new int[n * (m + 1)];
  addColumn(newA, arg2, arg3, a, n, m);
  delete[] a;
  a = newA;
  m++;
}

void processAddRow(int *&a, size_t &n, size_t m, size_t arg2, size_t fill)
{
  int *newA = new int[(n + 1) * m];
  addRow(newA, arg2, fill, a, n, m);
  delete[] a;
  a = newA;
  n++;
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Incorrect args count, need only input file\n";
    return 1;
  }

  int *a = nullptr;

  try
  {
    std::ifstream input(argv[1]);
    size_t n = 0, m = 0;

    input >> n >> m;
    a = new int[n * m];
    size_t m_size = readMatrixFromFile(input, a, n, m);

    if ((!input.eof() && input.fail()) || (m_size != n * m))
    {
      std::cerr << "Error while reading matrix data\n";
      delete[] a;
      return 1;
    }

    printMatrix(a, n, m);

    size_t com, arg2, arg3;
    while ((std::cin >> com >> arg2 >> arg3))
    {
      if ((com != 2 && com != 3) || (com == 2 && arg2 > m) || (com == 3 && (arg2 > n || arg3 > m)))
      {
        std::cerr << "Invalid command params\n";
        delete[] a;
        return 3;
      }
      if (com == 2)
      {
        processAddColumn(a, n, m, arg2, arg3);
      }
      if (com == 3)
      {
        processAddRow(a, n, m, arg2, 0);
        processAddColumn(a, n, m, arg3, 0);
      }
      printMatrix(a, n, m);
    }

    delete[] a;
    if (!std::cin.eof() && std::cin.fail())
    {
      std::cerr << "Invalid command input\n";
      return 3;
    }
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Memory allocation failed\n";
    delete[] a;
    return 2;
  }
  catch (...)
  {
    std::cerr << "Unknown error\n";
    delete[] a;
    return 1;
  }
}
