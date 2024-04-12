#include <iostream>
#include <string>
#include <utility>
#include "ForwardList.hpp"
#include "Vector.hpp"
#include "functions.hpp"

int main()
{
  try
  {
    std::string str;
    zasulsky::ForwardList < std::pair< std::string, zasulsky::Vector< int > > > list;
    while (!std::cin.eof())
    {
      std::getline(std::cin, str);
      getSequence(list, str);
    }
    outputNames(list, std::cout);
    outputSequence(list, std::cout);
  }
  catch (...)
  {
    std::cerr << "incorrect use of programm\n";
    return 1;
  }
}
