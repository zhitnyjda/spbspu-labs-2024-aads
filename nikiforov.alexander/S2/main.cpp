#include "functions.hpp"
#include <fstream>

int main(int argc, char* argv[])
{
  using namespace nikiforov;

  if (argc != 2)
  {
    std::cerr << "Error: wrong number of parameters\n";
    return 2;
  }

  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Error: unable to open the file\n";
    return 2;
  }

  List< long long > Result;
  Queue< dataTypes > Postfix;
  std::string infix = "";

  try
  {
    while (!input.eof())
    {
      std::getline(input, infix);
      convertToPostfix(infix, Postfix);
      calculation(Postfix, Result);
    }

    for (List< long long >::ConstIterator iter = Result.cbegin(); iter != Result.cend(); ++iter)
    {
      std::cout << *iter << "\n";
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 0;
  }
  return 0;
}
