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

  private:
    *Node root_;
  }
 // using Tree = BinarySearchTree;
}

template< typename Key, typename Value, typename Compare >
class kovshikov::Tree< Key, Value, Compare >::Node
{
public:
  friend class Tree;

private:
  *Node left_;
  *Node right_;
  *Node father_;
  size_t height_;
  std::pair< Key, Value > element;
}

#endif
