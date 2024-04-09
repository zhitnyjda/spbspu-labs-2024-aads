#ifndef NODE_HPP
#define NODE_HPP
#include <string>

namespace sobolevsky
{
  template< typename T >
  class Node
  {
  public:
    Node * next = nullptr;
    Node * prev = nullptr;
    T data = T();
    std::string name = "";

    Node(T dataIn, std::string nameIn)
    : name(nameIn)
    , data(dataIn)
    {}
  };
}

#endif
