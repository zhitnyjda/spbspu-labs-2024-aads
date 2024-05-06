#include <iostream>
#include "queue.hpp"
/*int main(int argc, char ** argv)
{
  if(argc == 1)
  {
    // работаем с потоком ввода вывода из терминала
  }
  else if(argc == 2)
  {
    // работаем с потоком ввода вывода из файла
  }
}*/

int main()
{
  using namespace kovshikov;
  Queue< int > queue1;
  std::cout << "start\n";
  queue1.push(2);
  queue1.push(5);
  queue1.push(29);
  std::cout << queue1.getSize() << "\n";
  std::cout << queue1.isEmpty() << "\n";
  Queue< int > queue2(queue1);
  for(int i = 0; i < 3; i++)
  {
    std::cout << queue2.back() << "\n";
    std::cout << queue2.front() << "\n";
    queue2.pop();
  }
  for(int i = 0; i < 3; i++)
  {
    std::cout << queue1.back() << "\n";
    std::cout << queue1.front() << "\n";
    queue1.pop();
  }
  std::cout << queue1.isEmpty() << "\n";
}
