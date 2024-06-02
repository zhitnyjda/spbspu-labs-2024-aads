#include <deque>
#include <iostream>
#include <forward_list>
#include <list>
#include "sort.hpp"

int main()
{
  using namespace kovshikov;
  std::forward_list< int > flint{1, 6, 10, -6, 3, 0, -4, 11, 2};
//  Ascending< int > ascending;
  Descending< int > descending;
  selectionSort(flint.begin(), flint.end(), descending);
  auto iterator = flint.begin();
  while(iterator != flint.end())
  {
    std::cout << *iterator << " ";
    iterator++;
  }
  std::deque< int > dint{1, 6, 10, -6, 3, 0, -4, 11, 2};
  Descending< int > descending2;
  selectionSort(dint.begin(), dint.end(), descending2);
  auto iterator2 = dint.begin();
  while(iterator2 != dint.end())
  {
    std::cout << *iterator2 << " ";
    iterator2++;
  }

  std::list< int > flint2{1, 6, 10, -6, 3, 0, -4, 11, 2};
  Ascending< int > ascending;
  //Descending< int > descending;
  shellSort(flint2.begin(), flint2.end(), ascending);
  auto iterator3 = flint2.begin();
  while(iterator3 != flint2.end())
  {
    std::cout << *iterator3 << " ";
    iterator3++;
  }

}
