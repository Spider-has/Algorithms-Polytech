#include <iostream>

// Задача 1.1.
// Найти в массиве data все значения f
// ...и вернуть массив указателей на эти значения
// В found записать количество найденных элементов
// Массив с результатами должен располагаться во Free Store
const int **find_all(const int *data, size_t s, int f, size_t &found)
{
  size_t count = 0;
  for (size_t i = 0; i < s; i++)
  {
    count += data[i] == f;
  }
  if (count)
  {
    const int **result = new const int *[count];
    size_t res_i = 0;
    found = count;
    for (size_t i = 0; i < s; i++)
    {
      if (data[i] == f)
      {
        result[res_i] = &data[i];
        res_i++;
      }
    }
    return result;
  }
  return nullptr;
}

// Задача 1.2.
// В массиве из массивов data размером s найти самый длинный
// ...и самый короткий массив. Вернуть массив массивов,
// ...состоящий из копий этих массивов. Размеры массивов хранятся в sizes
// Результаты должны располагаться во Free Store
int **find_big_and_tiny(const int *const *data, size_t s, const size_t *sizes)
{
  size_t max_size_i = 0;
  size_t min_size_i = 0;
  for (size_t i = 0; i < s; i++)
  {
    max_size_i = sizes[i] > sizes[max_size_i] ? i : max_size_i;
    min_size_i = sizes[i] < sizes[min_size_i] ? i : min_size_i;
  }
  if (s)
  {
    int **res = new int *[2];
    res[0] = nullptr;
    res[1] = nullptr;
    try
    {
      res[0] = new int[sizes[max_size_i]];
      res[1] = new int[sizes[min_size_i]];

      for (size_t i = 0; i < sizes[max_size_i]; i++)
      {
        res[0][i] = data[max_size_i][i];
      }
      for (size_t i = 0; i < sizes[min_size_i]; i++)
      {
        res[1][i] = data[min_size_i][i];
      }
    }
    catch (...)
    {
      delete[] res[0];
      delete[] res[1];
      delete[] res;
      throw;
    }

    return res;
  }
  return nullptr;
}

// Задача 1.3.
// Построить новый массив из массивов, чередуя строки двух существующих
// На чётных позициях (начиная с 0) должны идти строки массива массивов aa1
// На нечётных позициях должны идти строки массива aa2
// Если строк не хватает в каком-то из массивов, то записывать nullptr
// Таким образом количество полученных строк не превышает удвоенного количества
// ...строк массива массивов с самым большим числом строк
// Количество строк и столбцов в каждом массиве массивов задано отдельно
// Массив массивов с результатами должен располагаться во Free Store и
// ...полностью скопировать данные оригинальных массивов
int **merge_odd_even(const int *const *aa1, size_t n1, size_t m1, const int *const *aa2, size_t n2, size_t m2)
{
  size_t max_n = n1 > n2 ? n1 : n2;
  size_t res_size = max_n * 2;
  if (res_size)
  {
    int **res = new int *[res_size];
    size_t i = 0;
    try
    {
      for (; i < res_size; i++)
      {
        if (i % 2 == 0)
        {
          if (i / 2 < n1 && m1)
          {
            res[i] = new int[m1];
            for (size_t j = 0; j < m1; j++)
            {
              res[i][j] = aa1[i / 2][j];
            }
          }
          else
          {
            res[i] = nullptr;
          }
        }
        else
        {
          if (i / 2 < n2 && m2)
          {
            res[i] = new int[m2];
            for (size_t j = 0; j < m2; j++)
            {
              res[i][j] = aa2[i / 2][j];
            }
          }
          else
          {
            res[i] = nullptr;
          }
        }
      }
    }
    catch (...)
    {
      for (size_t j = 0; j < i; j++)
      {
        delete[] res[j];
      }
      delete[] res;
      throw;
    }
    return res;
  }
  return nullptr;
}
