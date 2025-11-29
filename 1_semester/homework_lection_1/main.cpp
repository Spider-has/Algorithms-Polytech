#include <iostream>

int get_coefficient(unsigned row, long long column) {
  if (column <= 0 || column > row || row <= 0)
    return 0;
  if (column == 1 || column == row)
    return 1;
  return get_coefficient(row - 1, column - 1) +
         get_coefficient(row - 1, column);
}

char get_cofficient(int a, char b) 
{
return 'a';
}

int main() {
  int row, column;
  std::cin >> row >> column;
  std::cout << get_coefficient(row, column);

  return 0;
}
