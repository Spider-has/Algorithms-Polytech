#include "boost_test.h"

BOOST_AUTO_TEST_CASE(test_deep_copy_success)
{
  // 1. Создаем исходный список: { [1, 2], [3] }
  Vec< int > v1{new int[2]{1, 2}, 2};
  Vec< int > v2{new int[1]{3}, 1};

  auto *node2 = new List< Vec< int > >{v2, nullptr};
  auto *node1 = new List< Vec< int > >{v1, node2};

  // 2. Копируем
  List< Vec< int > > *copied_h = copy(node1);

  // 3. Проверки
  BOOST_REQUIRE(copied_h != nullptr);
  BOOST_CHECK_NE(node1, copied_h);                     // Разные адреса узлов
  BOOST_CHECK_NE(node1->val.data, copied_h->val.data); // Разные адреса массивов

  BOOST_CHECK_EQUAL(copied_h->val.data[0], 1);
  BOOST_CHECK_EQUAL(copied_h->next->val.data[0], 3);

  // Очистка
  clear(node1);
  clear(copied_h);
}

BOOST_AUTO_TEST_CASE(test_copy_empty_list)
{
  List< Vec< int > > *empty_list = nullptr;
  List< Vec< int > > *result = copy(empty_list);

  BOOST_CHECK(result == nullptr);
}