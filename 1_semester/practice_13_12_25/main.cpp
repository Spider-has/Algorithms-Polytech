#include <iostream>

struct Stud
{
  const char *fst;
  const char *snd;
  int year;
  int dep;
};

struct Subj
{
  const char *name;
  size_t people, classes;
  const Stud *const *studs;
  const size_t *visited;
};

using studs = const Stud *const *;

const Stud **copy(studs src, const Stud **dest, size_t k)
{
  for (size_t i = 0; i < k; i++)
  {
    dest[i] = src[i];
  }
  return dest + k;
}

bool contains(studs studs, size_t k, const Stud *s)
{
  bool result = false;
  for (size_t i = 0; i < k && !result; i++)
  {
    result = result || studs[i] == s;
  }
  return result;
}
void cut_studs(const Stud ***init, size_t new_count)
{
  const Stud **tmp = new const Stud *[new_count];
  copy((*init), tmp, new_count);
  delete[] (*init);
  (*init) = tmp;
}

const Stud **stud_union(size_t &r, studs s1, size_t k1, studs s2, size_t k2)
{
  const Stud **uni = new const Stud *[k1 + k2];
  size_t count = 0;
  copy(s1, uni, k1);
  count += k1;
  for (size_t i = 0; i < k2; i++)
  {
    if (!contains(uni, count, s2[i]))
    {
      uni[count++] = s2[i];
    }
  }
  try
  {
    cut_studs(&uni, count);
  }
  catch (...)
  {
    delete[] uni;
    throw;
  }
  r = count;
  return uni;
}

const Stud **stud_union(size_t &r, const Subj &s1, const Subj &s2)
{
  return stud_union(r, s1.studs, s1.people, s2.studs, s2.people);
}

const Stud **stud_union(size_t &r, const Subj *ss, size_t k)
{
  if (!k)
  {
    r = 0;
    return nullptr;
  }
  else if (k == 1)
  {
    const Stud **uni = new const Stud *[ss[0].people];
    copy(ss[0].studs, uni, ss[0].people);
    return uni;
  }
  size_t count = 0;
  const Stud **uni = stud_union(count, ss[0], ss[1]);
  for (size_t i = 2; i < k; i++)
  {
    try
    {
      size_t temp_count = 0;
      const Stud **new_uni = stud_union(temp_count, uni, count, ss[i].studs, ss[i].people);
      delete[] uni;
      uni = new_uni;
      count = temp_count;
    }
    catch (...)
    {
      delete[] uni;
      throw;
    }
  }
  r = count;
  return uni;
}

const Stud **filter(size_t &r, const Stud *const *studs, size_t k, bool (*cond)(const Stud *))
{
  size_t count = 0;
  const Stud **uni = new const Stud *[k];
  for (size_t i = 0; i < k; i++)
  {
    if (cond(studs[i]))
    {
      uni[count++] = studs[i];
    }
  }
  try
  {
    cut_studs(&uni, count);
  }
  catch (...)
  {
    delete[] uni;
    throw;
  }
  r = count;
  return uni;
}

bool is_bachalor(const Stud *s)
{
  return s->year < 5;
}

const Stud **stud_union_batch(size_t &r, const Subj *ss, size_t k)
{
  size_t count = 0;
  const Stud **uni = stud_union(count, ss, k);
  try
  {
    size_t tmp_count = 0;
    const Stud **tmp = filter(tmp_count, uni, count, is_bachalor);
    delete[] uni;
    uni = tmp;
    count = tmp_count;
  }
  catch (...)
  {
    delete[] uni;
    throw;
  }
  r = count;
  return uni;
}
template <size_t Y> bool is_year(const Stud *stud)
{
  return stud->year == Y;
}

bool (*is_year_y(size_t y))(const Stud *stud)
{
  switch (y)
  {
  case 1:
    return is_year<1>;
  case 2:
    return is_year<2>;
  case 3:
    return is_year<3>;
  case 4:
    return is_year<4>;
  case 5:
    return is_year<5>;
  default:
    throw std::logic_error("bad year");
  }
}

const Stud **stud_union_year(size_t &r, const Subj *ss, size_t k)
{
  size_t count = 0;
  const Stud **uni = stud_union(count, ss, k);
  try
  {
    size_t tmp_count = 0;
    const Stud **tmp = filter(tmp_count, uni, count, is_year_y(4));
    delete[] uni;
    uni = tmp;
    count = tmp_count;
  }
  catch (...)
  {
    delete[] uni;
    throw;
  }
  r = count;
  return uni;
}

struct r_t
{
  size_t n, q;
};

bool r_t_greater(r_t v1, r_t v2)
{
  return v1.n * v2.q > v2.n * v1.q;
}

r_t get_stud_r_t(const size_t visited, size_t classes)
{
  return r_t{visited, classes};
}

bool is_subj_popular(const Subj *s, r_t v)
{
  bool result = true;
  for (size_t i = 0; i < s->people && result; i++)
  {
    if (s->studs[i]->year > 4)
    {
      r_t stud_r_t = get_stud_r_t(s->visited[i], s->classes);
      result = result && r_t_greater(stud_r_t, v);
    }
  }
  return result;
}

const Subj **copy_subj(const Subj *const *from, const Subj **to, size_t k)
{
  for (size_t i = 0; i < k; i++)
  {
    to[i] = from[i];
  }
  return to + k;
}

void cut_subj(const Subj ***s, size_t newSize)
{
  const Subj **new_subs = new const Subj *[newSize];
  copy_subj(*s, new_subs, newSize);
  delete[] *s;
  *s = new_subs;
}

const Subj **popular_mag(size_t &r, const Subj **s, size_t k, r_t rv)
{
  if (!k)
  {
    r = 0;
    return nullptr;
  }
  size_t count = 0;
  const Subj **subs = new const Subj *[k];
  for (size_t i = 0; i < k; i++)
  {
    if (is_subj_popular(s[i], rv))
    {
      subs[count++] = s[i];
    }
  }
  try
  {
    cut_subj(&subs, count);
  }
  catch (...)
  {
    delete[] subs;
    throw;
  }
  r = count;
  return subs;
}

int main()
{
}