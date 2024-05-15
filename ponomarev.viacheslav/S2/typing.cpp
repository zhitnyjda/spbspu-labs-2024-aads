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

