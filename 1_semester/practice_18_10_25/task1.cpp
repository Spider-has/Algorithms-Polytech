#include <cstddef>
#include <iostream>

size_t multiply(size_t a, size_t b) {
  size_t res = 0;
  while (b != 0) {
    res += a;
    b--;
  }

  return res;
}

size_t old_even_factorial(size_t a) {
  size_t start = 2 - (a % 2);
  size_t res = start;
  while (start < a) {
    start += 2;
    res = multiply(res, start);
  }
  return res;
}

size_t square(size_t a) {
  size_t res = 0;
  size_t start = 1;
  for (size_t i = 0; i < a; i++) {
    res += start;
    start += 2;
  }

  return res;
}

size_t reminder(size_t a, size_t b) {
  while (a >= b)
    a -= b;
  return a;
}

size_t gcd(size_t a, size_t b) {
  while (a > 0 && b > 0) {
    if (a > b)
      a = reminder(a, b);
    else
      b = reminder(b, a);
  }
  return a + b;
}

size_t divide(size_t a, size_t b) {
  size_t res = 0;
  while (a >= b) {
    a -= b;
    res++;
  }
  return res;
}

size_t lcm(size_t a, size_t b) { return multiply(a, divide(b, gcd(a, b))); }

size_t sum(size_t a, size_t b) {
  while (b > 0) {
    b--;
    a++;
  }
  return a;
}

size_t multiply_by_inc(size_t a, size_t b) {
  size_t res = 0;
  while (b) {
    res = sum(res, a);
    b--;
  }
  return res;
}

size_t power(size_t a, size_t b) {
  size_t res = 1;
  while (b) {
    --b;
    res = multiply_by_inc(res, a);
  }
  return res;
}

size_t faster_power(size_t a, size_t b) {
  size_t res = 1;
  size_t degree = 0;
  if (!b)
    return res;
  res *= a;
  ++degree;
  while (degree * 2 < b) {
    res *= res;
    degree *= 2;
  }
  return res * faster_power(a, b - degree);
}

int main() {
  size_t a, b;
  std::cin >> a >> b;
  //  std::cout << "power: " << power(a, b) << "\n";
  //  std::cout << "fast power: " << faster_power(a, b) << "\n";
  return 0;
}
