#ifndef TYPES_HPP
#define TYPES_HPP
#include "stack.hpp"

namespace mihalchenko
{
    struct CalcRez
    {
        CalcRez() = default;
        CalcRez(long long value);
        CalcRez operator+(const CalcRez &rhs);
        CalcRez operator-(const CalcRez &rhs);
        CalcRez operator*(const CalcRez &rhs);
        CalcRez operator/(const CalcRez &rhs);
        CalcRez operator%(const CalcRez &rhs);
        long long resultCalc;
    };

    struct finalTransform
    {
        // finalTransform() = default;
        // finalTransform(long long value);
        bool calculate();
        // bool canPop(Operator oper);
        // void calculate(Stack<char> &commands);

        Stack<CalcRez> calcRezult;
        Stack<char> commands;
        // long long resultCalc;
    };

    mihalchenko::CalcRez::CalcRez(long long value)
    {
        resultCalc = value;
    }

    mihalchenko::CalcRez mihalchenko::CalcRez::operator+(const CalcRez &rhs)
    {
        CalcRez result;
        result.resultCalc = resultCalc + rhs.resultCalc;
        return result;
    }
    mihalchenko::CalcRez mihalchenko::CalcRez::operator-(const CalcRez &rhs)
    {
        CalcRez result;
        result.resultCalc = resultCalc - rhs.resultCalc;
        return result;
    }
    mihalchenko::CalcRez mihalchenko::CalcRez::operator*(const CalcRez &rhs)
    {
        CalcRez result;
        result.resultCalc = resultCalc * rhs.resultCalc;
        return result;
    }
    mihalchenko::CalcRez mihalchenko::CalcRez::operator/(const CalcRez &rhs)
    {
        CalcRez result;
        result.resultCalc = resultCalc / rhs.resultCalc;
        return result;
    }
    mihalchenko::CalcRez mihalchenko::CalcRez::operator%(const CalcRez &rhs)
    {
        CalcRez result;
        result.resultCalc = resultCalc % rhs.resultCalc;
        return result;
    }

    // mihalchenko::finalTransform::finalTransform(long long value)
    //{
    // resultCalc = value;
    // }

    bool mihalchenko::finalTransform::calculate()
    {
        std::set<char> controlSet{'(', ')', '+', '-', '*', '/', '%'};
        // std::cout << "ku"  << std::endl;
        long long llMax = std::numeric_limits<long long>::max();
        // if finTrans.commands.getSize() = ullMax ...

        char codOperation;
        // commands.pop();
        CalcRez wremSave;
        CalcRez firstVal;
        CalcRez secondVal;
        bool flgSave = false;

        while (commands.getSize() > 0)
        {
            std::cout << "commands.getSize()=" << commands.getSize() << " calcRezult.getSize()=" << calcRezult.getSize() << std::endl;
            //------------------------------------------------------------------
            size_t stepСounter = 0;
            codOperation = '.';
            while ((commands.getSize() >= 0) && (!controlSet.count(codOperation)))
            {
                codOperation = commands.pop();
                stepСounter++;
                std::cout << codOperation << " ";
            }
            std::cout << "нашли команду" << std::endl;
            // std::cout << "may"  << std::endl;
            //------------------------------------------------------------------
            std::cout << "stepСounter=" << stepСounter << "commands.getSize()=" << commands.getSize() << std::endl;
            //========================================================
            std::cout << "Values:"
                      << "\n";
            size_t p = calcRezult.getSize();
            while (p > 0)
            {
                std::cout << calcRezult.watch(p - 1).resultCalc << " ";
                p = p - 1;
            }
            std::cout << std::endl;
            // return true;
            //========================================================

            if (stepСounter == 4)
            {
                wremSave = calcRezult.pop();
            }

            if (calcRezult.getSize() < 2)
            {
                std::cout << "ВНИМАНИЕ чисел меньше 2" << std::endl;
            }
            else
            {
                firstVal = calcRezult.pop();
                secondVal = calcRezult.pop();
            }
            if (codOperation == '+')
            {
                if ((llMax - firstVal.resultCalc) < secondVal.resultCalc)
                {
                    throw std::logic_error("Error: overflow!");
                    std::cerr << "Переполнение!\n";
                    return false;
                }
                calcRezult.push(firstVal + secondVal);
            }
            if (codOperation == '-')
            {
                calcRezult.push(firstVal - secondVal);
            }
            if (codOperation == '*')
            {
                calcRezult.push(firstVal * secondVal);
            }
            if (codOperation == '/')
            {
                calcRezult.push(firstVal / secondVal);
            }
            if (commands.getSize() != 0)
            {
                commands.push('.');
            }
            else
            {
                std::cout << calcRezult.watch(0).resultCalc << "\n";
            }
            if (stepСounter == 4)
            {
                calcRezult.push(wremSave);
                commands.push('.');
                flgSave = true;
            }

            //========================================================
            // std::cout <<  "commands:" << "\n" ;
            // while (commands.getSize() > 0)
            //{
            //  std::cout <<  commands.pop() << " " ;
            //}
            // std::cout << std::endl;
            //========================================================
            //========================================================
            /* if (stepСounter == 0)
             {
               std::cout <<  "commands:" << "\n" ;
               while (calcRezult.getSize() > 0)
               {
               std::cout << calcRezult.pop().resultCalc << " " ;
               }
               std::cout << std::endl;
             }*/
            //========================================================
        }
        return true;
    }
}

/*void mihalchenko::calculate()
{

}*/
/*void mihalchenko::calculate(long long operandOne, long long operandTwo, char operation)
{
  long long llMax = std::numeric_limits<long long>::max();
  long long resultVal;
  switch (operation)
  {
  case '+':
    if (llMax - operandTwo >= operandOne)
    {
      resultVal = operandTwo + operandOne;
      calcRezult.push(operandOne + operandTwo);
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
      resultVal = abs((operandOne / operandTwo -1) * operandTwo - operandOne);
    }
    else resultVal = operandTwo % operandOne;
    break;
  }
  calcRezult.push(resultVal);
}
*/
#endif
