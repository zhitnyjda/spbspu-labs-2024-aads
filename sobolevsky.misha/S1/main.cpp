#include <iostream>
#include <string>
#include <vector>
#include "list.hpp"

int main()
{
  sobolevsky::List< std::vector< int > > list;

  size_t maxlen = 0;
  size_t currlen = 0;
  std::string elem;
  while (std::cin >> elem)
  {
    if (elem == "penis")
    {
      break;
    }
    if (isalpha(elem[0]))
    {
      maxlen = std::max(maxlen, currlen);
      std::vector< int > vec;
      currlen = 0;
      list.pushBack(vec, elem);
    }
    else
    {
      int i = stoi(elem);
      currlen++;
      list.tail->data.push_back(i);
    }
  }

  std::cout << list.head->name << "\n";
  std::cout << list.head->data[0] << "\n";

  return 0;
}
