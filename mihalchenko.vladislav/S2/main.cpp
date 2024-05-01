#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <stdexcept>
#include <limits>
#include "stack.hpp"
#include "queue.hpp"
#include "list.hpp"
// #include "funcS2.hpp"

using namespace mihalchenko;

typedef struct
{
  size_t resiveDigitSize;
  size_t resiveControlSize;
  bool flgRezult;
} t_ret;

void printedResult(std::ostream &out, Stack<long long> &calcRes, size_t &num);
void printedQueuePostFix(std::ostream &out, Queue<std::string> &queue, size_t &num);
size_t CalculatePostFix(Queue<std::string> &resiveDigit, Stack<long long> &calculateResult, size_t &resiveDigitSize, size_t &stackSize);
// t_ret convertStr(std::ostream & out, std::string &currentStr, size_t currentStrSize, Queue < std::string > &resiveDigit, Stack < std::string > &resiveControl, size_t &resiveDigitSize, size_t &resiveControlSize);
t_ret convertStr(std::string &currentStr, size_t currentStrSize, Queue<std::string> &resiveDigit, Stack<std::string> &resiveControl, size_t &resiveDigitSize, size_t &resiveControlSize);

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
  Stack<long long> calculateResult;
  size_t ullMax = std::numeric_limits<size_t>::max();
  size_t llMax = std::numeric_limits<long long>::max();

  std::string currentStr; // вся текущая строка, считанная из консоли
  resiveControl.size_ = 0;
  calculateResult.size_ = 0;

  if (argc == 1) // Программа запущена без параметров командной строки. Берем данные из консоли
  {
    // std::cout << "Argument " << std::endl;
    while (std::getline(std::cin, currentStr, '\n')) // Перебор всех строк из консоли - считываем всю строку сразу
    {
      try
      {
        // auto P = convertStr(std::cout, currentStr, currentStr.size(), resiveDigit, resiveControl, resiveDigit.size_, resiveControl.size_);
        auto P = convertStr(currentStr, currentStr.size(), resiveDigit, resiveControl, resiveDigit.size_, resiveControl.size_);
        resiveDigit.size_ = P.resiveDigitSize;
        resiveControl.size_ = P.resiveControlSize;
        if (!P.flgRezult)
        {
          std::cerr << "Ошиюка входных данных!\n";
          return 1;
        }
        while ((resiveControl.size_ > 0) && (resiveControl.size_ != ullMax))
        {
          // std::cout << "7.ЧИТАЮ из Control и записываю ";
          std::string ttt = resiveControl.pop();
          resiveDigit.push(ttt); // Выгружаем из стека крайнюю команду в очередь. Получилась постфиксная запись выражения
          // std::cout << ttt << " в Digit" << " resiveControl.size_=" << resiveControl.size_ << std::endl;
        }
        // std::cout << " ===========resiveDigit.size_=" << resiveDigit.size_ << "=====================================" << std::endl;
        // queueWrem = resiveDigit;
        // queueWrem.size_ = resiveDigit.size_;
        // std::cout << " ===========resiveDigit.size_=" << resiveDigit.size_ << " queueWrem.size_=" << queueWrem.size_ << "=====================================" << std::endl;
        calculateResult.size_ = CalculatePostFix(resiveDigit, calculateResult, resiveDigit.size_, calculateResult.size_);
        // std::cout << " ===========calculateResult.size_=" << calculateResult.size_ << "llMax=" << llMax;
        if (calculateResult.size_ == llMax)
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
    // std::cout << "При запуске указано имя файла. Берем данные из файла" << std::endl;
    std::ifstream inputFF;
    inputFF.open(argv[1]);
    // inputFF.open("F:\\input.txt");
    // std::cout << "Открыли файл" << argv[1] << "на чтение" << std::endl;
    while (std::getline(inputFF, currentStr, '\n'))
    {
      try
      {
        // auto P = convertStr(std::cout, currentStr, currentStr.size(), resiveDigit, resiveControl, resiveDigit.size_, resiveControl.size_);
        auto P = convertStr(currentStr, currentStr.size(), resiveDigit, resiveControl, resiveDigit.size_, resiveControl.size_);
        resiveDigit.size_ = P.resiveDigitSize;
        resiveControl.size_ = P.resiveControlSize;
        if (!P.flgRezult)
        {
          std::cerr << "Ошиюка входных данных!\n";
          return 1;
        }
        while ((resiveControl.size_ > 0) && (resiveControl.size_ != ullMax))
        {
          // std::cout << "7.ЧИТАЮ из Control и записываю ";
          std::string ttt = resiveControl.pop();
          resiveDigit.push(ttt); // Выгружаем из стека крайнюю команду в очередь. Получилась постфиксная запись выражения
          // std::cout << ttt << " в Digit" << " resiveControl.size_=" << resiveControl.size_ << std::endl;
        }
        // std::cout << " ===========resiveDigit.size_=" << resiveDigit.size_ << "=====================================" << std::endl;
        // queueWrem = resiveDigit;
        // queueWrem.size_ = resiveDigit.size_;
        // std::cout << " ===========resiveDigit.size_=" << resiveDigit.size_ << " queueWrem.size_=" << queueWrem.size_ << "=====================================" << std::endl;
        calculateResult.size_ = CalculatePostFix(resiveDigit, calculateResult, resiveDigit.size_, calculateResult.size_);
        if (calculateResult.size_ == llMax)
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
        return 3;
      }
    }
    inputFF.close();
    // std::cout << "Error: нихрена не прочитал!" << std::endl;
  }
  else
  {
    std::cerr << "Error: wrong input!";
    return 1;
  }

  size_t num = calculateResult.size_;
  // std::cout << "calculateResult.size_=" << calculateResult.size_ << std::endl;
  printedResult(std::cout, calculateResult, num);

  return 0;
}

// ФУНКЦИИ программы
void printedResult(std::ostream &out, Stack<long long> &calcRes, size_t &num)
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

size_t CalculatePostFix(Queue<std::string> &resiveDigit, Stack<long long> &calculateResult, size_t &resiveDigitSize, size_t &stackSize)
{
  std::set<char> controlSet{'(', ')', '+', '-', '*', '/', '%'};
  long long resultVal = 0.0;
  long long wremVal = 0.0;
  long long llMax = std::numeric_limits<long long>::max();

  resiveDigit.size_ = resiveDigitSize;
  calculateResult.size_ = stackSize;

  bool flgStart = false;
  while (resiveDigit.size_ > 0)
  {
    if ((resiveDigit.size_ > 3) && (!controlSet.count(resiveDigit.watch(0)[0])) && (!controlSet.count(resiveDigit.watch(1)[0])) && (!controlSet.count(resiveDigit.watch(2)[0])) && (controlSet.count(resiveDigit.watch(3)[0])))
    {
      flgStart = true;
      calculateResult.push(stoll(resiveDigit.pop())); // фиксирую сюда первый элемент очереди
      switch (resiveDigit.watch(2)[0])
      {
      case '+':
        if (llMax - stoull(resiveDigit.watch(1)) >= stoull(resiveDigit.watch(0)))
        {
          resultVal = stoull(resiveDigit.pop()) + stoull(resiveDigit.pop());
          // out << resultVal << '\n';
        }
        else
        {
          std::cerr << "Переполнение!\n";
          return llMax;
        }
        break;
      case '-':
        resultVal = stoll(resiveDigit.pop());
        resultVal = resultVal - stoll(resiveDigit.pop());
        break;
      case '*':
        resultVal = stoll(resiveDigit.pop());
        wremVal = stoll(resiveDigit.pop());
        if (llMax / resultVal >= wremVal)
        {
          resultVal = resultVal * wremVal;
        }
        else
        {
          std::cerr << "Переполнение!\n";
          return llMax;
        }
        break;
      case '/':
        resultVal = stoll(resiveDigit.pop());
        resultVal = resultVal / stoll(resiveDigit.pop());
        break;
      case '%':
        resultVal = stoll(resiveDigit.pop());
        resultVal = stoll(resiveDigit.pop()) % resultVal;
        break;
      }
      calculateResult.push(resultVal);
      resiveDigit.pop(); // просто очищаем очередь от выполненной команды
      // resiveDigit.push(wremStr); //  возвращаю обратно
    }
    else if ((resiveDigit.size_ > 2) && (!controlSet.count(resiveDigit.watch(0)[0])) && (!controlSet.count(resiveDigit.watch(1)[0])) && (controlSet.count(resiveDigit.watch(2)[0])))
    {
      flgStart = true;
      switch (resiveDigit.watch(2)[0])
      {
      case '+':
        wremVal = stoll(resiveDigit.pop());
        resultVal = stoll(resiveDigit.pop());
        if (llMax - wremVal >= resultVal)
        {
          // out << "resultVal=" << resultVal << "wremVal= " << wremVal << '\n';
          resultVal = resultVal + wremVal;
          // out << resultVal << '\n';
        }
        else
        {
          std::cerr << "Переполнение!\n";
          return llMax;
        }
        break;
      case '-':
        resultVal = stoll(resiveDigit.pop());
        resultVal = resultVal - stoll(resiveDigit.pop());
        break;
      case '*':
        resultVal = stoll(resiveDigit.pop());
        wremVal = stoll(resiveDigit.pop());
        if (llMax / resultVal >= wremVal)
        {
          resultVal = resultVal * wremVal;
        }
        else
        {
          std::cerr << "Переполнение!\n";
          return llMax;
        }
        break;
      case '/':
        resultVal = stoll(resiveDigit.pop());
        resultVal = resultVal / stoll(resiveDigit.pop());
        break;
      case '%':
        resultVal = stoll(resiveDigit.pop());
        resultVal = stoll(resiveDigit.pop()) % resultVal;
        break;
      }
      calculateResult.push(resultVal);
      resiveDigit.pop(); // просто очищаем очередь от выполненной команды
    }
    else if ((flgStart) && (resiveDigit.size_ > 1) && (!controlSet.count(resiveDigit.watch(0)[0])) && (controlSet.count(resiveDigit.watch(1)[0])))
    {
      switch (resiveDigit.watch(1)[0])
      {
      case '+':
        resultVal = calculateResult.pop();
        if (llMax - resultVal >= stoll(resiveDigit.watch(0)))
        {
          resultVal = resultVal + stoll(resiveDigit.pop());
        }
        else
        {
          std::cerr << "Переполнение!\n";
          return llMax;
        }
        break;
      case '-':
        resultVal = calculateResult.pop() - stoll(resiveDigit.pop());
        break;
      case '*':
        resultVal = calculateResult.pop();
        wremVal = stoll(resiveDigit.pop());
        if (llMax / resultVal >= wremVal)
        {
          resultVal = resultVal * wremVal;
        }
        else
        {
          std::cerr << "Переполнение!\n";
          return llMax;
        }
        break;
      case '/':
        resultVal = calculateResult.pop() / stoll(resiveDigit.pop());
        break;
      case '%':
        resultVal = calculateResult.pop() % stoll(resiveDigit.pop());
        break;
      }
      calculateResult.push(resultVal);
      resiveDigit.pop(); // просто очищаем очередь от выполненной команды
    }
    else if ((flgStart) && (resiveDigit.size_ > 0) && (calculateResult.size_ > 1) && (controlSet.count(resiveDigit.watch(0)[0])))
    {
      switch (resiveDigit.watch(0)[0])
      {
      case '+':
        resultVal = calculateResult.pop();
        wremVal = calculateResult.pop();
        if (llMax - resultVal >= wremVal)
        {
          resultVal = resultVal + wremVal;
        }
        else
        {
          std::cerr << "Переполнение!\n";
          return llMax;
        }
        break;
      case '-':
        resultVal = calculateResult.pop();
        resultVal = calculateResult.pop() - resultVal;
        break;
      case '*':
        resultVal = calculateResult.pop();
        wremVal = calculateResult.pop();
        if (llMax / resultVal >= wremVal)
        {
          resultVal = resultVal * wremVal;
        }
        else
        {
          std::cerr << "Переполнение!\n";
          return llMax;
        }
        break;
      case '/':
        resultVal = calculateResult.pop();
        resultVal = calculateResult.pop() / resultVal;
        break;
      case '%':
        resultVal = calculateResult.pop();
        resultVal = calculateResult.pop() % resultVal;
        break;
      }
      calculateResult.push(resultVal);
      resiveDigit.pop(); // просто очищаем очередь от выполненной команды
    }
    else if ((!flgStart) && (resiveDigit.size_ > 0) && (calculateResult.size_ == 0) && (!controlSet.count(resiveDigit.watch(0)[0])))
    {
      calculateResult.push(stoll(resiveDigit.pop()));
    }
    else if ((!flgStart) && (resiveDigit.size_ > 0) && (calculateResult.size_ == 0))
    {
      std::string strV = resiveDigit.pop();
      // std::cout << strV << std::endl;
      if (strV[0] == '(')
      {
        strV.erase(0, 1);
      }
      // std::cout << strV << std::endl;
      if (strV.find(')'))
      {
        strV.erase(strV.find(')'), 1);
      }
      // std::cout << strV << std::endl;
      calculateResult.push(stoll(strV));
    }
    else
    {
      // std::cout << "flgStart=" << flgStart << " resiveDigit.size_=" << resiveDigit.size_ <<  " calculateResult.size_=" << calculateResult.size_ << " controlSet.count(resiveDigit.watch(0)[0])=" << controlSet.count(resiveDigit.watch(0)[0]) << "resiveDigit.watch(0)=" << resiveDigit.watch(0) << std::endl;
      // out << "!!!!!!!!ERROR!!!!!!!!!!!" << std::endl;
      std::cerr << "Ошибка входных данных!\n";
      return llMax;
    }
  }
  resiveDigit.clear();
  return calculateResult.size_;
}

// t_ret convertStr(std::ostream & out, std::string &currentStr, size_t currentStrSize, Queue < std::string > &resiveDigit, Stack < std::string > &resiveControl, size_t &resiveDigitSize, size_t &resiveControlSize)
t_ret convertStr(std::string &currentStr, size_t currentStrSize, Queue<std::string> &resiveDigit, Stack<std::string> &resiveControl, size_t &resiveDigitSize, size_t &resiveControlSize)
{
  resiveDigit.size_ = resiveDigitSize;
  resiveControl.size_ = resiveControlSize;
  std::string strFS;
  size_t posWhite;
  std::string elementStr; // элемент строки, текст между пробелами
  std::string str(1, '(');
  std::set<char> controlSet1{'(', ')', '+', '-', '*', '/', '%'};
  size_t wremCountLenStr = currentStrSize;
  std::string prewCommand = "";
  size_t i = 0;
  bool flgResult = true;
  size_t ullMax = std::numeric_limits<size_t>::max();

  // std::cout << "==============resiveControl.size_=" << resiveControl.size_ << "  resiveDigit.size_=" << resiveDigit.size_ <<  "================" << std::endl;
  if (resiveControl.size_ == ullMax)
  {
    resiveControl.size_ = 0;
  }

  while (i < wremCountLenStr) // Анализ текущей строки - перебираем элементы строки, разделенные пробелом
  {
    posWhite = currentStr.find(' ');                       // позиция символа, где встретился пробел(индекс начинается с 1)
    if ((posWhite > 0) && (posWhite != std::string::npos)) // проверка, найден ли пробел
    {
      // выделить из строки s подстроку, начинающуюся с позиции i, длиной l символов, можно при помощи вызова s.substr(i, l)
      elementStr = currentStr.substr(0, posWhite);
      currentStr.erase(0, posWhite + 1);
      // std::cout << "!!!!!!!!!!!!!!!!!!!test currentStr=" << currentStr << std::endl;
      i += posWhite + 1; // увеличиваем счетчик количества обработанных символов в строке(не забываем по пробел)
      // std::cout << "00elementStr=" << elementStr << "i=" << i << "posWhite=" << posWhite << std::endl;
      // std::cout << "==============считал следующий символ (до пробела) и удалил символ" << elementStr << "и пробел из исх.строки" << std::endl;
    }
    else
    {
      // std::cout << "==============пробел не найден)" << std::endl;
      std::size_t found = currentStr.find(' ');

      if (found <= currentStr.size())
      {
        // std::cout << "Самый первый символ в строке  currentStr  - пробел " << currentStr << std::endl;
        elementStr = "";
        currentStr.erase(0, 1);
        // std::cout << "?????????????????test currentStr=" << currentStr << std::endl;
        // std::cout << "11elementStr=" << elementStr << "i=" << i << "found=" << found << std::endl;
        i++;
      }
      else // делаем вывод, что все что осталось в строке, это число
      {
        elementStr = currentStr;
        // std::cout << "?????????????????test currentStr=" << currentStr << std::endl;
        // std::cout << "22elementStr=" << elementStr << "i=" << i << "found=" << found << std::endl;
        i += currentStr.size();
        // std::cout << "Строка закончилась. Крайний элемент справа =" << elementStr << "posWhite=" << posWhite << "i=" << i <<std::endl;
      }
    }
    /*    std::cout << "Argument exit " << std::endl;
        t_ret t;
        t.resiveDigitSize = resiveDigit.size_;
        t.resiveControlSize = resiveControl.size_;
        return t;
    */
    // std::cout << "==============elementStr.size()=" << elementStr.size() << "==============" << std::endl;
    if (elementStr.size() > 0) // length()
    {
      // std::cout << "============== цикл анализа типа и значения принятой подстроки ==============" << std::endl;
      // std::cout << "===controlSet1.count(elementStr[0])=" << controlSet1.count(elementStr[0]) << "====" << std::endl;
      // std::cout << "===!!!=== resiveControl.size_" << resiveControl.size_ << "resiveDigit=" << resiveDigit.size_ << std::endl;
      // std::cout << "=============== elementStr=" << elementStr << "elementStr.size()=" << elementStr.size() << std::endl;
      if ((elementStr.size() == 1) && (controlSet1.count(elementStr[0]))) // если это знак операции или скобки
      {
        // std::cout << "==============если elementStr-команда ==============" << std::endl;
        if (elementStr[0] == ')')
        {
          // std::cout << "встретилась закрывающая скобка:" << elementStr << std::endl;
          do
          {
            if ((resiveControl.size_ == 0) || (resiveControl.size_ == ullMax))
            {
              std::cout << "ЛОГИКА НАРУШЕНА" << std::endl;
              flgResult = false;
            }
            // std::cout << "1.))))) ЧИТАЮ ";
            strFS = resiveControl.pop(); // вынимаем из стека очередной символ
            // std::cout << strFS << " из Control пока не вытащим из стека ((((" << std::endl;
            if (strFS != str) // если из стека вытащили не "("
            {
              // std::cout << "2.))))) ПИШУ " << strFS << " в Digit, пока";
              resiveDigit.push(strFS); // Сохраняем принятый символ в очередь
              // std::cout << "не вытащим из стека ((((" << std::endl;
              // std::cout << "Сохраняем " << strFS << " из стека в очередь" << std::endl;
            }
            // else
            //{
            // std::cout << "вынули из стека открывающую скобку" << strFS << std::endl;
            //}
          } while ((strFS[0] != str[0]) && (resiveControl.size_ > 0));

          // if (resiveControl.size_ > 0)
          //{
          //   std::cout << resiveControl.pop() << "!!!!!!!!!!!!!!! Вынули из стека открывающую скобку" << std::endl;
          // }
        }
        else if ((prewCommand == "(") || (elementStr[0] == '('))
        {
          // resiveDigit.push(resiveControl.pop()); //Выгружаем из стека крайнюю команду в очередь.
          // std::cout << "3.ПИШУ " << elementStr;
          resiveControl.push(elementStr); // Сохраняем принятый символ в стек
          // std::cout << " в Control" << std::endl;
          // std::cout << "Сохраняем принятый символ " << elementStr << " в стек +-*/" << std::endl;
        }
        else
        {
          if ((resiveControl.size_ > 0) && (resiveControl.size_ != ullMax))
          {
            // std::cout << "4.ЧИТАЮ из Control и записываю";
            resiveDigit.push(resiveControl.pop()); // Выгружаем из стека крайнюю команду в очередь.
            // std::cout << "в Digit" << "resiveControl.size_=" << resiveControl.size_ << std::endl;
            // std::cout << "Сохраняем команду из стека в очередь" << std::endl;
          }
          // std::cout << "5.ПИШУ " << elementStr;
          resiveControl.push(elementStr); // Сохраняем принятый символ в стек
          // std::cout << " в Control" << std::endl;
          // std::cout << "Сохраняем" << elementStr << "в стек------------------------strFS =" << elementStr << "===" << std::endl;
        }
        prewCommand = elementStr;
      }
      else
      {
        // std::cout << "===========вот тут все и зависает===========" << std::endl;
        // std::cout << "6.ПИШУ " << elementStr << std::endl;
        resiveDigit.push(elementStr); // Сохраняем принятый символ в очередь
        // std::cout << " в Digit" << std::endl;
        // std::cout << "Сохраняем " << elementStr << " в очередь" << std::endl;
      }
    }
    else
    {
      std::cout << "ЛОГИКА НАРУШЕНА" << std::endl;
      flgResult = false;
    }
  }
  // std::cout << "Argument exit " << std::endl;
  t_ret t;
  t.resiveDigitSize = resiveDigit.size_;
  t.resiveControlSize = resiveControl.size_;
  t.flgRezult = flgResult;
  return t;
}
