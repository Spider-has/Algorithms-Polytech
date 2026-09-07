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
