#include <iostream>
#include "sort.hpp"
#include "random.hpp"
#include <iomanip>

int main()
{
  std::cout << std::fixed << std::setprecision(3);
  using namespace kovshikov;
  std::list< int > listInt;
  std::forward_list< int > fwdListInt;
  std::deque< int > dequeInt;
  std::list< float > listFloat;
  std::forward_list< float > fwdListFloat;
  std::deque< float > dequeFloat;

  size_t size = 10;

  getRandomInt(listInt, fwdListInt, dequeInt, size);
  getRandomFloat(listFloat, fwdListFloat, dequeFloat, size);

  printConteiner(listInt, std::cout);
  printConteiner(fwdListInt, std::cout);
  printConteiner(dequeInt, std::cout);
  printConteiner(listFloat, std::cout);
  printConteiner(fwdListFloat, std::cout);
  printConteiner(dequeFloat, std::cout);
}







/*  using namespace kovshikov;
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
  std::cout << "\n";

  std::deque< int > dint{1, 6, 10, -6, 3, 0, -4, 11, 2};
//  Descending< int > descending2;
  selectionSort(dint.begin(), dint.end(), descending);
  auto iterator2 = dint.begin();
  while(iterator2 != dint.end())
  {
    std::cout << *iterator2 << " ";
    iterator2++;
  }
  std::cout << "\n";

  std::list< int > flint2{1, 6, 10, -6, 3, 0, -4, 11, 2};
  //Ascending< int > ascending;
  //Descending< int > descending;
  shellSort(flint2.begin(), flint2.end(), descending);
  auto iterator3 = flint2.begin();
  while(iterator3 != flint2.end())
  {
    std::cout << *iterator3 << " ";
    iterator3++;
  }
  std::cout << "\n";

  std::forward_list< int > flint3{1, 6, 10, -6, 3, 0, -4, 11, 2};
  Ascending< int > ascending;
//  Descending< int > descending;
  bubbleSort(flint3.begin(), flint3.end(), ascending);
  auto iterator4 = flint3.begin();
  while(iterator4 != flint3.end())
  {
    std::cout << *iterator4 << " ";
    iterator4++;
  }
  std::cout << "\n";

*/
