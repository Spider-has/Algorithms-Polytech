#include <iostream>
#include <limits>
#include <new>

int safe_sum(int a, int b)
{
  using lim_int = std::numeric_limits<int>;
  const int max_int = lim_int::max();
  const int min_int = lim_int::min();
  if (a > 0 && b > 0 && a > max_int - b)
  {
    throw std::overflow_error("sum");
  }
  else if (a < 0 && b < 0 && a < min_int - b)
  {
    throw std::underflow_error("sum");
  }
  return a + b;
}

int safe_divide(int a, int b)
{
  using lim_int = std::numeric_limits<int>;
  const int min_int = lim_int::min();
  if (a == min_int && b == -1)
  {
    throw std::overflow_error("divide");
  }
  return a / b;
}

void bubble_sort(int *arr, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    for (size_t j = i; j < size; j++)
    {
      if (arr[i] > arr[j])
      {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
}

int calculate_median(int *arr, size_t n)
{
  bubble_sort(arr, n);
  if (n % 2 == 1)
  {
    return arr[n / 2];
  }
  else
  {
    return safe_divide(safe_sum(arr[n / 2], arr[n / 2 - 1]), 2);
  }
}

int main()
{
  size_t n = 0;
  int *arr = nullptr;
  size_t i = 0;

  if (!(std::cin >> n))
  {
    std::cerr << "Error reading input\n";
    return 1;
  }

  if (!n)
  {
    std::cout << 0 << "\n";
    return 0;
  }

  try
  {
    arr = new int[n];
  }
  catch (std::bad_alloc &e)
  {
    std::cerr << "bad alloc" << "\n";
    return 2;
  }

  int num = 0;
  while (std::cin >> num)
  {
    arr[i] = num;
    i++;
  }

  if (std::cin.eof() && n == i)
  {
    try
    {
      std::cout << calculate_median(arr, n) << "\n";
    }
    catch (std::overflow_error &e)
    {
      std::cerr << "overfow error: " << e.what() << "\n";
      delete[] arr;
      return 3;
    }
    catch (std::underflow_error &e)
    {
      std::cerr << "underflow error: " << e.what() << "\n";
      delete[] arr;
      return 3;
    }
  }
  else if (std::cin.fail())
  {
    std::cerr << "Error reading input" << "\n";
    delete[] arr;
    return 1;
  }

  delete[] arr;
}
