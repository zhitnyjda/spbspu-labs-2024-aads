#include "inputFunctions.hpp"
int redko::cutValue(std::string & str)
{
  int value = std::stoi(str.substr(0, str.find_first_of(" ", 0)));
  if (str.find_first_of(" ") == std::string::npos)
  {
    str = "";
  }
  else
  {
    str = str.substr(str.find_first_of(" ") + 1);
  }
  return value;
}

std::string redko::cutName(std::string& str)
{
  std::string name = str.substr(0, str.find_first_of(" ", 0));
  if (str.find_first_of(" ") == std::string::npos)
  {
    str = "";
  }
  else
  {
    str = str.substr(str.find_first_of(" ") + 1);
  }
  return name;
}
