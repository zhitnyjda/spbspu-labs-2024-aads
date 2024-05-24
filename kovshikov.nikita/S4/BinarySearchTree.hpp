#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include <utility>
#include <functional>
#include <iterator>
#include <cassert>

namespace kovshikov
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
 // class BinarySearchTree
  class Tree
  {
  public:
    class Node;
    class Iterator;
    class ConstIterator;

    using pair = std::pair< Key, Value >;
    Compare comp;
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

template< typename Key, typename Value, typename Compare >
kovshikov::Tree< Key, Value, Compare >::Iterator : public std::iterator< std::bidirectional_iterator_tag, pair >
{
public:
  friend class Tree< Key, Value, Compare >;
  using this_t = Iterator;

  Iterator(): node_(nullptr), root_(nullptr) {};
  Iterator(const this_t&) = default;
  ~Iterator() = default;

  this_t& operator=(const this_t &) = default;

  this_t& operator++();
  this_t operator++(int);

  this_t& operator--();
  this_t& operator--(int);
private:
  *Node node_;
  *Node root_;
}

template< typename Key, typename Value, typename Compare >
kovshikov::Tree< Key, Value, Compare >::Iterator::this_t& kovshikov::Tree< Key, Value, Compare >::Iterator::operator++()
{
  assert(node_ != nullptr);
  Node* current = node_;
  if(current -> right)
  {
    current = current -> right;
    while(current -> left)
    {
      current = current -> left;
    }
  }
  else
  {
    Node* currentFather = current -> father;
    while(currentFather && current == currentFather -> right)
    {
      current = currentFather;
      currentFather = currentFather -> father;
    }
    current = currentFather;
  }
  node_ = current;
  return *this;
}

template< typename Key, typename Value, typename Compare >
kovshikov::Tree< Key, Value, Compare >::Iterator::this_t& kovshikov::Tree< Key, Value, Compare >::Iterator::operator++(int)
{
  assert(node_ != nullptr);
  this_t currentIterator = *this;
  ++(*this)
  return currentIterator;
}

template< typename Key, typename Value, typename Compare >
kovshikov::Tree< Key, Value, Compare >::Iterator::this_t& kovshikov::Tree< Key, Value, Compare >::Iterator::operator--()
{
  assert(node_ != nullptr);
  Node* current = node_;
  if(current -> left)
  {
    current = current -> left;
    while(current -> right)
    {
      current = current -> right;
    }
  }
  else
  {
    Node* currentFather = current -> father;
    while(currentFather && current == left)
    {
      current = currentFather;
      currentFather = currentFather -> father;
    }
    current = currentFather;
  }
  node_ = current;
  return *this;
}

template< typename Key, typename Value, typename Compare >
kovshikov::Tree< Key, Value, Compare >::Iterator::this_t& kovshikov::Tree< Key, Value, Compare >::Iterator::operator--(int)
{
  assert(node_ != nullptr);
  this_t currentIterator = *this;
  --(*this);
  return currentIterator;
}

#endif
