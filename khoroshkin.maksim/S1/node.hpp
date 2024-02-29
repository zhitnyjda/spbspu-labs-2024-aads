#ifndef NODE_HPP
#define NODE_HPP

namespace khoroshkin
{
  template< typename T >
  class Node
  {
  public:
    Node(T data = T(), Node * pNext = nullptr);
    T data;
    Node< T >  * pNext;
  };
}

template < typename T >
khoroshkin::Node< T >::Node(T data, khoroshkin::Node< T > * pNext) :
  data(data), pNext(pNext)
{}

#endif
