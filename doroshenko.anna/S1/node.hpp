#ifndef NODE_HPP
#define NODE_HPP

namespace doroshenko
{
  template <typename T>
  struct Node
  {
    T data;
    Node<T>* next;
    Node(T value) :
      data(value),
      next(nullptr)
    {}
  };
}

#endif
