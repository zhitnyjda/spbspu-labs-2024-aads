#include <iostream>
#include <deque>
#include <list>
#include <cstring>
#include <iomanip>
#include "sort.hpp"
#include "list.hpp"

template< typename T >
std::ostream & outContainer(std::ostream & out, const T & container)
{
  for (auto it = container.begin(); it != container.end(); it++)
  {
    out << std::fixed << std::setprecision(1) << *it;
    out << ((std::next(it) == container.end()) ? "\n" : " ");
  }
  return out;
}

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
      forwardList.push_back((double)(rand() % 100));
      list.push_back((double)(rand() % 100));
      deque.push_back((double)(rand() % 100));
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