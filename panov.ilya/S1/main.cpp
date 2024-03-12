#include <iostream>
#include "list.hpp"
#include "inputlist.hpp"
#include "output.hpp"

int main()
{
  using namespace Panov;
  size_t size = 0;
  size_t max_size_list = 0;
  std::pair< std::string, Panov::List< unsigned long long >* >* pairs = nullptr;
  try
  {
    pairs = inputList(std::cin, size, max_size_list);
    output(std::cout, pairs, size, max_size_list);
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << '\n';
    freeMemory(pairs, size);
    return 1;
  }
  std::cout << '\n';
  freeMemory(pairs, size);
}
