#include <iostream>
#include <limits>
#include <stdexcept>

unsigned safe_multiply(unsigned a, unsigned b) {
  using lim_uns = std::numeric_limits<unsigned>;
  const unsigned max_uns = lim_uns::max();
  if (a > 0 && b > 0 && a > max_uns / b) {
    throw std::overflow_error("multiply");
  }
  return a * b;
}

unsigned safe_add(unsigned a, unsigned b) {
  using lim_uns = std::numeric_limits<unsigned>;
  const unsigned max_uns = lim_uns::max();
  if (a > max_uns - b) {
    throw std::overflow_error("add");
  }
  return a + b;
}

unsigned get_triangle_number(unsigned n) {
  if (n % 2 == 0)
    return safe_multiply(n / 2, safe_add(n, 1));
  else
    return safe_multiply(n, safe_add(n, 1) / 2);
}

int main() {
  unsigned n;
  std::cin >> n;
  try {
    std::cout << get_triangle_number(n) << "\n";
  } catch (std::overflow_error &e) {
    std::cout << "overflow_error: " << e.what() << "\n";
    return 1;
  }
  return 0;
}
