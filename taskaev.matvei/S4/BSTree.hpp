#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <iostream>

namespace taskaev
{
  template < typename Key, typename Value, typename Comparator >
  class BSTree
  {
  public:
    class Node;
    {
    public:
      friend class BSTree;
      explicit Node(const Key key, const Value val):
        data_(std::pair< Key, Value >(key, val)),
        right_(nullptr),
        left_(nullptr),
        parent_(nullptr),
        height_(1)
      {}
      Node* right_;
      Node* left_;
      Node* parent_;
      size_t height_;
      std::pair< Key, Value > data_;
    };
  };
}
