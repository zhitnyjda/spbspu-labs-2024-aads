#include "types.hpp"
#include <limits>
#include <cmath>

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
  if (resultCalc < 0)
  {
    result.resultCalc = abs((resultCalc / rhs.resultCalc - 1) * rhs.resultCalc - resultCalc);
  }
  else
    result.resultCalc = resultCalc % rhs.resultCalc;

  return result;
}

bool mihalchenko::finalTransform::calculate()
{
  std::set<char> controlSet{'(', ')', '+', '-', '*', '/', '%'};
  long long llMax = std::numeric_limits<long long>::max();
  char codOperation;
  CalcRez wremSave;
  CalcRez firstVal;
  CalcRez secondVal;
  // long long valWrem;
  // bool flgSave = false;
  if (calcRezult.getSize() == 1)
  {
    // std::cout << "введено одно число в строке"  << std::endl;
    return true;
  }
  else if ((calcRezult.getSize() == 0) && (commands.getSize() == 1))
  {
    // std::cout << "в строке один элемент" << valWrem << std::endl;
    return true;
  }

  while (commands.getSize() > 0)
  {
    size_t stepCounter = 0;
    codOperation = '.';
    while (/*(commands.getSize() >= 0) &&*/ (!controlSet.count(codOperation)))
    {
      codOperation = commands.pop();
      stepCounter++;
    }

    if (stepCounter == 4)
    {
      wremSave = calcRezult.pop();
    }

    if (calcRezult.getSize() < 2)
    {
      // std::cout << "ВНИМАНИЕ чисел меньше 2"  << std::endl;
      std::cerr << "Ошибка данных!\n";
      return false;
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
      if (llMax / firstVal.resultCalc < secondVal.resultCalc)
      {
        throw std::logic_error("Error: overflow!");
        std::cerr << "Переполнение!\n";
        return false;
      }
      calcRezult.push(firstVal * secondVal);
    }
    if (codOperation == '/')
    {
      calcRezult.push(firstVal / secondVal);
    }
    if (codOperation == '%')
    {
      calcRezult.push(firstVal % secondVal);
    }
    if (commands.getSize() != 0)
    {
      commands.push('.');
    }
    // else {std::cout << calcRezult.watch(0).resultCalc << "\n" ;}
    if (stepCounter == 4)
    {
      calcRezult.push(wremSave);
      commands.push('.');
      // flgSave = true;
    }
  }
  return true;
}
