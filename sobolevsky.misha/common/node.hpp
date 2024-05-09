#ifndef NODE_HPP
#define NODE_HPP
#include <string>

namespace sobolevsky
{
  template< typename T >
  class Node
  {
  public:
    Node * next;
    Node * prev;
    T data;

    Node(T dataIn);
  };
}

template< typename T >
sobolevsky::Node< T >::Node(T dataIn)
{
  data = dataIn;
  prev = nullptr;
  next = nullptr;
}

#endif
