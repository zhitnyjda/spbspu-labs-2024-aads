#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "stack.hpp"
#include "queue.hpp"
// #include "funcS2.hpp"

using namespace mihalchenko;

void printedResult(std::ostream &out, Stack<double> &calcRes, size_t &num);
void printedQueuePostFix(std::ostream &out, Queue<std::string> &queue, size_t &num);
size_t CalculatePostFix(std::ostream &out, Queue<std::string> &resiveDigit, Stack<double> &calculateResult, size_t &resiveDigitSize, size_t &stackSize);

int main(int argc, char *argv[])
{
  std::set<char> controlSet{'(', ')', '+', '-', '*', '/', '%'};
  /*  for (int i = 0; i < argc; i++)
    {
      // Выводим список аргументов в цикле
      std::cout << "Argument " << i << " : " << argv[i] << std::endl;
    }
   */
  Queue<std::string> resiveDigit;
  Queue<std::string> queueWrem;
  Stack<std::string> resiveControl;
  Stack<double> calculateResult;

  if (argc == 1) // Программа запущена без параметров командной строки. Берем данные из консоли
  {
    std::string elementStr;
    std::string currentStr;
    std::string str(1, '(');
    std::string strFS;
    while (std::getline(std::cin, currentStr, '\n')) // Перебор всех строк из консоли - считываем всю строку сразу
    {
      Queue<std::string> resiveDigit;
      Stack<std::string> resiveControl;
      int posWhite;
      size_t wremCountLenStr = currentStr.size();
      std::string prewCommand = "";
      int i = 0;
      while (i < wremCountLenStr) // Анализ текущей строки - перебираем элементы строки, разделенные пробелом
      {
        posWhite = currentStr.find(' '); // позиция символа, где встретился пробел(индекс начинается с 1)
        if (posWhite > 0)                // проверка, найден ли пробел
        {
          // выделить из строки s подстроку, начинающуюся с позиции i, длиной l символов, можно при помощи вызова s.substr(i, l)
          elementStr = currentStr.substr(0, posWhite);
          currentStr.erase(0, posWhite);
          i += posWhite; // увеличиваем счетчик количества обработанных символов в строке(не забываем по пробел)
        }
        else
        {
          std::size_t found = currentStr.find(' ');

          if (found <= currentStr.size())
          {
            // std::cout << "Самый первый символ в строке  currentStr  - пробел " << currentStr << std::endl;
            elementStr = "";
            currentStr.erase(0, 1);
            i++;
          }
          else // делаем вывод, что все что осталось в строке, это число
          {
            elementStr = currentStr;
            i += currentStr.size();
            // std::cout << "Строка закончилась. Крайний элемент справа =" << elementStr << "posWhite=" << posWhite << "i=" << i <<std::endl;
          }
        }
        if (elementStr.size() > 0) // length()
        {
          if ((elementStr.size() == 1) && (controlSet.count(elementStr[0]))) // если это знак операции или скобки
          {
            if (elementStr[0] == ')')
            {
              // std::cout << "встретилась закрывающая скобка:" << elementStr << std::endl;
              do
              {
                strFS = resiveControl.pop(); // вынимаем из стека очередной символ
                if (strFS != str)            // если из стека вытащили не "("
                {
                  resiveDigit.push(strFS); // Сохраняем принятый символ в очередь
                  // std::cout << "Сохраняем символ " << strFS << " из стека в очередь" << std::endl;
                }
              } while (!(strFS[0] == '(') && !(resiveControl.size_ == 0));
              // std::cout << "strFS = " << strFS << std::endl;
            }
            else if (((prewCommand == "+") || (prewCommand == "-")) && ((elementStr[0] == '+') || (elementStr[0] == '-')))
            {
              resiveDigit.push(resiveControl.pop()); // Выгружаем из стека крайнюю команду в очередь.
              resiveControl.push(elementStr);        // Сохраняем принятый символ в стек
              // std::cout << "Сохраняем принятый символ " << elementStr << " в стек +-*/" << std::endl;
            }
            else if (((prewCommand == "*") || (prewCommand == "/")) && ((elementStr[0] == '*') || (elementStr[0] == '/')))
            {
              resiveDigit.push(resiveControl.pop()); // Выгружаем из стека крайнюю команду в очередь.
              resiveControl.push(elementStr);        // Сохраняем принятый символ в стек
            }
            else
            {
              resiveControl.push(elementStr); // Сохраняем принятый символ в стек
              // std::cout << "Сохраняем принятый символ " << elementStr << " в стек" << std::endl;
            }
            prewCommand = elementStr;
          }
          else
          {
            resiveDigit.push(elementStr); // Сохраняем принятый символ в очередь
          }
        }
      }
      resiveDigit.push(resiveControl.pop()); // Выгружаем из стека крайнюю команду в очередь. Получилась постфиксная запись выражения

      queueWrem = resiveDigit;
      queueWrem.size_ = resiveDigit.size_;

      calculateResult.size_ = CalculatePostFix(std::cout, resiveDigit, calculateResult, resiveDigit.size_, calculateResult.size_);

      // resiveDigit.clear();
      resiveDigit.size_ = 0;

      size_t num = queueWrem.size_;
      printedQueuePostFix(std::cout, queueWrem, num);
    }
  }
  else if (argc == 2)
  {
    std::cout << "При запуске указано имя файла. Берем данные из файла" << std::endl;
    std::string elementStr;
    std::ifstream inputFF;
    inputFF.open(argv[1]);
    std::cout << "Открыли файл на чтение" << std::endl;
    while (std::getline(inputFF, elementStr, ' '))
    {
      Queue<std::string> resiveDigit;
      Stack<std::string> resiveControl;
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

  size_t num = calculateResult.size_;
  printedResult(std::cout, calculateResult, num);

  return 0;
}

// функции программы
void printedResult(std::ostream &out, Stack<double> &calcRes, size_t &num)
{
  for (size_t i = 0; i < num; i++)
  {
    out << calcRes.pop();
    if (i != num - 1)
    {
      out << " ";
    }
  }
  out << std::endl;
}

void printedQueuePostFix(std::ostream &out, Queue<std::string> &queue, size_t &num)
{
  for (size_t i = 0; i < num; i++)
  {
    out << queue.pop();
    if (i != num - 1)
    {
      out << " ";
    }
  }
  out << std::endl;
}

size_t CalculatePostFix(std::ostream &out, Queue<std::string> &resiveDigit, Stack<double> &calculateResult, size_t &resiveDigitSize, size_t &stackSize)
{
  std::set<char> controlSet{'(', ')', '+', '-', '*', '/', '%'};
  double resultVal = 0.0;

  resiveDigit.size_ = resiveDigitSize;
  calculateResult.size_ = stackSize;

  bool flgStart = false;
  while (resiveDigit.size_ > 0)
  {
    // out << "!!!!!!!! while !!!!!!!!!!! resiveDigit.size_ >0 " << resiveDigit.size_ << std::endl;
    if ((!controlSet.count(resiveDigit.watch(0)[0])) && (!controlSet.count(resiveDigit.watch(1)[0])) && (controlSet.count(resiveDigit.watch(2)[0])))
    {
      flgStart = true;
      switch (resiveDigit.watch(2)[0])
      {
      case '+':
        resultVal = stod(resiveDigit.pop()) + stod(resiveDigit.pop());
        break;
      case '-':
        resultVal = stod(resiveDigit.pop());
        resultVal = resultVal - stod(resiveDigit.pop());
        break;
      case '*':
        resultVal = stod(resiveDigit.pop()) * stod(resiveDigit.pop());
        break;
      case '/':
        resultVal = stod(resiveDigit.pop());
        resultVal = resultVal / stod(resiveDigit.pop());
        break;
      case '%':
        // resultVal = stod(resiveDigit.pop())
        // resultVal = stod(resiveDigit.pop()) % resultVal;
        break;
      }
      // out << "!!!!!!!!есть тройная команда !!!!!!!!!!! resiveDigit.size_ =" << resiveDigit.size_ << std::endl;
      calculateResult.push(resultVal);
      resiveDigit.pop(); // просто очищаем очередь от выполненной команды
      // out << "!!!!!!!!есть тройная команда2 !!!!!!!!!!! resiveDigit.size_ =" << resiveDigit.size_ << std::endl;
    }
    else if ((flgStart) && (!controlSet.count(resiveDigit.watch(0)[0])) && (controlSet.count(resiveDigit.watch(1)[0])))
    {
      switch (resiveDigit.watch(1)[0])
      {
      case '+':
        resultVal = calculateResult.pop() + stod(resiveDigit.pop());
        break;
      case '-':
        resultVal = calculateResult.pop() - stod(resiveDigit.pop());
        break;
      case '*':
        resultVal = calculateResult.pop() * stod(resiveDigit.pop());
        break;
      case '/':
        resultVal = calculateResult.pop() / stod(resiveDigit.pop());
        break;
      case '%':
        // resultVal = calculateResult.pop() % stod(resiveDigit.pop());
        break;
      }
      // out << "!!!!!!!!есть двойная команда !!!!!!!!!!! resultVal=" <<  resultVal << std::endl;
      calculateResult.push(resultVal);
      resiveDigit.pop(); // просто очищаем очередь от выполненной команды
    }
    else if ((flgStart) && (controlSet.count(resiveDigit.watch(0)[0])))
    {
      switch (resiveDigit.watch(0)[0])
      {
      case '+':
        resultVal = calculateResult.pop() + calculateResult.pop();
        break;
      case '-':
        resultVal = calculateResult.pop();
        resultVal = calculateResult.pop() - resultVal;
        break;
      case '*':
        resultVal = calculateResult.pop() * calculateResult.pop();
        break;
      case '/':
        resultVal = calculateResult.pop();
        resultVal = calculateResult.pop() / resultVal;
        break;
      case '%':
        // resultVal = calculateResult.pop() % calculateResult.pop());
        break;
      }
      // out << "!!!!!!!!есть деление!!!!!!!!!!! resultVal=" <<  resultVal << std::endl;
      calculateResult.push(resultVal);
      resiveDigit.pop(); // просто очищаем очередь от выполненной команды
    }
    else
    {
      out << "!!!!!!!!ERROR!!!!!!!!!!!" << std::endl;
      return 1;
    }
  }
  resiveDigit.clear();
  return calculateResult.size_;
}
