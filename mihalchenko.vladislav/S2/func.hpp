#ifndef FUNC_HPP
#define FUNC_HPP

#include <iostream>
#include <string>
#include "stack.hpp"
#include "queue.hpp"

namespace mihalchenko
{
  void printedResult(std::ostream &out, Stack<long long> &calcRes, size_t &num);
  size_t calculatePostFix(Queue<std::string> &resiveDigit, Stack<long long> &calculateResult);
  bool bildStrPostFix(std::string &currentStr, size_t currentStrSize, Queue<std::string> &resiveDigit,
    Stack<std::string> &resiveControl);
}

#endif
