#ifndef RANDOM_HPP
#define RANDOM_HPP
#include <algorithm>
#include <cstdlib>
#include <forward_list>
#include <iterator>
#include <iostream>
#include <list>
#include <deque>

namespace kovshikov
{
  void getRandomInt(std::list< int >& list, std::forward_list< int >& forward, std::deque< int >& deque, size_t size);
  void getRandomFloat(std::list< float >& list, std::forward_list< float >& forward, std::deque< float >& deque, size_t size);

  template< typename Container >
  std::ostream& printConteiner(const Container& container, std::ostream& out);
}

void kovshikov::getRandomInt(std::list< int >& list, std::forward_list< int >& forward, std::deque< int >& deque, size_t size)
{
  std::srand(0);
  for(size_t i = 0; i < size; i++)
  {
    list.push_front(std::rand() % 1000);
  }
  std::copy(list.begin(), list.end(), std::front_inserter(deque));
  std::copy(list.begin(), list.end(), std::front_inserter(forward));
}

void kovshikov::getRandomFloat(std::list< float >& list, std::forward_list< float >& forward, std::deque< float >& deque, size_t size)
{
  std::srand(0);
  for(size_t i = 0; i < size; i++)
  {
    float element = static_cast< float >(std::rand() % 1000) / static_cast< float >(std::rand() % 1000);
    list.push_front(element);
  }
  std::copy(list.begin(), list.end(), std::front_inserter(deque));
  std::copy(list.begin(), list.end(), std::front_inserter(forward));
}

template< typename Container >
std::ostream& kovshikov::printConteiner(const Container& container, std::ostream& out)
{
  auto begin = container.begin();
  auto end = container.end();
  auto next = begin;
  while(begin != end)
  {
    next++;
    if(next == end)
    {
      out << *begin << "\n";
    }
    else
    {
      out << *begin << " ";
    }
    begin++;
  }
  return out;
}

#endif
