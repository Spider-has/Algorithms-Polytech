#include <iostream>
#include <limits>
#include <stdexcept>

unsigned safe_positive_multiply(unsigned a, unsigned b)
{
  using lim_uns = std::numeric_limits<unsigned>;
  const unsigned maxUnsigned = lim_uns::max();
  if (a > 0 && b > 0 && a > maxUnsigned / b)
    throw std::overflow_error("multiply");
  return a * b;
}

unsigned safe_positive_add(unsigned a, unsigned b)
{
  using lim_uns = std::numeric_limits<unsigned>;
  const unsigned maxUnsigned = lim_uns::max();
  if (a > maxUnsigned - b)
    throw std::overflow_error("add");
  return a + b;
}

unsigned gcd(unsigned a, unsigned b)
{
  while (a && b)
  {
    if (a > b)
    {
      a = a % b;
    }
    else
    {
      b = b % a;
    }
  }
  return a + b;
}

unsigned get_abs(int a)
{
  using lim_int = std::numeric_limits<int>;
  const int minInt = lim_int::min();
  if (a == minInt)
  {
    throw std::overflow_error("abs");
  }
  return a >= 0 ? a : -a;
}

unsigned lcm(unsigned a, unsigned b)
{
  if (a == 0 || b == 0)
    return 0;
  return safe_positive_multiply(a / gcd(a, b), b);
}

int main()
{
  int a = 0;

  std::cin >> a;

  unsigned sequence_lcm = 0;
  unsigned sequence_square_sum = 0;
  try
  {
    sequence_lcm = get_abs(a);
    sequence_square_sum = safe_positive_multiply(get_abs(a), get_abs(a));
    while (std::cin >> a)
    {
      sequence_lcm = lcm(sequence_lcm, get_abs(a));
      sequence_square_sum = safe_positive_add(sequence_square_sum, safe_positive_multiply(get_abs(a), get_abs(a)));
    }
  }
  catch (const std::overflow_error &e)
  {
    std::cerr << "Overflow: " << e.what() << "\n";
    return 2;
  }

  if (std::cin.eof())
  {
    std::cout << "lcm: " << sequence_lcm << "\n";
    std::cout << "square sum: " << sequence_square_sum << "\n";
    std::cout << "\n";
  }
  else if (std::cin.fail())
  {
    std::cerr << "Error input reading\n";
    return 1;
  }
}
