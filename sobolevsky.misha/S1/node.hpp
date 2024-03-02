#ifndef NODE_HPP
#define NODE_HPP

namespace sobolevsky
{
  template< typename T >
  class Node
  {
  public:
    Node * next;
    Node * prev;
    T data;
    char Name;

    Node(T data);
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
