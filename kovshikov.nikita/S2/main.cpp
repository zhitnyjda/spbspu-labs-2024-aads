#include <iostream>
#include "stack.hpp"
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
  Stack< int > stack1;
  std::cout << "start\n";
  stack1.push(2);
  stack1.push(5);
  stack1.push(29);
  std::cout << stack1.getSize() << "\n";
  std::cout << stack1.isEmpty() << "\n";
  Stack< int > stack2(stack1);
  for(int i = 0; i < 3; i++)
  {
    std::cout << stack2.top() << "\n";
    stack2.pop();
  }
  for(int i = 0; i < 3; i++)
  {
    std::cout << stack1.top() << "\n";
    stack1.pop();
  }
  std::cout << stack1.isEmpty() << "\n";
}
