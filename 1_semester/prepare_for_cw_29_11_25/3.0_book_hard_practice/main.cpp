#include <iostream>

struct Book
{
  const char *title;
  const char *author;
};
// Задача 3.1.
// Пусть структура книжного каталога задана структурой Lib
// Количество различных наименований задаётся полем books
// Информация о книгах записана в массиве lib
// Количество каждой книги под учётом записано в массив counts на соответствующих позициях
// Количество каждой книги в наличии - в массиве stocks

struct Lib
{
  size_t books;
  const Book *const *lib;
  const size_t *counts;
  const size_t *stocks;
};

// Вернуть массив из указателей на книги, которые закончились
// Массив с результатами должен располагаться во Free Store,
// ...но ссылаться на книги в каталоге. Количество книг записать в out
const Book **out_of_stocks(const Lib &db, size_t &out)
{
  size_t out_stocks_count = 0;
  for (size_t i = 0; i < db.books; i++)
  {
    out_stocks_count += db.stocks[i] == 0;
  }
  if (out_stocks_count)
  {
    const Book **out_books = new const Book *[out_stocks_count];
    size_t out_books_i = 0;
    out = out_stocks_count;
    for (size_t i = 0; i < db.books; i++)
    {
      if (db.stocks[i] == 0)
      {
        out_books[out_books_i] = db.lib[i];
        out_books_i++;
      }
    }
    return out_books;
  }
  return nullptr;
}

// Задача 3.2.
// Найти хотя бы одного автора, чьих книг не осталось
// Если таких авторов нет - вернуть nullptr
// Если таких авторов несколько - вернуть любого
// Учитывать только авторов книг каталога

bool str_cmp(const char *arr1, const char *arr2)
{
  if (arr1 && arr2)
  {
    size_t i = 0;
    while (arr1[i] && arr2[i])
    {
      if (arr1[i] != arr2[i])
      {
        return false;
      }
      i++;
    }
    return arr1[i] == arr2[i];
  }
  return false;
}

const int find(const char *const *arr, size_t s, const char *value)
{
  for (size_t i = 0; i < s; i++)
  {
    if (arr[i] && str_cmp(arr[i], value))
    {
      return i;
    }
  }
  return -1;
}

const char **expanded_char(const char *const *old, size_t oldSize, size_t newSize)
{
  const char **newArr = new const char *[newSize];
  for (size_t i = 0; i < oldSize; i++)
  {
    newArr[i] = old[i];
  }
  return newArr;
}

size_t *expanded_size(const size_t *old, size_t oldSize, size_t newSize)
{
  size_t *newArr = new size_t[newSize];
  for (size_t i = 0; i < oldSize; i++)
  {
    newArr[i] = old[i];
  }
  return newArr;
}

const char *out_of_author(const Lib &db)
{
  size_t authors_count = 0;
  const char **authors = nullptr;
  size_t *authors_books_count = nullptr;
  if (db.books && db.lib[0])
  {
    authors = new const char *[1];
    authors_books_count = new size_t[authors_count];
    authors_books_count[0] = db.stocks[0];
    authors[0] = db.lib[0]->author;
    authors_count++;
    try
    {
      for (size_t i = 1; i < db.books; i++)
      {
        const int author_i = find(authors, authors_count, db.lib[i]->author);
        if (author_i == -1)
        {
          authors = expanded_char(authors, authors_count, authors_count + 1);
          authors_books_count = expanded_size(authors_books_count, authors_count, authors_count + 1);
          authors[authors_count + 1] = db.lib[i]->author;
          authors_books_count[authors_count + 1] = db.stocks[i];
          authors_count++;
        }
        else
        {
          authors_books_count[author_i] += db.stocks[i];
        }
      }
    }
    catch (...)
    {
      for (size_t i = 0; i < authors_count; i++)
      {
        delete[] authors[i];
      }
      delete[] authors;
      delete[] authors_books_count;
      throw;
    }
    for (size_t i = 0; i < authors_count; i++)
    {
      if (authors_books_count[i] == 0)
      {
        return authors[i];
      }
    }
  }
  return nullptr;
}

// Задача 3.3.
// Найти списанные книги (под учётом - 0), но оставшиеся в наличии
// Вернуть массив из указателей на эти книги, а количество этих книг
// ...записать в disc
const Book **discarded(const Lib &db, size_t &disc);

// Задача 3.4.
// Найти всех авторов, чьих книг не осталось
// Вернуть массив из имён авторов и записать количество
// ...этих авторов в out
// Если таких авторов нет, то вернуть nullptr, а в out записать 0
const char **out_of_authors(const Lib &db, size_t &out);
