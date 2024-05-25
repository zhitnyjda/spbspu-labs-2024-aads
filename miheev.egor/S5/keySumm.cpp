#include "keySumm.hpp"

miheev::KeySumm::KeySumm():
  result(0),
  values("")
{}

void miheev::KeySumm::operator()(const std::pair< const int, std::string >& keyValue)
{
  result += keyValue.first;
  if (!values.empty())
  {
    values += " ";
  }
  values += keyValue.second;
}

std::string miheev::KeySumm::getResults()
{
  return std::to_string(result) + " " + values;
}
