#ifndef COMPUTING_HPP
#define COMPUTING_HPP
#include "queue.hpp"

namespace kovshikov
{
  void readData(std::istream& in, Queue< std::string >& allData);
  void separateElements(std::string str, Queue< std::string >& queue);
  //void getPostfix
}

#endif
