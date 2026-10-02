#include <atomic>
#include <chrono>
#include <csignal>
#include <iostream>
#include <thread>

std::atomic< bool > keep_running(true);

void signal_handler(int signal_num)
{
  if (signal_num == SIGINT)
  {
    std::cout << "\n[Сигнал] Получен Ctrl + C (SIGINT). Завершаем работу...\n";
    keep_running = false;
  }
}

int main()
{
  std::signal(SIGINT, signal_handler);

  std::cout << "Программа запущена. Нажмите Ctrl + C для выхода." << "\n";

  while (keep_running)
  {
    std::cout << "Работаю... " << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  // Здесь выполняем очистку ресурсов
  std::cout << "Ресурсы очищены. Программа успешно завершена." << "\n";

  return 0;
}
