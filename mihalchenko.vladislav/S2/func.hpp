#ifndef FUNC_HPP
#define FUNC_HPP
#include "stack.hpp"
#include "queue.hpp"
#include "list.hpp"

namespace mihalchenko
{
  void printedResult(std::ostream &out, Stack<long long> &calcRes, size_t &num);
  // void printedQueuePostFix(std::ostream &out, Queue<std::string> &queue, size_t &num);
  // size_t calculatePostFix(Queue<std::string> &resiveDigit, Stack<long long> &calculateResult, Stack<mihalchenko::CalcRez> &calcRezult);
  size_t calculatePostFix(Queue<std::string> &resiveDigit, Stack<long long> &calculateResult);
  bool bildStrPostFix(std::string &currentStr, size_t currentStrSize, Queue<std::string> &resiveDigit, Stack<std::string> &resiveControl);
  long long bildOperation(long long operandOne, long long operandTwo, char operation);
}

#endif
