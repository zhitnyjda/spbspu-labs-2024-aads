#include "types.hpp"
#include <limits>
#include <cmath>
#include <list.hpp>
#include "processing.hpp"

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

bool mihalchenko::FinalTransform::calculate()
{
  mihalchenko::List< char > list = mihalchenko::getListFromString("()+-*/%");
  long long llMax = std::numeric_limits< long long >::max();
  char codOperation;
  CalcRez wremSave;
  CalcRez firstVal;
  CalcRez secondVal;

  if (calcRezult.getSize() == 1)
  {
    return true;
  }
  else if ((calcRezult.getSize() == 0) && (commands.getSize() == 1))
  {
    return true;
  }

  while (commands.getSize() > 0)
  {
    size_t stepCounter = 0;
    codOperation = '.';
    bool flag = false;
    bool flag1;
    while(!flag)
    {
      flag1 = false;
      for(size_t i = 0; i < list.getSize(); i++)
      {
        if (list[i] == codOperation)
        {
          flag1 = true;
        }
      }
      if (flag1)
      {
        flag = true;
      }
      else
      {
        codOperation = commands.pop();
        stepCounter++;
      }
    }
    if (stepCounter == 4)
    {
      wremSave = calcRezult.pop();
    }

    if (calcRezult.getSize() < 2)
    {
      std::cerr << "Data error!\n";
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
        std::cerr << "Overflow!\n";
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
        std::cerr << "Overflow!\n";
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
    if (codOperation == '(' || codOperation == ')')
    {
      calcRezult.push(codOperation);
    }
    if (commands.getSize() != 0)
    {
      commands.push('.');
    }
    if (stepCounter == 4)
    {
      calcRezult.push(wremSave);
      commands.push('.');
    }
  }
  return true;
}
