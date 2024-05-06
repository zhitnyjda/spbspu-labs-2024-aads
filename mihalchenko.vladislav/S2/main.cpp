#include <iostream>
#include <fstream>
#include <set>
// #include <stdexcept>
#include <limits>
#include "stack.hpp"
#include "queue.hpp"
#include "list.hpp"
#include "func.hpp"
// #include "stack.hpp"

using namespace mihalchenko;

int main(int argc, char *argv[])
{
  std::set<char> controlSet{'(', ')', '+', '-', '*', '/', '%'};
  Queue<std::string> resiveDigit;
  // Queue<std::string> queueWrem;
  Stack<std::string> resiveControl;
  Stack<long long> calculateResult;
  // Stack<CalcRez> calcRezult;
  size_t ullMax = std::numeric_limits<size_t>::max();
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
          std::cerr << "Ошиюка входных данных!\n";
          return 1;
        }
        while ((resiveControl.getSize() > 0) && (resiveControl.getSize() != ullMax))
        {
          resiveDigit.push(resiveControl.pop()); // Выгружаем из стека в очередь. Получилась постфиксная запись выражения
        }
        // queueWrem = resiveDigit;
        // queueWrem.size_ = resiveDigit.size_;
        // calculateResult.size_ = calculatePostFix(resiveDigit, calculateResult, calcRezult);
        calculateResult.size_ = calculatePostFix(resiveDigit, calculateResult);
        if (calculateResult.getSize() == llMax)
        {
          return 1;
        }
        resiveDigit.clear();
        resiveDigit.size_ = 0;

        // size_t num = queueWrem.size_;
        // printedQueuePostFix(std::cout, queueWrem, num);
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
          std::cerr << "Ошиюка входных данных!\n";
          return 1;
        }
        while ((resiveControl.getSize() > 0) && (resiveControl.getSize() != ullMax))
        {
          resiveDigit.push(resiveControl.pop()); // Выгружаем из стека в очередь. Получилась постфиксная запись выражения
        }
        // calculateResult.size_ = calculatePostFix(resiveDigit, calculateResult, calcRezult);
        calculateResult.size_ = calculatePostFix(resiveDigit, calculateResult);
        if (calculateResult.getSize() == llMax)
        {
          return 1;
        }
        resiveDigit.clear();
        resiveDigit.size_ = 0;
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
