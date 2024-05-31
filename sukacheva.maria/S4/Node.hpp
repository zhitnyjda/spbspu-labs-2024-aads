#ifndef NODE_HPP
#define NODE_HPP
#include <utility>

namespace sukacheva
{
  namespace details
  {
    template < typename Value, typename Key >
    struct Node {
      std::pair< Key, Value > data;
      Node* left;
      Node* right;
      Node* parent;
      size_t height;
      Node(Key k, Value v) : data(std::make_pair(k, v)), left(nullptr), right(nullptr), parent(nullptr), height(0) {}
      Node(Key k, Value v, Node* p) : data(std::make_pair(k, v)), left(nullptr), right(nullptr), parent(p), height(0) {}
    };
  }
}

#endif
