#include "func.hpp"
// #include <iostream>
// #include <fstream>
// #include <set>
// #include <limits>
#include "types.hpp"
// #include "stack.hpp"
// #include "queue.hpp"

void mihalchenko::printedResult(std::ostream &out, Stack<long long> &stack, size_t &num)
{
  for (size_t i = 0; i < num; i++)
  {
    out << stack.pop();
    if (i != num - 1)
    {
      out << " ";
    }
  }
  out << std::endl;
}

size_t mihalchenko::calculatePostFix(Queue<std::string> &resiveDigit, Stack<long long> &calculateResult)
{
  finalTransform finTrans;
  std::set<char> controlSet{'(', ')', '+', '-', '*', '/', '%'};
  // bool flgStart = false;
  long long llMax = std::numeric_limits<long long>::max();
  long long i = resiveDigit.getSize();
  while ((i > 0) && (i != llMax))
  {
    if (!controlSet.count(resiveDigit.watch(i - 1)[0]))
    {
      finTrans.calcRezult.push(stoll(resiveDigit.watch(i - 1))); // копирую числа из очереди в суперстек из чисел
      finTrans.commands.push('.');
    }
    else
    {
      finTrans.commands.push(resiveDigit.watch(i - 1)[0]); // копирую команду из очереди в стек
    }
    i = i - 1;
  }

  if (!finTrans.calculate())
  {
    return llMax;
  }

  if (finTrans.calcRezult.getSize() > 0)
  {
    // std::cout << "!!!" << finTrans.calcRezult.watch(0).resultCalc << std::endl;
    calculateResult.push(finTrans.calcRezult.watch(0).resultCalc);
  }
  resiveDigit.clear();
  resiveDigit.size_ = 0;
  return calculateResult.getSize();
}

bool mihalchenko::bildStrPostFix(std::string &currentStr, size_t currentStrSize, Queue<std::string> &resiveDigit, Stack<std::string> &resiveControl)
{
  // с помощью стека и очереди формирую постфиксную запись выражения В ОЧЕРЕДИ
  size_t ullMax = std::numeric_limits<size_t>::max();
  if (resiveControl.size_ == ullMax)
  {
    resiveControl.size_ = 0;
  }
  bool flgResult = true;
  size_t i = 0;
  std::string elementStr; // элемент строки, текст между пробелами
  std::string prewCommand = "";
  int counterSc = 0;
  while (i < currentStrSize) // Анализ текущей строки - перебираем элементы строки, разделенные пробелом
  {
    size_t posWhite = currentStr.find(' ');                // позиция символа, где встретился пробел(индекс начинается с 1)
    if ((posWhite > 0) && (posWhite != std::string::npos)) // проверка, найден ли пробел
    {
      elementStr = currentStr.substr(0, posWhite); // выделить из строки s подстроку, начинающуюся с позиции i, длиной l символов
      currentStr.erase(0, posWhite + 1);
      i += posWhite + 1; // увеличиваем счетчик количества обработанных символов в строке(не забываем по пробел)
    }
    else
    {
      if (currentStr.find(' ') <= currentStr.size())
      {
        elementStr = "";
        currentStr.erase(0, 1);
        i++;
      }
      else // делаем вывод, что все что осталось в строке, это число
      {
        elementStr = currentStr;
        i += currentStr.size();
      }
    }
    if (elementStr.size() > 0)
    {
      std::set<char> controlSet1{'(', ')', '+', '-', '*', '/', '%'};
      if ((elementStr.size() == 1) && (controlSet1.count(elementStr[0]))) // если это знак операции или скобки
      {
        if (elementStr[0] == ')')
        {
          counterSc = counterSc - 1;
          std::string strFS;
          do
          {
            if ((resiveControl.getSize() == 0) || (resiveControl.getSize() == ullMax))
            {
              std::cout << "ЛОГИКА НАРУШЕНА" << std::endl;
              flgResult = false;
            }
            strFS = resiveControl.pop(); // вынимаем из стека очередной символ
            if (strFS != "(")            // если из стека вытащили не "("
            {
              resiveDigit.push(strFS); // Сохраняем принятый символ в очередь
            }
          } while ((strFS[0] != '(') && (resiveControl.getSize() > 0));
        }
        else if ((prewCommand == "(") || (elementStr[0] == '('))
        {
          resiveControl.push(elementStr); // Сохраняем принятый символ в стек
          if (elementStr[0] == '(')
          {
            counterSc = counterSc + 1;
          }
        }
        else
        {
          if ((resiveControl.getSize() > 0) && (resiveControl.getSize() != ullMax))
          {
            resiveDigit.push(resiveControl.pop()); // Выгружаем из стека крайнюю команду в очередь.
          }
          resiveControl.push(elementStr); // Сохраняем принятый символ в стек
        }
        prewCommand = elementStr;
      }
      else
      {
        resiveDigit.push(elementStr); // Сохраняем принятый символ в очередь
      }
    }
    else
    {
      std::cerr << "ЛОГИКА НАРУШЕНА" << std::endl;
      flgResult = false;
    }
  }
  if (counterSc != 0)
  {
    std::cerr << "количество скобок не бьется" << std::endl;
    flgResult = false;
  }
  while ((resiveControl.getSize() > 0) && (resiveControl.getSize() != ullMax))
  {
    resiveDigit.push(resiveControl.pop()); // Выгружаем из стека в очередь. Получилась постфиксная запись выражения
  }
  return flgResult;
}
