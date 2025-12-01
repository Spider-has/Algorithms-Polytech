#include <iostream>

namespace top
{
  namespace pod
  {
    struct p_t
    {
      int x, y;
    };

    bool operator==(p_t a, p_t b);
    bool operator!=(p_t a, p_t b);

    struct frame_t
    {
      p_t left_bot;
      p_t right_top;
    };
  }
  using namespace pod;

  namespace figures
  {
    struct IDraw
    {
      virtual p_t begin() const = 0;
      virtual p_t next(p_t) const = 0;

      virtual ~IDraw() = default;
    };

    struct Dot : IDraw
    {
      Dot(int x, int y);
      Dot(p_t pt);

      p_t begin() const override;
      p_t next(p_t) const override;
      p_t o;
    };
    size_t count(IDraw &d);

  }
  using namespace figures;

  void makeFigures(IDraw **f, size_t size);
  void getPoints(IDraw *figure, p_t **ps, size_t &size);

  frame_t buildFrame(const p_t *ps, size_t s);
  char *buildCanvas(frame_t f);
  void paintCanvas(char *cnv, frame_t frame, const p_t *ps, size_t k, char f);
  void printCanvas(const char *cnv, frame_t fr);
}

int main()
{
  using namespace top;
  IDraw *f[3] = {};
  p_t *p = nullptr;
  size_t s = 0;

  char *cnv = nullptr;

  int err = 0;
  try
  {
    makeFigures(f, 3);
    for (size_t i = 0; i < 3; i++)
    {
      getPoints(f[i], &p, s);
    }
    frame_t frame = buildFrame(p, s);
    cnv = buildCanvas(frame);
    paintCanvas(cnv, frame, p, s, '#');
    printCanvas(cnv, frame);
  }
  catch (...)
  {
    err = 1;
  }

  for (size_t i = 0; i < 3; i++)
  {
    delete[] f[i];
  }
  delete[] f;
  delete[] p;
  delete[] cnv;
  return err;
}

bool top::pod::operator==(p_t a, p_t b)
{
  return a.x == b.x && a.y == b.y;
}

bool top::pod::operator!=(p_t a, p_t b)
{
  return !(a == b);
}

size_t top::figures::count(IDraw &d)
{
  {
    size_t k = 0;
    p_t p = d.begin();
    while (d.next(p) == d.begin())
    {
      k++;
      p = d.next(p);
    }
    return k;
  }
}

top::Dot::Dot(int x, int y):
    IDraw(),
    o{x, y}
{
}

top::p_t top::Dot::begin() const
{
  return o;
}

top::p_t top::Dot::next(p_t prev) const
{
  return o;
}

void top::makeFigures(IDraw **f, size_t size)
{
  f[0] = new Dot(0, 0);
  f[1] = new Dot(5, 3);
  f[2] = new Dot(4, 4);
}