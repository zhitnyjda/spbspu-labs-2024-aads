#include "list.hpp"

int main()
{
  hohlova::List<std::pair<std::string, hohlova::List<int>>>;
  std::string input;
  while (std::getline(std::cin, input))
  {
    if (input == "")
    {
      break;
    }
  }
}

