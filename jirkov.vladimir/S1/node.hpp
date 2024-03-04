#ifndef NODE_HPP
#define NODE_HPP

namespace jirkov {

template <typename T>
struct Node {
  using value_type = T;

  Node(const value_type& value, Node<T>* next) : data(value), next(next) {}

  value_type data;
  Node<T>* next;
};

}

#endif
