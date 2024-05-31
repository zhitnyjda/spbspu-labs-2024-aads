#ifndef STRUCTSUMMA_HPP
#define STRUCTSUMMA_CPP
#include <utility>
#include "queue.hpp"

namespace kovshikov
{
  struct TreeTraversal
  {
    void operator()(const std::pair< const int, std::string >& element)
    {
      result += element.first;
      allValue.push(element.second);
    }
    Queue< std::string > allValue;
    int result = 0;
  };
}

#endif
