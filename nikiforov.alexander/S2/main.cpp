#include "functions.hpp"

int main()
{
  using namespace nikiforov;

  List< long long > Result;
  List< std::string > Postfix;
  std::string infix = "";

  try
  {
    while (!std::cin.eof())
    {
      std::getline(std::cin, infix);
      convertToPostfix(infix, Postfix);
      calculation(Postfix, Result);
    }

    for (List< long long >::ConstIterator iter = Result.cbegin(); iter != Result.cend(); ++iter)
    {
      std::cout << *iter << "\n";
    }
  }
  catch (const std::overflow_error& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 0;
  }
  return 0;
}
