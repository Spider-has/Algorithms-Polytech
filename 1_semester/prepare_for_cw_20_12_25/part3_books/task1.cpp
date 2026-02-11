#include <iostream>
struct Book
{
  const char *title;
  const char *author;
};

struct Refs
{
  const Book *src;
  size_t refs;
  const Book *const *books;
};

/* Как часто ссылаются на книгу?
 * Посчитать, сколько книг ссылаются на заданную
 * Сформировать массив из этих книг
 */

size_t refs_to(
    // (результат) указатель на массив из книг
    //   которые ссылаются на заданную
    const Book ***res,
    const Book *src, // заданная книга
    // набор ссылок
    const Refs *rs, size_t s)
{
  size_t count = 0;
  for (size_t i = 0; i < s; i++)
  {
    bool found = false;
    for (size_t j = 0; j < rs[i].refs && !found; j++)
    {
      if (rs[i].books[j] == src)
      {
        count++;
        found = true;
      }
    }
  }
  const Book **result = nullptr;
  if (count)
  {
    result = new const Book *[count];
    size_t size = 0;
    for (size_t i = 0; i < s; i++)
    {
      bool found = false;
      for (size_t j = 0; j < rs[i].refs && !found; j++)
      {
        if (rs[i].books[j] == src)
        {
          result[size++] = rs[i].src;
          found = true;
        }
      }
    }
  }

  *res = result;
  return count;
}

// В наборе ссылок найти книги
//  количество ссылок на которые меньше заданных
size_t refs_to_less(size_t k, // количество ссылок [0; k)
                              // (результат) указатель на массив из книг
                    const Book ***res,

                    // набор ссылок
                    const Refs *rs, size_t s)
{
}