#include <iostream>
#include <list>
#include <deque>
#include "io.hpp"
#include "oddEvenSort.hpp"
#include "insertionSort.hpp"
#include "random.hpp"

int main()
{
  srand(time(0));

  std::list< int > listForInsertion;
  for (size_t i = 0; i < 15; i++)
  {
    listForInsertion.push_back(zheleznyakov::anarchy::randomInt());
  }

  std::list< int > listForOddEven;
  std::copy(listForInsertion.begin(), listForInsertion.end(), std::back_inserter(listForOddEven));

  zheleznyakov::sorts::insertion(listForInsertion.begin(), listForInsertion.end(), std::greater< int >());
  zheleznyakov::sorts::oddEven(listForOddEven.begin(), listForOddEven.end(), std::less< int >());

  zheleznyakov::iterOut(listForInsertion, std::cout);
  zheleznyakov::iterOut(listForOddEven, std::cout);

  std::list< float > floatListForInsertion;
  for (size_t i = 0; i < 15; i++)
  {
    floatListForInsertion.push_back(zheleznyakov::anarchy::randomFloat());
  }

  std::list< float > floatListForOddEven;
  std::copy(floatListForInsertion.begin(), floatListForInsertion.end(), std::back_inserter(floatListForOddEven));

  zheleznyakov::sorts::insertion(floatListForInsertion.begin(), floatListForInsertion.end(), std::greater< int >());
  zheleznyakov::sorts::oddEven(floatListForOddEven.begin(), floatListForOddEven.end(), std::less< int >());

  zheleznyakov::iterOut(floatListForInsertion, std::cout);
  zheleznyakov::iterOut(floatListForOddEven, std::cout);

  return 0;
}
