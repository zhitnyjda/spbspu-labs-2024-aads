#include "funcs.hpp"

using namespace khoroshkin;

void khoroshkin::printResult(std::ostream & out, List< std::pair< std::string, List< int > > > & allPairs, size_t maxLength)
{
  for (auto it = allPairs.begin(); it != allPairs.end(); ++it)
  {
    out << (*it).first;
    allPairs.next(it) == allPairs.end() ? std::cout << "\n" : std::cout << " ";
  }

  /*for (size_t i = 0; i < maxLength; i++)
  {
    for (size_t j = 0; j < length; j++)
    {
      if (allPairs[j].second.getSize() > i)
      {
        std::cout << allPairs[j].second[i];
        j == length ? std::cout << "\n" : std::cout << " ";
      }
    }
    std::cout << "\n";
  }

  for (size_t i = 0; i < maxLength; i++)
  {
    int sum = 0;
    for (size_t j = 0; j < length; j++)
    {
      if (allPairs[j].second.getSize() > i)
      {
        sum += allPairs[j].second[i];
      }
    }
    std::cout << sum;
    i + 1 == maxLength ? std::cout << "\n" : std::cout << " ";
  }*/
}
