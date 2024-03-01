#ifndef NODE_HPP
#define NODE_HPP

namespace gorbunova
{
  template<typename T>
  class Node
  {
  public:
    Node* next;
    T data;
    Node(T data = T(), Node* next = nullptr)
    {
      this->data = data;
      this->next = next;
    }
  };
}

#endif
