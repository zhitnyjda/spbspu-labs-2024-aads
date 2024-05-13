#include <iostream>
#include <chrono>
#include <iomanip>
#include <deque>
#include <list>
#include <cstring>
#include "list.hpp"
#include "bucketSort.hpp"
#include "quickSort.hpp"
#include "outputFunction.hpp"

int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    std::cerr << "Error: wrong number of parameters\n";
    return 2;
  }

  int size = std::atoi(argv[3]);
  if (size == 0)
  {
      std::cerr << "Error: wrong size parameter\n";
      return 1;
  }

  srand(time(0));

  if (!strcmp(argv[2], "ints"))
  {
    redko::List< int > forwardList{};
    for (auto i = 0; i < size; ++i)
    {
      forwardList.pushBack(rand() / 10);
    }

    std::list< int > firstList(size);
    std::copy_n(forwardList.cbegin(), size, firstList.begin());
    std::list< int > secondList(size);
    std::copy_n(forwardList.cbegin(), size, secondList.begin());
    std::deque< int > firstDeque(size);
    std::copy_n(forwardList.cbegin(), size, firstDeque.begin());
    std::deque< int > secondDeque(size);
    std::copy_n(forwardList.cbegin(), size, secondDeque.begin());

    if (!strcmp(argv[1], "ascending"))
    {
      redko::sortBucket(forwardList.begin(), forwardList.end());
      redko::sortBucket(firstList.begin(), firstList.end());
      redko::sortQuick(secondList.begin(), secondList.end(), std::less< int >());
      redko::sortBucket(firstDeque.begin(), firstDeque.end());
      redko::sortQuick(secondDeque.begin(), secondDeque.end(), std::less< int >());
    }
    else if (!strcmp(argv[1], "descending"))
    {
      redko::sortBucket(forwardList.begin(), forwardList.end(), false);
      redko::sortBucket(firstList.begin(), firstList.end(), false);
      redko::sortQuick(secondList.begin(), secondList.end(), std::greater< int >());
      redko::sortBucket(firstDeque.begin(), firstDeque.end(), false);
      redko::sortQuick(secondDeque.begin(), secondDeque.end(), std::greater< int >());
    }
    else
    {
      std::cerr << "Error: wrong sort parameter\n";
      return 1;
    }

    redko::printSorted(std::cout, forwardList.begin(), forwardList.end());
    redko::printSorted(std::cout, firstList.begin(), firstList.end());
    redko::printSorted(std::cout, secondList.begin(), secondList.end());
    redko::printSorted(std::cout, firstDeque.begin(), firstDeque.end());
    redko::printSorted(std::cout, secondDeque.begin(), secondDeque.end());
  }
  else if (!strcmp(argv[2], "floats"))
  {
    redko::List< double > forwardList{};
    for (auto i = 0; i < size; ++i)
    {
      forwardList.pushBack(double(rand()) / 10);
    }

    std::list< double > firstList(size);
    std::copy_n(forwardList.cbegin(), size, firstList.begin());
    std::list< double > secondList(size);
    std::copy_n(forwardList.cbegin(), size, secondList.begin());
    std::deque< double > firstDeque(size);
    std::copy_n(forwardList.cbegin(), size, firstDeque.begin());
    std::deque< double > secondDeque(size);
    std::copy_n(forwardList.cbegin(), size, secondDeque.begin());

    if (!strcmp(argv[1], "ascending"))
    {
      redko::sortBucket(forwardList.begin(), forwardList.end());
      redko::sortBucket(firstList.begin(), firstList.end());
      redko::sortQuick(secondList.begin(), secondList.end(), std::less< double >());
      redko::sortBucket(firstDeque.begin(), firstDeque.end());
      redko::sortQuick(secondDeque.begin(), secondDeque.end(), std::less< double >());
    }
    else if (!strcmp(argv[1], "descending"))
    {
      redko::sortBucket(forwardList.begin(), forwardList.end(), false);
      redko::sortBucket(firstList.begin(), firstList.end(), false);
      redko::sortQuick(secondList.begin(), secondList.end(), std::greater< double >());
      redko::sortBucket(firstDeque.begin(), firstDeque.end(), false);
      redko::sortQuick(secondDeque.begin(), secondDeque.end(), std::greater< double >());
    }
    else
    {
      std::cerr << "Error: wrong sort parameter\n";
      return 1;
    }

    std::cout << std::fixed << std::setprecision(1);
    redko::printSorted(std::cout, forwardList.begin(), forwardList.end());
    redko::printSorted(std::cout, firstList.begin(), firstList.end());
    redko::printSorted(std::cout, secondList.begin(), secondList.end());
    redko::printSorted(std::cout, firstDeque.begin(), firstDeque.end());
    redko::printSorted(std::cout, secondDeque.begin(), secondDeque.end());
  }
  else
  {
    std::cerr << "Error: wrong type parameter\n";
    return 1;
  }
  return 0;
}
