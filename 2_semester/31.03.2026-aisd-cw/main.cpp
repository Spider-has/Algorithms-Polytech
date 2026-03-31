#include <cstddef>
#include <utility>
#include <vector>

template < class Key, class T, class Hash, class Equal > struct HashTabl
{
  using Value = std::pair< Key, T >;
  size_t size;
  size_t capacity;
  Value **slots;
};

template < class K, class T, class Hash, class Equal >
size_t psl(const HashTabl< K, T, Hash, Equal > &table, typename HashTabl< K, T, Hash, Equal >::Value **value)
{
  Hash hasher;
  size_t home = hasher((*value)->first) % table.capacity;
  size_t ind = value - table.data;
  if (ind >= home)
  {
    return ind - home;
  }
  return table.capacity - (home - ind);
}

template < class K, class T, class Hash, class Equal >
typename HashTabl< K, T, Hash, Equal >::Value **find(const HashTabl< K, T, Hash, Equal > &table, const K &key)
{
  // Смотрим на значения по хэшу, если элементы не совпадают, двигаем и сравниваем psl. Идем пока psl текущего элемента
  // меньше или равен чем psl элемента в таблице
}

template < class K, class T > struct HashTable
{
  using Value = std::pair< K, T >;
  std::vector< std::pair< Value, bool > > t1;
  std::vector< std::pair< Value, bool > > t2;

  size_t size;
  size_t capacity;
};

template < class K, class T, class HS1, class HS2, class EQ > size_t erase(HashTable< K, T > &table, const K &k)
{
  size_t i1 = HS1{}(k) % table.capacity;
  size_t i2 = HS2{}(k) % table.capacity;
  if (table.t1[i1].second && EQ{}(table.t1[i1].first.first, k))
  {
    table.t1[i1].second = false;
    table.size--;
    return 1;
  }
  if (table.t2[i2].second && EQ{}(table.t2[i2].first.first, k))
  {
    table.t2[i2].second = false;
    table.size--;
    return 1;
  }
  return 0;
}
