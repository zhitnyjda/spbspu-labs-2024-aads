#include "divideFuncs.hpp"
#include <iostream>

std::string psarev::getOrd(std::string& line)
{
  std::string ord;
  ord = line.substr(0, line.find_first_of(" ", 0));
  if (line.find_first_of(" ") != std::string::npos)
  {
    line = line.substr(line.find_first_of(" ") + 1);
  }
  else
  {
    line = "";
  }
  return ord;
}

int psarev::getDigit(std::string& line)
{
  int digit = std::stoi(line.substr(0, line.find_first_of(" ", 0)));
  if (line.find_first_of(" ") != std::string::npos)
  {
    line = line.substr(line.find_first_of(" ") + 1);
  }
  else
  {
    line = "";
  }
  return digit;
}
