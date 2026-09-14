#include <cmath>
#include <future>
#include <iostream>

#ifdef PROMISE
void task(std::promise< int > &&p)
{
  p.set_value(1);
}

int main()
{
  // Вычисляющая сторона promise
  std::promise< int > p;

  // ожидающая сторона future
  std::future< int > f = p.get_future();

  std::thread th(task, std::move(p));

  std::cout << f.get() << "\n";
  th.join();
}
#endif

#ifdef EXCEPTION

void task(std::promise< int > &&p)
{
  try
  {
    throw std::logic_error("fail to calc");
  }
  catch (...)
  {
    p.set_exception(std::current_exception());
  }
}

int main()
{
  std::promise< int > p;
  std::future< int > f = p.get_future();
  std::thread th(task, std::move(p));

  try
  {
    std::cout << f.get() << "\n";
  }
  catch (const std::exception &e)
  {
    std::cout << e.what() << "\n";
  }

  th.join();
}

#endif

#ifdef GENERATE_EXCEPTION
void task(std::promise< int > &&p)
{
  p.set_exception(std::make_exception_ptr(std::logic_error("fail to calc with logic error")));
}

int main()
{
  std::promise< int > p;
  std::future< int > f = p.get_future();
  std::thread th(task, std::move(p));

  try
  {
    std::cout << f.get() << "\n";
  }
  catch (const std::exception &e)
  {
    std::cout << e.what() << "\n";
  }

  th.join();
}
#endif

#ifdef GENERATE_PROMISE_EXCEPTION
void task(std::promise< int > &&p)
{
}

int main()
{
  std::promise< int > p;
  std::future< int > f = p.get_future();
  std::thread th(task, std::move(p));

  try
  {
    std::cout << f.get() << "\n";
  }
  catch (const std::exception &e)
  {
    std::cout << e.what() << "\n";
  }

  th.join();
}
#endif

#ifdef DOUBLE_SET_VALUE
void task(std::promise< int > &&p)
{
  p.set_value(1);
  p.set_value(2);
}

int main()
{
  std::promise< int > p;
  std::future< int > f = p.get_future();
  std::thread th(task, std::move(p));

  try
  {
    std::cout << f.get() << "\n";
  }
  catch (const std::exception &e)
  {
    std::cout << e.what() << "\n";
  }

  th.join();
}
#endif

#ifdef SHARED_FUTURE
void task(std::shared_future< int > shf)
{
  std::cout << shf.get() + shf.get() << "\n";
}

int main()
{
  constexpr size_t size = 1'000'000'000;
  std::promise< int > p;
  std::shared_future< int > f(p.get_future());
  std::thread th1(task, f);
  std::thread th2(task, f);
  p.set_value(1);
  th1.join();
  th2.join();

  return 0;
}
#endif
