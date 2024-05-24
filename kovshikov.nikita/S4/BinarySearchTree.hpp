#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include <utility>
#include <functional>
#include <iterator>
#include <cassert>
#include <memory>

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

    using Pair = std::pair< Key, Value >;
    Compare comp;

    bool isEmpty() const noexcept;
    void insert(const Key& key, const Value& value);

  private:
    Node* root_;
  };
 // using Tree = BinarySearchTree;
}


template< typename Key, typename Value, typename Compare >
class kovshikov::Tree< Key, Value, Compare >::Node
{
public:
  friend class Tree< Key, Value, Compare >;
  Node(Key key, Value value, Node* father = nullptr, size_t height = 0, Node* left = nullptr, Node* right = nullptr);

private:
  Node* left_;
  Node* right_;
  Node* father_;
  size_t height_;
  Pair element_;
};

template< typename Key, typename Value, typename Compare >
kovshikov::Tree< Key, Value, Compare >::Node::Node(Key key, Value value, Node* father, size_t height, Node* left, Node* right):
  left_(left),
  right_(right),
  father_(father),
  height_(height),
  element_(std::make_pair(key, value))
{};

template< typename Key, typename Value, typename Compare >
class kovshikov::Tree< Key, Value, Compare >::Iterator : public std::iterator< std::bidirectional_iterator_tag, Pair >
{
public:

  friend class Tree< Key, Value, Compare >;
  using this_t = Iterator;

  Iterator(): node_(nullptr), root_(nullptr) {};
  Iterator(Node* node, Node* root): node_(node), root_(root) {};
  Iterator(const this_t&) = default;
  ~Iterator() = default;

  this_t& operator=(const this_t&) = default;

  this_t& operator++();
  this_t operator++(int);

  this_t& operator--();
  this_t operator--(int);

  bool operator==(const this_t& other) const;
  bool operator!=(const this_t& other) const;

  Pair& operator*() const;
  Pair* operator->() const;

private:
  Node* node_;
  Node* root_;
};

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Iterator::this_t& kovshikov::Tree< Key, Value, Compare >::Iterator::operator++()
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
typename kovshikov::Tree< Key, Value, Compare >::Iterator::this_t kovshikov::Tree< Key, Value, Compare >::Iterator::operator++(int)
{
  assert(node_ != nullptr);
  this_t currentIterator = *this;
  ++(*this);
  return currentIterator;
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Iterator::this_t& kovshikov::Tree< Key, Value, Compare >::Iterator::operator--()
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
    while(currentFather && current == currentFather -> left)
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
typename kovshikov::Tree< Key, Value, Compare >::Iterator::this_t kovshikov::Tree< Key, Value, Compare >::Iterator::operator--(int)
{
  assert(node_ != nullptr);
  this_t currentIterator = *this;
  --(*this);
  return currentIterator;
}

template< typename Key, typename Value, typename Compare >
bool kovshikov::Tree< Key, Value, Compare >::Iterator::operator==(const this_t& other) const
{
  return node_ == other.node_;
}

template< typename Key, typename Value, typename Compare >
bool kovshikov::Tree< Key, Value, Compare >::Iterator::operator!=(const this_t& other) const
{
  return !(*this == other);
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Pair& kovshikov::Tree< Key, Value, Compare >::Iterator::operator*() const
{
  assert(node_ != nullptr);
  return node_ -> element_;
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Pair* kovshikov::Tree< Key, Value, Compare >::Iterator::operator->() const
{
  assert(node_ != nullptr);
  return std::addressof(node_ -> element_);
}

template< typename Key, typename Value, typename Compare >
class kovshikov::Tree< Key, Value, Compare >::ConstIterator : public std::iterator< std::bidirectional_iterator_tag, Pair >
{
public:

  friend class Tree< Key, Value, Compare >;
  using this_t = ConstIterator;

  ConstIterator(): iterator_(Iterator()) {};
  ConstIterator(Iterator iterator): iterator_(iterator) {};
  ConstIterator(const this_t&) = default;
  ~ConstIterator() = default;

  this_t& operator=(const this_t&) = default;

  this_t& operator++();
  this_t operator++(int);

  this_t& operator--();
  this_t operator--(int);

  bool operator==(const this_t& other) const;
  bool operator!=(const this_t& other) const;

  const Pair& operator*() const;
  const Pair* operator->() const;

private:
  Iterator iterator_;
};

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::ConstIterator& kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator++()
{
  assert(iterator_.node_ != nullptr);
  iterator_++;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::ConstIterator kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator++(int)
{
  assert(iterator_.node_ != nullptr);
  ++iterator_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::ConstIterator& kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator--()
{
  assert(iterator_.node_ != nullptr);
  iterator_--;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::ConstIterator kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator--(int)
{
  assert(iterator_.node_ != nullptr);
  --iterator_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
bool kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator==(const this_t& other) const
{
  return iterator_ == other.iterator_;
}

template< typename Key, typename Value, typename Compare >
bool kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator!=(const this_t& other) const
{
  return !(*this == other);
}

template< typename Key, typename Value, typename Compare >
const typename kovshikov::Tree< Key, Value, Compare >::Pair& kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator*() const
{
  assert(iterator_.node_ != nullptr);
  return iterator_.node_ -> element_;
}

template< typename Key, typename Value, typename Compare >
const typename kovshikov::Tree< Key, Value, Compare >::Pair* kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator->() const
{
  assert(iterator_.node_ != nullptr);
  return std::addressof(iterator_.node_ -> element_);
}

template< typename Key, typename Value, typename Compare >
bool kovshikov::Tree< Key, Value, Compare >::isEmpty() const noexcept
{
  return (root_ == nullptr) ? true : false;
}

template< typename Key, typename Value, typename Compare >
void kovshikov::Tree< Key, Value, Compare >::insert(const Key& key, const Value& value)
{
  //нет проверки на то что такой ключ уже есть
  Node* newNode = new Node(key, value);
  if(isEmpty())
  {
    root_ = newNode;
  }
  else
  {
    Node* current = root_;
    Node* father = nullptr;
    while(current != nullptr)
    {
      father = current;
      if(comp(key, current -> element_.first))
      {
        current = current -> left;
      }
      else
      {
        current = current -> right;
      }
    }
    newNode -> father = father;
    if(comp(key, father -> element_.first))
    {
      father -> left = newNode;
    }
    else
    {
      father -> right = newNode;
    }
  }
  //нужна балансировка
}

#endif
