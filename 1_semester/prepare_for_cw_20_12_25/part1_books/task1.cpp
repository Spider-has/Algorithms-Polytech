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

/* Какие книги написал заданный автор (или авторы)?
 * Найти в библиотеке все книги, авторы которых
    соответствуют автору заданной книги
    или одному из авторов книг в заданном наборе
 * Поиск нужно выполнить для одной библиотеки
    и для нескольких
 * Автор один и тот же, если соответствующие указатели
    в Book равны
 * Функция должна вовзращать nullptr, если таких книг нет
 * Массивы с результатами должны располагаться во Free Store
 */

void copy_books(const Book **from, const Book **to, size_t k)
{
  for (size_t i = 0; i < k; i++)
  {
    to[i] = from[i];
  }
}

void cut_books(const Book ***arr, size_t newSize)
{
  const Book **newArr = nullptr;
  if (newSize)
  {
    newArr = new const Book *[newSize];
    copy_books(*arr, newArr, newSize);
  }
  delete[] *arr;
  *arr = newArr;
}

void same_author_fill(const Lib &db, const Book **books, size_t &count, const Book *book)
{
  for (size_t i = 0; i < db.books; i++)
  {
    if (book->author == db.lib[i]->author)
    {
      books[count++] = db.lib[i];
    }
  }
}

const Book **same_author(size_t &out, const Lib &db, const Book *book)
{
  if (db.books && book)
  {
    size_t count = 0;
    const Book **author_books = new const Book *[db.books];
    same_author_fill(db, author_books, count, book);
    try
    {
      cut_books(&author_books, count);
    }
    catch (...)
    {
      delete[] author_books;
      throw;
    }
    out = count;
    return author_books;
  }
  return nullptr;
}

void expand_books(const Book ***books, size_t &size, size_t newSize)
{
  const Book **newBooks = new const Book *[newSize];
  copy_books(*books, newBooks, size);
  delete[] *books;
  size = newSize;
  *books = newBooks;
}

void libs_same_author_fill(const Lib **libs, size_t l, const Book ***authorBooks, size_t &size, size_t &count,
                           const Book *book)
{
  size_t k = count;
  for (size_t i = 0; i < l; i++)
  {
    if (k + libs[i]->books >= size)
    {
      expand_books(authorBooks, size, size + libs[i]->books);
    }
    size_t c = 0;
    same_author_fill(*libs[i], *(authorBooks) + k, c, book);
    k += c;
  }
  count = k;
}

const Book **same_author(size_t &out, const Lib **libs, size_t l, const Book *book)
{
  if (l && book && libs[0])
  {
    size_t count = 0;
    size_t size = libs[0]->books ? libs[0]->books : 1;
    const Book **author_books = new const Book *[size];
    try
    {
      libs_same_author_fill(libs, l, &author_books, size, count, book);
      cut_books(&author_books, count);
      out = count;
      return author_books;
    }
    catch (...)
    {
      delete[] author_books;
      throw;
    }
  }
  return nullptr;
}

const Book **same_author(size_t &out, const Lib &db, const Book *const *match, size_t b)
{
  if (db.books && b)
  {
    size_t count = 0;
    const Book **authors_books = new const Book *[db.books];
    for (size_t i = 0; i < b; i++)
    {
      size_t authorCount = 0;
      same_author_fill(db, authors_books + count, authorCount, match[i]);
      count += authorCount;
    }
    try
    {
      cut_books(&authors_books, count);
    }
    catch (...)
    {
      delete[] authors_books;
      throw;
    }
    out = count;
    return authors_books;
  }
  return nullptr;
}

const Book **same_author(size_t &out, const Lib **libs, size_t l, const Book *const *match, size_t b)
{
  if (l && b && libs[0])
  {
    size_t count = 0;
    size_t size = libs[0]->books ? libs[0]->books : 1;
    const Book **libs_authors = new const Book *[size];
    try
    {
      for (size_t i = 0; i < b; i++)
      {
        libs_same_author_fill(libs, l, &libs_authors, size, count, match[i]);
      }
      cut_books(&libs_authors, count);
      out = count;
      return libs_authors;
    }
    catch (...)
    {
      delete[] libs_authors;
      throw;
    }
  }
  return nullptr;
}