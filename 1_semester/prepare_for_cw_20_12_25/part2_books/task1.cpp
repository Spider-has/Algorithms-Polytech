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
 * Сколько и каких книг определённого автора (авторов) нужно
    изъять из библиотеки (библиотек)?
 * Сформировать смету списанных книг, авторы которых
    соответствуют автору заданной книги
    или одному из авторов книг в заданном наборе
 */

bool is_book_out(size_t stock, size_t count)
{
  return stock && !count;
}

bool is_same_author(const Book *book, const Book *match)
{
  return book->author == match->author;
}

bool is_author_mathes(const Book *book, const Book *const *match, size_t k)
{
  for (size_t i = 0; i < k; i++)
  {
    if (is_same_author(book, match[i]))
    {
      return true;
    }
  }
  return false;
}

size_t out_list(const Book ***to_out, const size_t **out_each, const Lib &db, const Book *book)
{
  size_t out_books = 0;
  for (size_t i = 0; i < db.books; i++)
  {
    if (is_book_out(db.stocks[i], db.counts[i]) && is_same_author(db.lib[i], book))
    {
      out_books++;
    }
  }
  const Book **out = nullptr;
  size_t *out_counts = nullptr;
  if (out_books)
  {
    out = new const Book *[out_books];
    out_counts = new size_t[out_books];
    size_t count = 0;
    for (size_t i = 0; i < db.books; i++)
    {
      if (is_book_out(db.stocks[i], db.counts[i]) && is_same_author(db.lib[i], book))
      {
        out[count] = db.lib[i];
        out_counts[count] = db.stocks[i];
        count++;
      }
    }
  }
  *to_out = out;
  *out_each = out_counts;
  return out_books;
}

size_t out_list(
    // (результат) указатель на книги из сметы
    //   книги не должны повторяться, если одна книга
    //   соответствует нескольким образцам
    const Book ***to_out,

    // (результат) указатель на массив из количеств каждой книги сметы
    const size_t **out_each, const Lib &db,
    const Book *const *match, // книги-образцы
    size_t b                  // количество книг
)
{
  size_t out_books = 0;
  for (size_t i = 0; i < db.books; i++)
  {
    if (is_book_out(db.stocks[i], db.counts[i]) && is_author_mathes(db.lib[i], match, b))
    {
      out_books++;
    }
  }
  const Book **out = nullptr;
  size_t *out_counts = nullptr;
  if (out_books)
  {
    out = new const Book *[out_books];
    out_counts = new size_t[out_books];
    size_t count = 0;
    for (size_t i = 0; i < db.books; i++)
    {
      if (is_book_out(db.stocks[i], db.counts[i]) && is_author_mathes(db.lib[i], match, b))
      {
        out[count] = db.lib[i];
        out_counts[count] = db.stocks[i];
        count++;
      }
    }
  }
  *to_out = out;
  *out_each = out_counts;
  return out_books;
}

// возвращает массив с размерами смет
// количество смет равно количеству библиотек (l)
size_t *out_list(
    // (результат) указатель на массивы книг из сметы каждой библиотеки
    const Book ****to_out,

    // (результат) указатель на массив из
    //   массивов количеств книг в сметах
    const size_t ***out_each,
    const Lib *libs, // массив библиотек
    size_t l,        // количество библиотек
    const Book *book)
{
  size_t *out_lib_list = nullptr;
  const Book ***out_books = nullptr;
  const size_t **out_each_books = nullptr;
  if (l && book)
  {
    out_lib_list = new size_t[l];
    size_t count = 0;
    try
    {
      out_books = new const Book **[l];
      out_each_books = new const size_t *[l];
      for (size_t i = 0; i < l; i++)
      {
        out_lib_list[i] = out_list(&out_books[i], &out_each_books[i], libs[i], book);
        count++;
      }
    }
    catch (...)
    {
      for (size_t i = 0; i < count; i++)
      {
        delete[] out_books[i];
        delete[] out_each_books[i];
      }
      delete[] out_books;
      delete[] out_each_books;
      delete[] out_lib_list;
      throw;
    }
  }
  *to_out = out_books;
  *out_each = out_each_books;
  return out_lib_list;
}

size_t *out_list(const Book ****to_out, const size_t ***out_each, const Lib *libs, size_t l, const Book *const *match,
                 size_t b)
{
  size_t *out_lib_list = nullptr;
  const Book ***out_books = nullptr;
  const size_t **out_each_books = nullptr;
  if (l && match)
  {
    out_lib_list = new size_t[l];
    size_t count = 0;
    try
    {
      out_books = new const Book **[l];
      out_each_books = new const size_t *[l];
      for (size_t i = 0; i < l; i++)
      {
        out_lib_list[i] = out_list(&out_books[i], &out_each_books[i], libs[i], match, b);
        count++;
      }
    }
    catch (...)
    {
      for (size_t i = 0; i < count; i++)
      {
        delete[] out_books[i];
        delete[] out_each_books[i];
      }
      delete[] out_books;
      delete[] out_each_books;
      delete[] out_lib_list;
      throw;
    }
  }
  *to_out = out_books;
  *out_each = out_each_books;
  return out_lib_list;
}