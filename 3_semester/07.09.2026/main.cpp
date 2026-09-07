#include <iostream>
#include <thread>

void out()
{
  for (size_t i = 0; i < 10; ++i)
  {
    std::cout << i << "\n"; // static storage
  }
}

#ifdef JOIN
int main()
{
  std::cout << "join" << "\n";
  std::thread th1(out); // automatic memory
  try
  {
    for (size_t i = 0; i < 10; ++i)
    {
      std::cout << "main: " << i << "\n"; // static storage
    }
  }
  catch (...)
  {
    th1.join(); // если не вызывать join, деструктор вызовется преждевременно и дропается исключение
    return 1;
  }
  th1.join(); // join ждет пока поток завершится в потоке программы. По сути async / await
}
#endif

#ifdef DETACH
int main()
{
  std::cout << "detach: " << "\n";
  std::thread th1(out); // automatic memory
  th1.detach();
  for (size_t i = 0; i < 10; ++i)
  {
    std::cout << "main: " << i << "\n"; // static storage
  }
}
#endif

#ifdef ARG
void outArg(const char *s, std::ostream &os)
{
  (os) << s;
}

int main()
{
  std::thread th(outArg, "Hi, bro!\n", std::ref(std::cout));
  th.join();
}
#endif

#ifdef RETURNING
#include <future>

bool outReturn(const char *s, std::ostream &os)
{
  (os) << s;
  return os.fail();
}

int main()
{
  std::future< bool > ft = std::async(std::launch::async, outReturn, "Hi\n", std::ref(std::cout));
  std::cout << "is future failed: " << ft.get() << "\n";
}
#endif

#ifdef HOMEWORK

#include <future>
#include <random>
#include <vector>

bool isInside(double x, double y, double r)
{
  return ((x - r) * (x - r)) + ((y - r) * (y - r)) <= r * r;
}

size_t calc(double r, size_t tests, size_t seed)
{
  std::default_random_engine engine(seed);

  std::uniform_real_distribution< double > dist(0.0, 2 * r);
  size_t succed = 0;
  for (size_t i = 0; i < tests; ++i)
  {
    succed += isInside(dist(engine), dist(engine), r);
  }
  return succed;
}

double area(double r, size_t thread, size_t tests)
{
  std::vector< std::future< size_t > > threads_vec;

  size_t n = tests / thread;
  size_t mod = tests % thread;
  for (size_t i = 0; i < thread - 1; ++i)
  {
    threads_vec.emplace_back(std::async(std::launch::async, calc, r, n, i));
  }
  threads_vec.emplace_back(std::async(std::launch::async, calc, r, n, thread));
  size_t success = 0;
  for (size_t i = 0; i < thread; ++i)
  {
    success += threads_vec[i].get();
  }
  std::cout << success << "\n";
  return (double(success) / double(tests)) * (4 * r);
}

int main()
{
  std::cout << area(1, 4, 100000000) << "\n";
  return 0;
}

#endif
