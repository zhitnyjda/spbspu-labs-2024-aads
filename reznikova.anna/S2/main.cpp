#include "InputProcessing.hpp"

int main()
{
  reznikova::Queue< reznikova::Element > infix;
  reznikova::readLine(std::cin, infix);
  reznikova::Postfix postfix;
  long long int calculate_result = 0;
  try
  {
    reznikova::makePostfix(infix, postfix);
    calculate_result = reznikova::calculate(postfix);
  }
  catch (std::exception & e)
  {
    std::cerr << e.what();
    return 1;
  }
  std::cout << calculate_result;
  return 0;
}
