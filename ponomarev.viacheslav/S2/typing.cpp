#include "typing.hpp"

ponomarev::Bracket::Bracket(char symbol):
  bracket(symbol)
{}

bool ponomarev::isBracket(char symbol)
{
  return (symbol == ")" || symbol == "(");
}

bool ponomarev::isOpenBracket(char symbol)
{
  return (symbol == "(");
}

ponomarev::Operation::Operation(char elem):
  operation_(elem);
{}

ponomarev::Operand::Operand():
  num(0)
{}

ponomarev::Operand::Operand(int num):
  num(num)
{}

