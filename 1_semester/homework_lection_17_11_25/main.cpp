#include <iostream>

struct p_t
{
  int x, y;
};

void print_pt(const p_t &pt)
{
  std::cout << pt.x << " " << pt.y << "\n";
}

const p_t &left_bot(const p_t &lhs, const p_t &rhs)
{
  if ((lhs.x < rhs.x) || (lhs.x == rhs.x && lhs.y < rhs.y))
  {
    return lhs;
  }
  else
  {
    return rhs;
  }
}

const p_t &right_top(const p_t &lhs, const p_t &rhs)
{
  if ((lhs.x > rhs.x) || (lhs.x == rhs.x && lhs.y > rhs.y))
  {
    return lhs;
  }
  else
  {
    return rhs;
  }
}

const p_t *left_bot(const p_t *lhs, size_t size)
{
  const p_t *lb_pt = lhs;
  for (size_t i = 1; i < size; i++)
  {
    lb_pt = &left_bot(*lb_pt, lhs[i]);
  }
  return lb_pt;
}

const p_t *right_top(const p_t *lhs, size_t size)
{
  const p_t *rt_pt = lhs;
  for (size_t i = 1; i < size; i++)
  {
    rt_pt = &right_top(*rt_pt, lhs[i]);
  }
  return rt_pt;
}

int main()
{
  p_t A{2, 2};
  p_t B{1, 1};

  const p_t pt_arr[] = {{1, 1}, {5, 0}, {2, 2}, {0, 100}, {0, 1}, {0, 0}};
  const p_t *l_b = nullptr;
  const p_t *r_t = nullptr;
  // const p_t &left_b = left_bot(A, B);
  // const p_t &right_t = right_top(A, B);
  // const p_t &ref = left_bot({1, 1}, {2, 2});
  // print_pt(ref);
  // print_pt(left_b);
  // print_pt(right_t);
  l_b = left_bot(pt_arr, 6);
  r_t = right_top(pt_arr, 6);
  print_pt(*l_b);
  print_pt(*r_t);
}
