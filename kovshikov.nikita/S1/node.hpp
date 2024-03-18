#ifndef NODE_HPP
#define NODE_HPP

namespace kovshikov
{
  template <typename T>
  struct Node
  {
    T data;
    Node* prev;
    Node* next;
    Node(): data(0), prev(nullptr), next(nullptr) {};
    Node(T data_) :
    data(data_),
    prev(nullptr),
    next(nullptr)
    {};
    ~Node() = default;
  };
}

#endif
