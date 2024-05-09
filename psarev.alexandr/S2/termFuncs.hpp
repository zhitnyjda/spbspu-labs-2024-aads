#ifndef TERMFUNCS_HPP
#define TERMFUNCS_HPP
#include <iostream>
#include <string>
#include "stack.hpp"
#include "queue.hpp"

namespace psarev
{
  void readTerms(std::istream& input, Queue< std::string >& result);
  void strToQueue(std::string expression, Queue< std::string >& result);
  bool isOperand(std::string symbol);
  bool isOperator(std::string c);
  int priori(std::string c);
  void postfixation(Queue< std::string >& term, Queue< std::string >& result);
  long long makeOper(long long fval, long long sval, std::string operation);
  long long calculateExpr(Queue< std::string >& terms);
  void formResultStack(Queue< std::string >& terms, Stack< long long >& resultStack);
}

#endif