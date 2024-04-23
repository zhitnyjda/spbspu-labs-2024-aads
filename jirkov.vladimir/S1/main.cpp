#include <limits>
#include "list.hpp"

int main()
{
  using namespace jirkov;
  try
  {
    List<std::pair<std::string,List<size_t>>>list = Input(std::cin);
    const size_t maximum = std::numeric_limits< size_t >::max();
    size_t sum = 0;
    Iterator<std::pair<std::string, List<size_t>>>iterator = list.begin();
    List< size_t > sums;
    Iterator< size_t > iterator;
    return 0;
}
