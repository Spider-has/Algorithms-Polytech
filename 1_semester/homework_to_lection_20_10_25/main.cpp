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

unsigned safe_add_no_exception(unsigned a, unsigned b) {
  using lim_uns = std::numeric_limits<unsigned>;
  const unsigned max_uns = lim_uns::max();
  if (a > max_uns - b) {
    return 0;
  }
  return a + b;
}

unsigned safe_multiply_no_exception(unsigned a, unsigned b) {
  using lim_uns = std::numeric_limits<unsigned>;
  const unsigned max_uns = lim_uns::max();
  if (a > 0 && b > 0 && a > max_uns / b) {
    return 0;
  }
  return a * b;
}

unsigned get_triangle_number_using_exception(unsigned n) {
  if (n % 2 == 0)
    return safe_multiply(n / 2, safe_add(n, 1));
  else
    return safe_multiply(n, safe_add(n, 1) / 2);
}

bool isMultipleOverflowError(unsigned result, unsigned a, unsigned b) {
  return !result && a > 0 && b > 0;
}

bool isAddOverflowError(unsigned result, unsigned a, unsigned b) {
  return !result && (a > 0 || b > 0);
}

bool isTriangleNumberAddOverflow(unsigned result, unsigned n) {
  return !result && n > 0;
}

bool isTriangleNumberMultiplyOverflow(unsigned result, unsigned n) {
  return result == 1 && n > 1;
}

unsigned get_triangle_number_no_exception(unsigned n) {
  unsigned sum = safe_add_no_exception(n, 1);
  if (isAddOverflowError(sum, n, 1)) {
    return 0;
  }
  if (n % 2 == 0) {
    unsigned result = safe_multiply_no_exception(n / 2, sum);
    if (isMultipleOverflowError(result, n / 2, sum)) {
      return 1;
    }
    return result;
  } else {
    unsigned result = safe_multiply_no_exception(n, sum / 2);
    if (isMultipleOverflowError(result, n, sum / 2)) {
      return 1;
    }
    return result;
  }
}

int main() {
  unsigned n;
  std::cin >> n;
  // try {
  //   std::cout << get_triangle_number_using_exeption(n) << "\n";
  // } catch (std::overflow_error &e) {
  //  std::cerr << "overflow_error: " << e.what() << "\n";
  //  return 1;
  //}

  unsigned result = get_triangle_number_no_exception(n);
  if (isTriangleNumberAddOverflow(result, n)) {
    std::cerr << "overflow_error: add" << "\n";
    return 1;
  } else if (isTriangleNumberMultiplyOverflow(result, n)) {
    std::cerr << "overflow_error: multiply" << "\n";
    return 1;
  }

  std::cout << result << "\n";

  return 0;
}
