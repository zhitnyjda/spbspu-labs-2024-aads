#include <limits>
#include "list.hpp"
#include "functions.hpp"

int main()
{
  using namespace doroshenko;
  try
  {
    List< std::pair< std::string, List< size_t > > > list = listInput(std::cin);
    List< size_t > sums;
    namesOutput(list, std::cout);
    listOutput(list, std::cout, sums);
    sumsOutput(std::cout, sums);
    return 0;
  }
  catch (std::overflow_error& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
