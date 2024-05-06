#include <iostream>
#include "queue.hpp"
#include "stack.hpp"
#include "read.hpp"
#include <cstring>
#include <fstream>

int main(int argc, char ** argv)
{
  using namespace kovshikov;
  Queue< std::string > allData; //очередь в которой элементом является арифмитическое выражение
  if(argc == 1)
  {
    readData(std::cin, allData);
  }
  else if(argc == 2)
  {
    std::ifstream file(argv[1]);
    readData(file, allData);
    size_t size = allData.getSize();
    for(size_t i = 0; i < size; i++)
    {
      std::cout << allData.front() << "\n";
      allData.pop();
    }
    // работаем с потоком ввода вывода из файла
    // считываем данные из файла, вносим в стек/очередь, какая-то функция
  }
}
