#include <iostream>
#include <utility>
#include "list.hpp"

int main()
{
  psarev::List< std::pair< std::string, psarev::List< int > > > seqs;

  while (!std::cin.eof())
  {
    for (size_t i = 0; i < psarev::list.getSize(); i++)
    {
      std::cout << list[i] << ' ';
    }
    std::cout << '\n';

    list.remove(2);
    for (size_t i = 0; i < list.getSize(); i++)
    {
      std::cout << list[i] << ' ';
    }
    std::cout << '\n';
  }
}
