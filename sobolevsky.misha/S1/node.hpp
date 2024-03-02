#ifndef NODE_HPP
#define NODE_HPP

template< class T >
class Node
{
public:
  Node(T data)
  {
    data = data;
    prev = nullptr;
    next = nullptr;
  }
private:
  Node * next;
  Node * prev;
  T data;
  char Name;
};

#endif
