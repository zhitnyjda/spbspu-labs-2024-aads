#include <iostream>
#include <fstream>
#include <string>
// #include <iomanip>
// #include <limits>
#include "queue.hpp"
#include "stack.hpp"
#include <set>
// #include <utility>
// #include <cctype>
// #include <locale>
// #include "delimiters.hpp"

using namespace mihalchenko;

int main(int argc, char *argv[])
{
  std::cout << "Hello World" << std::endl;
  std::set<int> numbers{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i = 0; i < argc; i++)
  {
    // Выводим список аргументов в цикле
    std::cout << "Argument " << i << " : " << argv[i] << std::endl;
  }

  Queue<std::string> resiveDigit;
  Stack<std::string> resiveControl;

  if (argc == 1)
  {
    std::cout << "Программа запущена без параметров командной строки. Берем данные из консоли" << std::endl;
    /*while (!std::cin.eof())
    {
      std::copy(
        std::istream_iterator<mihalchenko::DataStruct>{std::cin},
        std::istream_iterator<mihalchenko::DataStruct>{},
        std::back_inserter(dataStruct));
      if (std::cin.fail() && !std::cin.eof())
      {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }  */
    std::string elementStr;
    while (std::getline(std::cin, elementStr, ' '))
    {
      // std::cout << "elementStr =" << elementStr << std::endl;
      if (elementStr.length() > 0)
      {
        // std::cout << "elementStr =" << elementStr << std::endl;
        if ((isdigit(elementStr[0])) && (numbers.count(stoi(elementStr)))) //(numbers.contains(elementStr)))
        // if (numbers.count(stoi(elementStr)))
        {
          resiveDigit.push(elementStr); // Сохраняем принятый символ в очередь
          std::cout << "Сохраняем принятый символ " << elementStr << " в очередь" << std::endl;
        }
        else
        {
          // resiveControl.push(elementStr); //Сохраняем принятый символ в стек
          std::cout << "Сохраняем принятый символ " << elementStr << " в стек" << std::endl;
        }
        // std::cout << "Сохраняем принятый символ " << std::endl;
      }
    }
  }
  else if (argc == 2)
  {
    std::cout << "При запуске указано имя файла. Берем данные из файла" << std::endl;
    std::string elementStr;
    std::ifstream inputFF;
    inputFF.open(argv[1]);
    // inputFF.open("F:\\input.txt");
    std::cout << "Открыли файл на чтение" << std::endl;
    // std::getline(inputFF, elementStr);
    // std::cout << "elementStr =" << elementStr << std::endl;
    while (std::getline(inputFF, elementStr, ' '))
    {
      std::cout << "Читаем из файла" << std::endl;
      if (elementStr.length() > 0)
      {
        resiveDigit.push(elementStr);
        std::cout << "Сохраняем принятый символ в очередь" << std::endl;
      }
    }
    inputFF.close();
  }
  else
  {
    std::cerr << "Error: wrong input!";
    return 1;
  }

  std::cout << "Good By World" << std::endl;
  return 0;
}
