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
   // Node() : data(0), prev(nullptr), next(nullptr) {}; //два очень схожих конструктора
    Node(T data_ = 0, Node* prev_ = nullptr, Node* next_ = nullptr) :
    data(data_),
    prev(prev_),
    next(next_)
    {};
    ~Node() = default;
  };
}

#endif
