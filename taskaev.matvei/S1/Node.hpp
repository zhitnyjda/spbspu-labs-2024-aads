#ifndef NODE_HPP
#define NODE_HPP

namespace taskaev
{
  template<typename T>
  struct Node
  {
    T data;
    Node<T>* next;
    Node(const T& value) : data(value), next(nullptr) {}
  };
}
#endif
