#include <fstream>
#include "termFuncs.hpp"

int main(int argc, char* argv[])
{
  psarev::Queue< std::string > terms;
  psarev::Stack< long long > resultStack;

  if (argc == 1)
  {
    psarev::readTerms(std::cin, terms);
  }
  else if (argc == 2)
  {
    std::ifstream input(argv[1]);
    psarev::readTerms(input, terms);
  }
  else
  {
    std::cerr << "Error: Wrong parameters amount!\n";
    return 1;
  }
  try
  {
    psarev::formResultStack(terms, resultStack);
    while (!resultStack.isEmpty())
    {
      std::cout << resultStack.getTop();
      resultStack.pop();
      if (!resultStack.isEmpty())
      {
        std::cout << ' ';
      }
    }
    std::cout << '\n';
  }
  catch (std::exception& e)
  {
    std::cout << e.what();
    return 1;
  }
  return 0;
}