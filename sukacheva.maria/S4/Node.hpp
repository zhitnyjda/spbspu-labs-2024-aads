#ifndef NODE_HPP
#define NODE_HPP
#include <utility>
#include <cstddef>

namespace sukacheva
{
  namespace details
  {
    template < typename Value, typename Key >
    struct Node {
      Node(Key k, Value v) : data(std::make_pair(k, v)), left(nullptr), right(nullptr), parent(nullptr), height(0) {}
      Node(Key k, Value v, Node* p) : data(std::make_pair(k, v)), left(nullptr), right(nullptr), parent(p), height(0) {}
      std::pair< Key, Value > data;
      Node* left;
      Node* right;
      Node* parent;
      size_t height;
    };
  }
}

#endif
