#include <limits>
#include "list.hpp"
#include "inputPair.hpp"
#include "findSize.hpp"
#include "outputPair.hpp"

int main()
{
  using namespace jirkov;
  try
  {
    List<std::pair<std::string, List<size_t>>> list = inputPair(std::cin);
    outputPair(list);
    return 0;
  }
  catch (std::overflow_error const & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
