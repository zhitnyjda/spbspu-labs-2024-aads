#include "func.hpp"
#include <iostream>
#include <fstream>
#include <set>
#include <limits>
#include "types.hpp"

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
// size_t mihalchenko::calculatePostFix(Queue<std::string> &resiveDigit, Stack<long long> &calculateResult, Stack<CalcRez> &calcRezult)
{
  Stack<CalcRez> calcRezult;
  std::set<char> controlSet{'(', ')', '+', '-', '*', '/', '%'};
  bool flgStart = false;
  while (resiveDigit.getSize() > 0)
  {
    if ((resiveDigit.getSize() > 3) && (!controlSet.count(resiveDigit.watch(0)[0])) && (!controlSet.count(resiveDigit.watch(1)[0])) && (!controlSet.count(resiveDigit.watch(2)[0])) && (controlSet.count(resiveDigit.watch(3)[0])))
    {
      flgStart = true;
      calculateResult.push(stoll(resiveDigit.pop())); // фиксирую сюда первый элемент очереди
      calculateResult.push(bildOperation(stoll(resiveDigit.pop()), stoll(resiveDigit.pop()), resiveDigit.watch(2)[0]));
      // calcRezult.push(stoll(resiveDigit.pop()) + stoll(resiveDigit.pop()));
      // calcRezult.push(stoll(resiveDigit.pop()));
      calcRezult.push(1000000);
      std::cout << calcRezult.pop().resultCalc << std::endl;
      resiveDigit.pop(); // просто очищаем очередь от выполненной команды
    }
    else if ((resiveDigit.getSize() > 2) && (!controlSet.count(resiveDigit.watch(0)[0])) && (!controlSet.count(resiveDigit.watch(1)[0])) && (controlSet.count(resiveDigit.watch(2)[0])))
    {
      flgStart = true;
      calculateResult.push(bildOperation(stoll(resiveDigit.pop()), stoll(resiveDigit.pop()), resiveDigit.watch(2)[0]));
      resiveDigit.pop(); // просто очищаем очередь от выполненной команды
    }
    else if ((flgStart) && (resiveDigit.getSize() > 1) && (!controlSet.count(resiveDigit.watch(0)[0])) && (controlSet.count(resiveDigit.watch(1)[0])))
    {
      calculateResult.push(bildOperation(stoll(resiveDigit.pop()), calculateResult.pop(), resiveDigit.watch(1)[0]));
      resiveDigit.pop(); // просто очищаем очередь от выполненной команды
    }
    else if ((flgStart) && (resiveDigit.getSize() > 0) && (calculateResult.getSize() > 1) && (controlSet.count(resiveDigit.watch(0)[0])))
    {
      long long wrem = calculateResult.pop();
      calculateResult.push(bildOperation(wrem, calculateResult.pop(), resiveDigit.watch(0)[0]));
      resiveDigit.pop(); // просто очищаем очередь от выполненной команды
    }
    else if ((!flgStart) && (resiveDigit.getSize() > 0) && (calculateResult.getSize() == 0) && (!controlSet.count(resiveDigit.watch(0)[0])))
    {
      calculateResult.push(stoll(resiveDigit.pop()));
    }
    else if ((!flgStart) && (resiveDigit.getSize() > 0) && (calculateResult.getSize() == 0))
    {
      std::string strV = resiveDigit.pop();
      if (strV[0] == '(')
      {
        strV.erase(0, 1);
      }
      if (strV.find(')'))
      {
        strV.erase(strV.find(')'), 1);
      }
      calculateResult.push(stoll(strV));
    }
    else
    {
      std::cerr << "Ошибка входных данных!\n";
      return std::numeric_limits<long long>::max();
    }
  }
  resiveDigit.clear();
  return calculateResult.getSize();
}

long long mihalchenko::bildOperation(long long operandOne, long long operandTwo, char operation)
{
  long long llMax = std::numeric_limits<long long>::max();
  long long resultVal;
  switch (operation)
  {
  case '+':
    if (llMax - operandTwo >= operandOne)
    {
      resultVal = operandTwo + operandOne;
    }
    else
    {
      std::cerr << "Переполнение!\n";
      return llMax;
    }
    break;
  case '-':
    resultVal = operandTwo - operandOne;
    break;
  case '*':
    if (llMax / operandOne >= operandTwo)
    {
      resultVal = operandTwo * operandOne;
    }
    else
    {
      std::cerr << "Переполнение!\n";
      return llMax;
    }
    break;
  case '/':
    resultVal = operandTwo / operandOne;
    break;
  case '%':
    if (operandOne < 0)
    {
      resultVal = abs((operandOne / operandTwo - 1) * operandTwo - operandOne);
    }
    else
      resultVal = operandTwo % operandOne;
    break;
  }
  return resultVal;
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
  return flgResult;
}
