#include "resultCounter.hpp"

anikanov::ResultCounter::ResultCounter()
{
  result = 0;
  values = "";
}

void anikanov::ResultCounter::operator()(const std::pair< int, std::string > &key_value)
{
  result += key_value.first;
  values += key_value.second + " ";
}

int anikanov::ResultCounter::getResult() const
{
  return result;
}

std::string anikanov::ResultCounter::getValues() const
{
  return values;
}
