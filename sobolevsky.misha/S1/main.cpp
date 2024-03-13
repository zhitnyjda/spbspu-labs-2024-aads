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

  if (length == 0)
  {
    std::cerr << "Empty input\n";
    return 0;
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

  if (maxlen > 0)
  {
    std::vector< int > lastList;
    size_t sumInts = 0;
    for (size_t i = 0; i < maxlen; i++)
    {
      sumInts = 0;
      bool first = true;
      sobolevsky::Iterator< std::vector< int > > iter2(list.head);
      for (size_t j = 0; j < length; j++)
      {
        if (i < iter2.currNode->data.size())
        {
          if (first)
          {
            std::cout << iter2.currNode->data[i];
            first = false;
          }
          else
          {
            std::cout << " " << iter2.currNode->data[i];
          }
          sumInts += iter2.currNode->data[i];
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
  }
  else
  {
    std::cout << "0\n";
  }

  return 0;
}
