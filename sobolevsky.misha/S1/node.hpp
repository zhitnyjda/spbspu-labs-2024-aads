#ifndef NODE_HPP
#define NODE_HPP

template< class T >
class Node
{
  private:
    Node * next;
    Node * prev;
    T data;
};

#endif