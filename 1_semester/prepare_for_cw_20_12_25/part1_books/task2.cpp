#include <iostream>

struct Book
{
  const char *title;
  const char *author;
};

struct Lib
{
  size_t books;
  const Book *const *lib;
  const size_t *counts;
  const size_t *stocks;
};

/*
 * Сколько книг определённого автора (авторов) нужно изъять из библиотеки (библиотек)?
 * Посчитать копии списанных книг, авторы которых
    соответствуют автору заданной книги
    или одному из авторов книг в заданном наборе
 * Книга отправлена под списание, если она в наличии
    но под учётом не находится. Её количество копий в наличии
    добавляется к общему количеству под списание
 * Поиск нужно выполнить для одной библиотеки
    и для нескольких
 */

bool should_write_off(size_t stock, size_t count)
{
  return stock > 0 && !count;
}

size_t space_after_out(const Lib &db, const Book *book)
{
  size_t count = 0;
  for (size_t i = 0; i < db.books; i++)
  {
    if (db.lib[i]->author == book->author && should_write_off(db.stocks[i], db.counts[i]))
    {
      count += db.stocks[i];
    }
  }
  return count;
}

size_t space_after_out(const Lib *libs, size_t l, const Book *book)
{
  size_t size = 0;
  for (size_t i = 0; i < l; i++)
  {
    size += space_after_out(libs[i], book);
  }
  return size;
}

bool book_match(const Book *book, const Book *const *match, size_t b)
{
  for (size_t i = 0; i < b; i++)
  {
    if (book->author == match[i]->author)
    {
      return true;
    }
  }
  return false;
}

size_t space_after_out(const Lib &db, const Book *const *match, size_t b)
{
  size_t size = 0;
  for (size_t i = 0; i < db.books; i++)
  {
    if (book_match(db.lib[i], match, b) && should_write_off(db.stocks[i], db.counts[i]))
    {
      size += db.stocks[i];
    }
  }
  return size;
}

size_t space_after_out(const Lib *libs, size_t l, const Book *const *match, size_t b)
{
  size_t size = 0;
  for (size_t i = 0; i < l; i++)
  {
    size += space_after_out(libs[i], match, b);
  }
  return size;
}