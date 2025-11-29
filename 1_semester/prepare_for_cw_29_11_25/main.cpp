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

const size_t deps_count = 4;

const Stud **find_dep_dobs(const Subj &sub, int &dep, size_t &dobs, size_t min_visits)
{
  size_t *stud_dep_visiting = new size_t[deps_count]();
  size_t *stud_dep_classes_count = new size_t[deps_count]();
  // Записываем посещяемость всех студентов по кафедрам и общее количество часов для каждой кафедры.
  for (size_t i = 0; i < sub.people; i++)
  {
    stud_dep_classes_count[sub.studs[i]->dep] += sub.classes;
    stud_dep_visiting[sub.studs[i]->dep] += sub.visited[i];
  }
  size_t min_vis_number = 0;
  // Находим минимальную относительную посещяемость
  for (size_t i = 0; i < deps_count; i++)
  {
    if (stud_dep_visiting[min_vis_number] * stud_dep_classes_count[i] >
        stud_dep_classes_count[min_vis_number] * stud_dep_visiting[i])
    {
      min_vis_number = i;
    }
  }
  delete[] stud_dep_classes_count;
  delete[] stud_dep_visiting;
  dep = min_vis_number;
  size_t dobs_count = 0;
  // Считаем количество людей, не проходящих по посящемости по нижней границе
  for (size_t i = 0; i < sub.people; i++)
  {
    if (sub.studs[i]->dep == min_vis_number)
    {
      if (sub.visited[i] < min_visits)
      {
        dobs_count++;
      }
    }
  }
  const Stud **dobs_studs = new Stud *[dobs_count];
  size_t dobs_i = 0;
  dobs = dobs_count;
  // Записываем этих людей
  for (size_t i = 0; i < sub.people; i++)
  {
    if (sub.studs[i]->dep == min_vis_number)
    {
      if (sub.visited[i] < min_visits)
      {
        dobs_studs[dobs_i] = sub.studs[i];
        dobs_i++;
      }
    }
  }
  return dobs_studs;
}

int main()
{
}