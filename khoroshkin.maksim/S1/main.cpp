#include <iostream>
#include <cstring>
#include <memory>
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
      allPairs[count].second.push_back(std::stoll(input));
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
  if (allPairs[0].second.isEmpty())
  {
    std::cout << 0;
    return 0;
  }
  try
  {
    printResult(std::cout, allPairs, maxLength);
  }
  catch(const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
