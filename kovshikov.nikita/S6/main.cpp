#include <iomanip>
#include <iostream>
#include "random.hpp"
#include "sort.hpp"

int main(int argc, char ** argv)
{
  if(argc != 4)
  {
    std::cerr << "<THERE SHOULD BE 4 PARAMETERS>" << "\n";
    return 1;
  }

  std::cout << std::fixed << std::setprecision(3);
  using namespace kovshikov;

  std::string compare = argv[1];
  std::string type = argv[2];
  std::string strSize = argv[3];
  bool haveCompare = compare == "ascending" || compare == "descending";
  bool haveType = type == "ints" || type == "floats";

  if(!(haveCompare && haveType))
  {
    std::cerr << "<THE TYPE OR SORTING METHOD IS SPECIFIED INCORRECTLY>" << "\n";
    return 1;
  }

  if(!isDigit(strSize) || strSize == "0")
  {
    std::cerr << "<YOU NEED TO ENTER THE CORRECT SIZE>" << "\n";
    return 1;
  }
  size_t size = std::stoll(strSize);

  if(type == "ints")
  {
    std::forward_list< int > fwdList;
    DoubleList< int > list;
    std::deque< int > deque;
    getRandomInt(list, fwdList, deque, size);
    if(compare == "ascending")
    {
      Ascending< int > ascending;
      sort(ascending, deque, fwdList, list, std::cout);
    }
    else
    {
      Descending< int > descending;
      sort(descending, deque, fwdList, list, std::cout);
    }
  }
  else
  {
    std::forward_list< float > fwdList;
    DoubleList< float > list;
    std::deque< float > deque;
    getRandomFloat(list, fwdList, deque, size);
    if(compare == "ascending")
    {
      Ascending< float > ascending;
      sort(ascending, deque, fwdList, list, std::cout);
    }
    else
    {
      Descending< float > descending;
      sort(descending, deque, fwdList, list, std::cout);
    }
  }

  return 0;
}
