#include <cstddef>
#include <iostream>
#include <stdexcept>

class Ints
{
  size_t s;
  int *data;

public:
  Ints(size_t size, int fill);
  Ints(const Ints &ints);
  Ints(Ints &&ints);
  Ints();

  Ints &operator=(const Ints &ints);
  Ints &operator=(Ints &&ints);

  ~Ints();

  size_t size() const;
  void set(size_t id, int value);
  int get(size_t id) const;
  void append(int value);
  Ints append(Ints values) const;
  Ints append(int value) const;
};

Ints::Ints() : s(0), data(nullptr)
{
}

int *copy(const int *origin, int *newArr, size_t s)
{
  for (size_t i = 0; i < s; i++)
  {
    *newArr = origin[i];
    newArr++;
  }
  return newArr;
}

Ints in()
{
  Ints r(1, 1);
  int v = 0;
  while (std::cin >> v)
  {
    r.append(v);
  }
  return r;
}

int main()
{
  Ints data = in();
  for (size_t i = 0; i < data.size(); i++)
  {
  }
}

Ints::Ints(size_t size, int fill) : s(size), data(new int[size])
{
  for (size_t i = 0; i < size; i++)
  {
    data[i] = fill;
  }
}

Ints::Ints(const Ints &ints) : s(ints.s), data(new int[ints.s])
{
  for (size_t i = 0; i < ints.s; i++)
  {
    data[i] = ints.data[i];
  }
}

Ints::Ints(Ints &&ints) : s(ints.s), data(ints.data)
{
  ints.data = nullptr;
}

Ints &Ints::operator=(const Ints &ints)
{
  if (this == &ints)
    return *this;
  s = ints.s;
  int *temp = new int[s];
  copy(ints.data, temp, s);
  delete[] data;
  data = temp;
  return *this;
}

Ints &Ints::operator=(Ints &&ints)
{
  delete[] data;
  s = ints.s;
  data = ints.data;
  ints.data = nullptr;
  return *this;
}

size_t Ints::size() const
{
  return s;
}

int Ints::get(size_t id) const
{
  if (id >= s)
    throw std::range_error("Index out of range");
  return data[id];
}

void Ints::set(size_t id, int val)
{
  if (id >= s)
    throw std::range_error("Index out of range");
  data[id] = val;
}

void Ints::append(int value)
{
  Ints newInts(s + 1, 0);
  copy(data, newInts.data, s);
  newInts.data[s] = value;
  return newInts;
}

Ints Ints::append(int value) const
{
  Ints newInts(s + 1, 0);
  copy(data, newInts.data, s);
  newInts.data[s] = value;
  return newInts;
}

Ints Ints::append(const Ints values) const
{
  Ints res;
  res.data = new int[s + values.s];
  for (size_t i = 0; i < s; i++)
  {
    res.data[i] = data[i];
  }
  for (size_t i = s; i < s + values.s; i++)
  {
    res.data[i] = values.data[i - s];
  }
  res.s = s + values.s;
  return res;
}

Ints::~Ints()
{
  delete[] data;
}
