#include <limits>
#include "list.hpp"
#include "functions.hpp"

int main()
{
  using namespace doroshenko;
  try
  {
    List< std::pair< std::string, List< size_t > > > list = listInput(std::cin);
    List< List < size_t > > lists;
    List< size_t > sums;
    namesOutput(list, std::cout);
    //listProcess(list, sums, lists);
    if (!list.isEmpty())
    {
      listFormation(list, lists);
      sumsFormation(lists, sums);
      listsOutput(std::cout, lists);
    }
    sumsOutput(std::cout, sums);
    return 0;
  }
  catch (std::overflow_error& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
