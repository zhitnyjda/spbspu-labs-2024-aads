#include "functions.hpp"
#include <fstream>

int main(int argc, char* argv[])
{
  using namespace nikiforov;

  List< long long > Result;
  Queue< dataTypes > Postfix;
  std::string infix = "";

  try
  {
    if (argc == 2)
    {
      std::ifstream input(argv[1]);
      if (!input)
      {
        std::cerr << "Error: unable to open the file\n";
        return 2;
      }

      while (!input.eof())
      {
        std::getline(input, infix);
        convertToPostfix(infix, Postfix);
        calculation(Postfix, Result);
      }
    }
    else if (argc == 1)
    {
      while (!std::cin.eof())
      {
        std::getline(std::cin, infix);
        convertToPostfix(infix, Postfix);
        calculation(Postfix, Result);
      }
    }
    else
    {
      std::cerr << "Error: wrong number of parameters\n";
    }

    for (List< long long >::ConstIterator iter = Result.cbegin(); iter != Result.cend(); ++iter)
    {
      std::cout << *iter << "\n";
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}
