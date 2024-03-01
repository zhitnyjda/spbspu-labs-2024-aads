#include <iostream>
#include <sstream>
#include <utility>
#include <string>
#include "list.hpp"

using SI_pair = typename std::pair< std::string, miheev::List< int > >;

void expandPairsArr(SI_pair*& pairs, size_t& size)
{
  const size_t additionalSize = 5;
  SI_pair* copy = new SI_pair[size + additionalSize];
  for (size_t i = 0; i < size; i++)
  {
    copy[i] = pairs[i];
  }
  size += additionalSize;
  delete [] pairs;
  pairs = copy;
}

miheev::List< int > readNumbers(std::istringstream& stream)
{
  int number = 0;
  stream >> number;

  miheev::List< int > list(number);

  while(stream >> number)
  {
    std::cout << "the number is " << number << '\n';
    list.pushBack(number);
  }
  list.print();
  return list;
}

SI_pair readLine()
{
  std::string line;
  std::getline(std::cin, line);
  std::istringstream stream(line);

  SI_pair pair;
  stream >> pair.first; // reading word
  pair.second = readNumbers(stream);

  return pair;
}

int main()
{
  using namespace miheev;

  size_t pairsSize = 5;
  SI_pair* pairs = new SI_pair[pairsSize];
  size_t unusedIndex = 0;

  while (!std::cin.eof())
  {
    if (unusedIndex >= pairsSize)
    {
      expandPairsArr(pairs, pairsSize);
    }
    pairs[unusedIndex] = readLine();
    unusedIndex++;
  }

  return 0;
}

