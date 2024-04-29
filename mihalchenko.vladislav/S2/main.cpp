#include <iostream>
#include <fstream>
#include <string>
// #include <iomanip>
// #include <limits>
#include "stack.hpp"
#include "queue.hpp"
#include <set>
// #include <utility>
// #include <cctype>
// #include <locale>
// #include "delimiters.hpp"

using namespace mihalchenko;

int main(int argc, char *argv[])
{
  std::cout << "Hello World" << std::endl;
  std::set<int> numberSet{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::set<char> controlSet{'(', ')', '+', '-', '*', '/', '%'};
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
    std::string str(1, '(');
    std::string strFS;
    while (std::getline(std::cin, elementStr, ' '))
    {
      if (elementStr.length() > 0)
      {
        if ((elementStr.size() == 1) && (controlSet.count(elementStr[0]))) // если это знак операции или скобки
        {
          if (elementStr[0] == ')')
          {
            // std::string str(1, '(');
            // std::string strFS;
            std::cout << "встретилась закрывающая скобка " << elementStr << std::endl;
            do
            {
              // str = elementStr;//std::to_string(resiveControl.pop());  //вынимаем из стека очередной символ
              strFS = resiveControl.pop(); // вынимаем из стека очередной символ
              if (strFS != str)            // если из стека вытащили не "("
              {
                // resiveDigit.push(resiveControl.pop()); //Сохраняем принятый символ в очередь
                resiveDigit.push(strFS); // Сохраняем принятый символ в очередь
                std::cout << "Сохраняем символ " << strFS << " из стека в очередь" << std::endl;
              }
            } while (!(strFS[0] == '(') && !(resiveControl.size_ == 0));
            std::cout << "strFS = " << strFS << std::endl;
          }
          else
          {
            resiveControl.push(elementStr); // Сохраняем принятый символ в стек
            std::cout << "Сохраняем принятый символ " << elementStr << " в стек" << std::endl;
          }
        }
        else
        {
          resiveDigit.push(elementStr); // Сохраняем принятый символ в очередь
          std::cout << "Сохраняем принятый символ " << elementStr << " в очередь" << std::endl;
        }
      }
    }
    resiveDigit.push(resiveControl.pop()); // Выгружаем из стека крайнюю команду в очередь. Получилась постфиксная запись выражения
    // std::cout << "Выгружаем из стека крайнюю команду " << strFS << " в очередь" << std::endl;
    std::cout << "Выгружаем из стека крайнюю команду в очередь" << std::endl;
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

  // if ((isdigit(elementStr[0]))
  // if (numbers.count(stoi(elementStr)))

  size_t num = resiveDigit.size_;
  for (size_t i = 0; i < num; i++)
  {
    std::cout << resiveDigit.pop();
    if (i != num - 1)
    {
      std::cout << " ";
    }
  }
  std::cout << std::endl;

  std::cout << "Good By World" << std::endl;
  return 0;
}
