#include <iostream>
#include <type_traits>
#include <vector>
template < class T, class = void > struct has_size : std::false_type
{
};

template < class T > struct has_size< T, std::void_t< decltype(std::declval< const T & >().size()) > > : std::true_type
{
};

#include <iostream>
#include <type_traits>

template < class T, std::enable_if_t< has_size< T >::value, int > = 0 > void printSize(const T &value)
{
  std::cout << "size: " << value.size() << '\n';
}

void printSize(...)
{
  std::cout << "size() is unavailable\n";
}

int main()
{
  printSize(std::vector{1, 2, 3});
  printSize(1);
}
