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

size_t out_list(const Book ***to_out, const size_t **out_each, const Lib &db, const Book *book)
{
}