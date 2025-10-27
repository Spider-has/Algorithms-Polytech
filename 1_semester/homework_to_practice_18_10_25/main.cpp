#include <iostream>

int get_max_bit_position_in_number(int num) {
  if (num == 0)
    return -1;
  int position = 0;
  while (num >> 1) {
    position++;
    num = num >> 1;
  }
  return position;
}

bool is_number_bit_palindrome(int num) {
  int rightBitPosition = get_max_bit_position_in_number(num);
  int leftBitPosition = 0;

  while (leftBitPosition < rightBitPosition) {
    int leftBit = (num >> leftBitPosition) & 0b1;
    int rightBit = (num >> rightBitPosition) & 0b1;

    rightBitPosition--;
    leftBitPosition++;

    if (leftBit != rightBit)
      return false;
  }
  return true;
}

bool is_number_bit_palindrome_rec(int num, int left, int right) {
  if (left >= right)
    return true;
  int maxBit = (num >> right) & 0b1;
  int minBit = (num >> left) & 01;
  if (maxBit == minBit)
    return is_number_bit_palindrome_rec(num, left + 1, right - 1);
  return false;
}

bool is_number_bit_palindrome_recursive(int num) {
  int maxBitPosition = get_max_bit_position_in_number(num);
  return is_number_bit_palindrome_rec(num, 0, maxBitPosition);
}

int main() {
  int num = 5;
  std::cin >> num;
  std::cout << "is bit palendrome: " << is_number_bit_palindrome_recursive(num)
            << "\n";
}
