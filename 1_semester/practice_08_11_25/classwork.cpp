#include <iostream>

int *resized_copy(int *arr, size_t oldLen, size_t newLen)
{
  int *resized = new int[newLen];
  for (int i = 0; i < oldLen; i++)
  {
    resized[i] = arr[i];
  }
  return resized;
}

int main()
{
  size_t count = 0;
  size_t i = 0;
  size_t len = 10;
  int *nums = nullptr;
  size_t num;
  try
  {
    nums = new int[len];
    while (std::cin >> num)
    {
      if (i >= len)
      {
        int *resized = resized_copy(nums, len, len + 10);
        delete[] nums;
        nums = resized;
        len += 10;
      }
      nums[i] = num;
      i++;
    }
  }
  catch (...)
  {
    delete[] nums;
    return 2;
  }

  if (std::cin.eof())
  {
    if (i > 0)
      for (size_t k = 0; k < i; k++)
      {
        if (nums[k] % nums[i - 1] == 0)
          count++;
      }
    std::cout << count << "\n";
  }
  else if (std::cin.fail())
  {
    std::cerr << "Input reading error" << "\n";
    delete[] nums;
    return 1;
  }
  delete[] nums;
}
