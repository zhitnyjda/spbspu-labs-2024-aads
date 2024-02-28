#include <iostream>
#include <utility>
#include <string>
#include "list.hpp"

int main()
{
  using namespace miheev;
  using SI_pair = std::pair< std::string, List< int > >;

  size_t pairsCount = 5;
  SI_pair* pairs = new SI_pair[pairsCount];
  while (std::cin and !std::cin.eof())
  {
    std::string line;
    std::getline(std::cin, line);
    std::string word;
    word << line;
    std::cout << word << '\n';
  }
  return 0;
}

