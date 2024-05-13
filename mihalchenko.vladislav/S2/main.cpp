#include <iostream>
#include <fstream>
#include <set>
#include <limits>
#include <cctype>
// #include "stack.hpp"
// #include "queue.hpp"
// #include "list.hpp"
#include "func.hpp"

using namespace mihalchenko;

int main(int argc, char *argv[])
{
  std::set<char> controlSet{'(', ')', '+', '-', '*', '/', '%'};
  Queue<std::string> resiveDigit;
  Stack<std::string> resiveControl;
  Stack<long long> calculateResult;
  // size_t ullMax = std::numeric_limits<size_t>::max();
  size_t llMax = std::numeric_limits<long long>::max();

  std::string currentStr; // вся текущая строка, считанная из консоли
  resiveControl.size_ = 0;
  calculateResult.size_ = 0;
  resiveDigit.size_ = 0;

  if (argc == 1) // Программа запущена без параметров командной строки. Берем данные из консоли
  {
    while (std::getline(std::cin, currentStr, '\n')) // Перебор всех строк из консоли - считываем всю строку сразу
    {
      try
      {
        if (!bildStrPostFix(currentStr, currentStr.size(), resiveDigit, resiveControl))
        {
          std::cerr << "Ошибка входных данных!\n";
          return 1;
        }
        calculateResult.size_ = calculatePostFix(resiveDigit, calculateResult);
        if (calculateResult.getSize() == llMax)
        {
          return 1;
        }
      }
      catch (...)
      {
        std::cerr << "Exception!\n";
        return 5;
      }
    }
  }
  else if (argc == 2)
  {
    std::ifstream inputFF;
    inputFF.open(argv[1]);
    while (std::getline(inputFF, currentStr, '\n'))
    {
      try
      {
        if (!bildStrPostFix(currentStr, currentStr.size(), resiveDigit, resiveControl))
        {
          std::cerr << "Ошибка входных данных!\n";
          return 1;
        }
        calculateResult.size_ = calculatePostFix(resiveDigit, calculateResult);
        if (calculateResult.getSize() == llMax)
        {
          return 1;
        }
      }
      catch (...)
      {
        std::cerr << "Exception!\n";
        return 3;
      }
    }
    inputFF.close();
  }
  else
  {
    std::cerr << "Error: wrong input!";
    return 1;
  }

  size_t num = calculateResult.getSize();
  printedResult(std::cout, calculateResult, num);
  return 0;
}
