#ifndef FUNCTIONALOBJECT_HPP
#define FUNCTIONALOBJECT_HPP

#include <utility>
#include "queue.hpp"

namespace khoroshkin
{
  struct Traverse
  {
    void operator()(const std::pair< const int, std::string > & kv_pair)
    {
      result += kv_pair.first;
      bypass.push(kv_pair.second);
    }
    Queue< std::string > bypass{};
    int result = 0;
  };
}

#endif
