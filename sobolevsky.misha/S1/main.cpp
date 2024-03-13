#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "list.hpp"

int main()
{
  sobolevsky::List< std::vector< unsigned long long > > list;

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
      std::vector< unsigned long long > vec;
      currlen = 0;
      list.pushBack(vec, elem);
      length++;
    }
    else
    {
      unsigned long long i = stoll(elem);
      currlen++;
      list.tail->data.push_back(i);
    }
  }

  if (length == 0)
  {
    std::cout << "0\n";
    return 0;
  }

  sobolevsky::Iterator< std::vector< unsigned long long > > iter(list.head);
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
    std::vector< unsigned long long > lastList;
    size_t sumInts = 0;
    for (size_t i = 0; i < maxlen; i++)
    {
      sumInts = 0;
      bool first = true;
      sobolevsky::Iterator< std::vector< unsigned long long > > iter2(list.head);
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
          if (iter2.currNode->data[i] > (std::numeric_limits< unsigned long long >::max() - sumInts))
          {
            std::cerr << "Number is too big\n";
            return 1;
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
