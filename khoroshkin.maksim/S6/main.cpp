#include <iostream>
#include <deque>
#include <list>
#include <cstring>
#include <iomanip>
#include "sort.hpp"
#include "list.hpp"

int main(int argc, char * argv[])
{
  using namespace khoroshkin;
  srand(time(0));

  if (argc != 4)
  {
    std::cerr << "Error: wrong input!\n";
    return 1;
  }

  if (std::string(argv[2]) == "ints")
  {
    List< int > forwardList;
    std::list< int > list;
    std::deque< int > deque;

    for (size_t i = 0; i < std::stoull(argv[3]); ++i)
    {
      forwardList.push_back(rand() % 100);
      list.push_back(rand() % 100);
      deque.push_back(rand() % 100);
    }

    outContainer(std::cout, forwardList);
    outContainer(std::cout, list);
    outContainer(std::cout, deque);

    if (std::string(argv[1]) == "ascending")
    {
      std::less< int > comp;
      timSort(forwardList.begin(), forwardList.end(), comp);
      shellSort(list.begin(), list.end(), comp);
      timSort(deque.begin(), deque.end(), comp);
    }
    else if (std::string(argv[1]) == "descending")
    {
      std::greater< int > comp;
      timSort(forwardList.begin(), forwardList.end(), comp);
      shellSort(list.begin(), list.end(), comp);
      timSort(deque.begin(), deque.end(), comp);
    }
    else
    {
      std::cerr << "Error: wrong input!\n";
      return 1;
    }

    outContainer(std::cout, forwardList);
    outContainer(std::cout, list);
    outContainer(std::cout, deque);
  }
  else if (std::string(argv[2]) == "floats")
  {
    List< double > forwardList;
    std::list< double > list;
    std::deque< double > deque;

    for (size_t i = 0; i < std::stoull(argv[3]); ++i)
    {
      forwardList.push_back(static_cast< double >(rand() % 100));
      list.push_back(static_cast< double >(rand() % 100));
      deque.push_back(static_cast< double >(rand() % 100));
    }

    outContainer(std::cout, forwardList);
    outContainer(std::cout, list);
    outContainer(std::cout, deque);

    if (std::string(argv[1]) == "ascending")
    {
      std::less< double > comp;
      timSort(forwardList.begin(), forwardList.end(), comp);
      shellSort(list.begin(), list.end(), comp);
      timSort(deque.begin(), deque.end(), comp);
    }
    else if (std::string(argv[1]) == "descending")
    {
      std::greater< double > comp;
      timSort(forwardList.begin(), forwardList.end(), comp);
      shellSort(list.begin(), list.end(), comp);
      timSort(deque.begin(), deque.end(), comp);
    }
    else
    {
      std::cerr << "Error: wrong input!\n";
      return 1;
    }

    outContainer(std::cout, forwardList);
    outContainer(std::cout, list);
    outContainer(std::cout, deque);
  }
  else
  {
    std::cerr << "Error: wrong input!\n";
    return 1;
  }

  return 0;
}
