#include <iostream>
#include <numeric>

unsigned int div(unsigned int a, unsigned int b) {
  unsigned int result = 0;
  while (a >= b) {
    result++;
    a = a - b;
  }
  return result;
}

unsigned long int multiply(unsigned int a, unsigned int b) {
  unsigned long int result = 0;
  while (b > 0) {
    result += a;
    b--;
  }
  return result;
}

unsigned int mod(unsigned int a, unsigned int b) {
  while (a >= b)
    a -= b;
  return a;
}

unsigned int gcd(unsigned int a, unsigned int b) {
  while (a != 0 && b != 0) {
    if (a >= b)
      a = mod(a, b);
    else
      b = mod(b, a);
  }
  return a + b;
}

unsigned long int lcm(unsigned int a, unsigned int b) {
  return multiply(div(a, gcd(a, b)), b);
}

int main() {
  unsigned int a = 117;
  unsigned int b = 11;
  std::cout << "div: " << div(a, b) << ", mod: " << mod(a, b) << "\n";
  std::cout << "multiply: " << multiply(a, b) << "\n";
  std::cout << "gcd: " << gcd(a, b) << ", 30 | 6 = " << gcd(30, 6) << ", "
            << gcd(6, 30) << "\n";
  std::cout << "lcm: " << lcm(a, b) << ", real: " << std::lcm(a, b) << "\n";
  std::cout << "lcm: " << lcm(1235, 113) << ", real: " << std::lcm(1235, 113)
            << "\n";
  // Тест: одинаковые числа
  std::cout << "lcm(12, 12) = " << lcm(12, 12) << "\n"; // 12

  // Тест: взаимно простые
  std::cout << "lcm(7, 13) = " << lcm(7, 13) << "\n"; // 91

  // Тест: одно число делит другое
  std::cout << "lcm(15, 5) = " << lcm(15, 5) << "\n"; // 15

  // Тест: большие числа (проверка на переполнение в multiply)
  std::cout << "lcm(100000, 99999) = " << lcm(100000, 99999) << "\n";
  // Должно быть 9999900000 — влезает в unsigned long int
  return 0;
}
