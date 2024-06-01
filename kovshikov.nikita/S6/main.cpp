#include <iostream>
#include <forward_list>
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
}
