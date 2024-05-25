#ifndef TREE_HPP
#define TREE_HPP
#include <utility>
#include <stdexcept>
#include <functional>

namespace zheleznyakov {
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  class Tree {
  public:
    using data_t = typename std::pair< Key, Value >;

    Tree() = default;
    ~Tree() = default;
  private:
    struct Node
    {
      Node(
        Node * parent = nullptr,
        Node * left = nullptr,
        Node * right = nullptr
      ):
        parent{parent},
        left{left},
        right{right}
      {}

      data_t data;
      Node * parent;
      Node * left;
      Node * right;
    };

    Node * root_;
  };
}
#endif
