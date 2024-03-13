#include <iostream>
#include <string>
#include <vector>
#include "list.hpp"

int main()
{
  sobolevsky::List< std::vector< int > > list;

  size_t maxlen = 0;
  size_t currlen = 0;
  size_t length = 0;
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
      length++;
    }
    else
    {
      int i = stoi(elem);
      currlen++;
      list.tail->data.push_back(i);
    }
  }

  sobolevsky::Iterator< std::vector< int > > iter(list.head);
  for (size_t i = 0; i < length; i++)
  {
    std::cout << iter.name();
    ++iter;
    if (i != (length - 1))
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";

  std::vector< int > lastList;
  size_t sumInts = 0;
  for (size_t i = 0; i < maxlen; i++)
  {
    sumInts = 0;
    sobolevsky::Iterator< std::vector< int > > iter2(list.head);
    for (size_t j = 0; j < length; j++)
    {
      if (i < iter2.currNode->data.size())
      {
        std::cout << iter2.currNode->data[i];
        sumInts += iter2.currNode->data[i];
        if (j != (length - 1))
        {
          std::cout << " ";
        }
      }
      ++iter2;
    }
    lastList.push_back(sumInts);
    std::cout << "\n";
  }

  for (size_t i = 0; i < lastList.size(); i++)
  {
    std::cout << lastList[i];
    if (i != (lastList.size() - 1))
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";

  return 0;
}
