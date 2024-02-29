#include "inputFunctions.hpp"
int redko::cutValue(std::string & str)
{
  int m = std::stoi(str.substr(0, str.find_first_of(" ", 0)));  if (str.find_first_of(" ") == std::string::npos)
  {
    str = "";
  }
  else
  {
    str = str.substr(str.find_first_of(" ") + 1);
  }
  return m;
}

std::string redko::cutName(std::string& str)
{
  std::string n = str.substr(0, str.find_first_of(" ", 0));  if (str.find_first_of(" ") == std::string::npos)
  {
    str = "";
  }
  else
  {
    str = str.substr(str.find_first_of(" ") + 1);
  }
  return n;
}
