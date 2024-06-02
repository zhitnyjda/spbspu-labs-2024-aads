#ifndef IO_PROCESSING_HPP
#define IO_PROCESSING_HPP

#include <iostream>
#include <iomanip>
#include <deque>
#include <list>

namespace miheev
{
  template< typename Container >
  void printContainer(std::ostream&, const Container&);
  template< typename Printer, typename... PrinterArgs >
  void newLineWrapper(std::ostream&, Printer p, PrinterArgs... pArgs);

  void fillContainersWithRandom(std::deque< double >&, std::list< double >&, size_t amount);
  void fillContainersWithRandom(std::deque< int >&, std::list< int >&, size_t amount);
  
  template< typename T, typename Comparator >
  void testSorts(std::ostream&, size_t size,  Comparator comp);
}

template< typename Container >
void miheev::printContainer(std::ostream& out, const Container& container)
{
  out << std::fixed << std::setprecision(1);
  for (auto iter(container.cbegin()); iter != container.cend();)
  {
    out << *iter;
    if (++iter != container.cend())
    {
      out << ' ';
    }
  }
}
template< typename Printer, typename... PrinterArgs >
void miheev::newLineWrapper(std::ostream& out, Printer p, PrinterArgs... pArgs)
{
  p(out, pArgs...);
  out << '\n';
}

void miheev::fillContainersWithRandom(std::deque< int >& deque, std::list< int >& bidirect, size_t amount)
{
  for (size_t i = 0; i < amount; i++)
  {
    int random = rand() % 100;
    deque.push_back(random);
  }
  std::copy(deque.begin(), deque.end(), std::back_inserter(bidirect));
}

void miheev::fillContainersWithRandom(std::deque< double >& deque, std::list< double >& bidirect, size_t amount)
{
  for (size_t i = 0; i < amount; i++)
  {
    double random = static_cast< double >(rand() % 1000) / (rand() % 10);
    deque.push_back(random);
  }
  copy(deque.begin(), deque.end(), std::back_inserter(bidirect));
}

template< typename T, typename Comparator >
void miheev::testSorts(std::ostream&, size_t size,  Comparator comp)
{
  std::list< T > bidirect;
  std::deque< T > deque;
  fillContainersWithRandom(deque, bidirect, size);
  
}

#endif

