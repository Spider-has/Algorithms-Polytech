#include <iostream>

struct BimBim
{
  const int a;
  const int &b;
  // корректно, объявление стуктуры BamBam внутри другой структуры/
  struct BamBam;

  //   BimBim(int );
  ~BimBim()
  {
    std::cout << "abc\n";
  };
  BimBim():
      a(1),
      b(2)
  {
  }

  // ошибка компиляции -- неверный синтаксис, попытка объявить список аргументов у того, что не ялвяется функцией.
  //   BamBam *(BimBim *BamBamBam)(BimBim);

  // ошибка компиляции -- noexcept присущь только методам и функциям, нельзя его применять к обычным полям объекта.
  //   BimBim &BamBamBimBim noexcept;

  // корректно, указатель на объект BamBam
  BamBam *BimBimBamBam;

  // корректно, метод структуры BimBim, который принимает в качестве аргумента объект BimBim
  //   BimBim Bam(BimBim BamBamBim);

  // корректно, перегрузка оператора для объекта BimBim, которая принимает в качестве аргумента объект BamBam и
  // возвращает BamBam
  BamBam operator=(BamBam bimBim);

  // ошибка компиляции -- два параметра одного имени.
  //   BimBim(BamBam BimBim, BamBam BimBim);

  // корректно, метод объекта BimBim, который принимает объект BimBim и возвращает указатель на BimBim
  //   BimBim *BamBamBimBimBamBam(BimBim bamBam);

  // Ошибка компиляции -- у деструктора не должно быть аргументов
  //   ~BimBim(BamBam bimBam = {});

  // ошибка компиляции, попытка сделать поведение по умолчанию у самописного метода объекта.
  //   BimBim bamBimbam(BamBam bimBam, BimBim bamBim) = default;
};

int main()
{
  BimBim a;
}