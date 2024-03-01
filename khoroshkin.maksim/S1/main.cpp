#include <iostream>
#include <string>
#include <memory>
#include <limits>
#include "list.hpp"
#include "funcs.hpp"

using namespace khoroshkin;

int main()
{
  List< std::pair< std::string, List< int > > > allPairs;
  std::string input;
  size_t count = -1;
  size_t maxLength = 0;
  while (std::cin >> input)
  {
    if (isdigit(input[0]))
    {
      try
      {
        allPairs[count].second.push_back(std::stoll(input));
      }
      catch(const std::out_of_range & e)
      {
        std::cerr << e.what() << '\n';
        return 1;
      }
    }
    else
    {
      allPairs.push_back({input,{}});
      count++;
    }
    if (maxLength < allPairs[count].second.getSize())
    {
      maxLength = allPairs[count].second.getSize();
    }
  }

  try
  {
    printResult(std::cout, allPairs, maxLength);
  }
  catch(const std::logic_error & e)
  {
    std::cout << 0 << '\n';
    return 0;
  }
  catch(const std::out_of_range & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
