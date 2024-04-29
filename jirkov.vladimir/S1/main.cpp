#include <iostream>
#include <string>
#include <limits>
#include "list.hpp"
#include "calculatingData.hpp"

int main()
{
  using namespace jirkov;
  try
  {
    List<std::pair<std::string, List<size_t>>> newList = inputPair(std::cin);
    List<size_t> sums;
    if (newList.empty())
    {
      std::cout << "0\n";
      return 0;
    }
    printListNames(newList);
    printValues(newList, sums);
    getSums(sums);
    return 0;
  }
  catch (std::overflow_error const & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
