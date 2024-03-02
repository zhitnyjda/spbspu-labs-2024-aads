#ifndef NODE_HPP
#define NODE_HPP

namespace sobolevsky
{
  template< class T >
  class Node
  {
  public:
    Node(T data);
  private:
    Node * next;
    Node * prev;
    T data;
    char Name;
  };
}

template< class T >
sobolevsky::Node< T >::Node(T data)
{
  data = data;
  prev = nullptr;
  next = nullptr;
}

#endif
