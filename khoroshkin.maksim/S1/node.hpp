#ifndef NODE_HPP
#define NODE_HPP

namespace khoroshkin
{
  template< typename T >
  class Node
  {
  public:
    T data;
    Node< T >  * pNext;

    Node(T data = T(), Node * pNext = nullptr)
    {
      this->data = data;
      this->pNext = pNext;
    }
  };
}

#endif