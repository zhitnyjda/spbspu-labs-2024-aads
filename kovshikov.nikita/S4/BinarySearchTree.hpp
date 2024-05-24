#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include <utility>

namespace kovshikov
{
  template< typename Key, typename Value, typename Compare >
 // class BinarySearchTree
  class Tree
  {
  public:
    class Node;
    using pair = std::pair< Key, Value >;

  private:
    *Node root_;
  }
 // using Tree = BinarySearchTree;
}

template< typename Key, typename Value, typename Compare >
class kovshikov::Tree< Key, Value, Compare >::Node
{
public:
  friend class Tree< Key, Value, Compare >;
  Node(Key key, Value value, *Node father = nullptr, size_t height = 0, *Node left = nullptr, *Node right = nullptr);

private:
  *Node left_;
  *Node right_;
  *Node father_;
  size_t height_;
  pair element;
}

template< typename Key, typename Value, typename Compare >
kovshikov::Tree< Key, Value, Compare >::Node::Node(Key key, Value value, *Node father, size_t height, *Node left, *Node right):
  left_(left),
  right_(right),
  father_(father),
  height_(height),
  element_(std::make_pair(key, value))
{};

#endif
