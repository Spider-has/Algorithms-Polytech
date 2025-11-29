#include <iostream>

struct Book
{
  const char *title;
  const char *author;
};

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

// Задача 2.1.
// Пусть определена структура книги Book с автором и названием книги
// Посчитать, сколько книг указанного автора находится в массиве
size_t authored_by(const Book *const *lib, size_t books, const char *author)
{
  size_t count = 0;
  if (lib)
  {
    for (size_t i = 0; i < books; i++)
    {
      count += str_cmp(lib[i]->author, author);
    }
  }
  return count;
}

size_t get_size(const char *str)
{
  size_t size = 0;
  if (str)
  {
    while (str[size])
    {
      size++;
    }
  }
  return size;
}

// Задача 2.2.
// Найти книгу с самым длинным названием. Вернуть указатель на неё
const Book *longest_title(const Book *const *lib, size_t books)
{
  size_t max_size = 0;
  size_t max_size_i = 0;
  if (lib && lib[0] && books)
  {
    max_size = get_size(lib[0]->title);
    for (size_t i = 1; i < books; i++)
    {
      size_t curr_size = get_size(lib[i]->title);
      if (curr_size > max_size)
      {
        max_size = curr_size;
        max_size_i = i;
      }
    }
    return lib[max_size_i];
  }
  return nullptr;
}