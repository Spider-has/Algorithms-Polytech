#include <iostream>

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

struct p_t
{
  int x, y;
};

struct Points
{
  Points() = default;
  p_t get(size_t id) const;
  void set(size_t id, p_t a);

  size_t size() const;

  Points append(p_t a) const;
  Points append(const Points &w) const;

private:
  Points(Ints &&d);
  Ints data;
};

Points::Points(Ints &&d) : data(std::move(d))
{
}

Points Points::append(const Points &w) const
{
  Ints delta(w.data);
  delta = data.append(delta);
  return Points(std::move(delta));
}

int main()
{
}
