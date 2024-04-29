#ifndef NODE_HPP
#define NODE_HPP

namespace jirkov
{
  namespace details
  {
    template <typename T>
    struct Node
    {
      T data;
      Node<T>* next;
      explicit Node(T value) : data(value), next(nullptr) {}
    };
  }
}

#endif
