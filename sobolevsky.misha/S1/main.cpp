#include <iostream>
#include <string>
#include <limits>
#include "list.hpp"
#include "funcs.hpp"

int main()
{
  sobolevsky::List< sobolevsky::List< unsigned long long > > list;

  size_t maxlen = 0;
  size_t currlen = 0;
  size_t length = 0;
  std::string elem;
  while (std::cin >> elem)
  {
    if (isalpha(elem[0]))
    {
      maxlen = std::max(maxlen, currlen);
      sobolevsky::List< unsigned long long > subList;
      currlen = 0;
      list.pushBack(subList, elem);
      length++;
    }
    else
    {
      unsigned long long i = stoull(elem);
      currlen++;
      list.tail->data.pushBack(i, " ");
    }
  }

  if (length == 0)
  {
    std::cout << "0\n";
    return 0;
  }

  sobolevsky::Iterator< sobolevsky::List< unsigned long long > > iter(list.head);
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

  if (maxlen == 0)
  {
    std::cout << "0\n";
  }

  try
  {
    sobolevsky::output(list, maxlen, length);
  }
  catch(const std::overflow_error & e)
  {
    std::cerr << e.what();
    return 1;
  }

  return 0;
}
