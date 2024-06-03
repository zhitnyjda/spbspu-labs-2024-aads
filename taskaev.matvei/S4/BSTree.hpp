#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <iostream>
#include <cassert>
#include <utility>
#include <functional>
#include <stdexcept>

namespace taskaev
{
  template < typename Key, typename Value, typename Comparator >
  class BSTree
  {
  public:
    class ConstIterator;
    class Iterator;
    using value_t = std::pair< Key, Value >;
    class Node
    {
    public:
      friend class BSTree;
      explicit Node(value_t data, Node* right = nullptr, Node* left = nullptr, Node* parent = nullptr, size_t h = 0):
        data_(data),
        right_(right),
        left_(left),
        parent_(parent),
        height_(h)
      {}
      std::pair< Key, Value > data_;
      Node* right_;
      Node* left_;
      Node* parent_;
      size_t height_;
    };
    BSTree();
    BSTree(const BSTree& rhs);
    BSTree(BSTree&& rhs);
    ~BSTree();

    Value& at(const Key& key); // yes
    bool empty() const noexcept;
    void clear();
    size_t size() const noexcept;
    void swap(BSTree& rhs);

    void insert(const value_t& pair);
    void insert(const Key& key, const Value& value);

    void erase(const Key& key);
    ConstIterator find(const Key& key) const;

    Iterator begin();
    Iterator end();

    ConstIterator cbegin() const;
    ConstIterator cend() const;

  private:
    Node* root_;
    Comparator comp_;
    size_t size_;

    Node* balance(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
    void updHeight(Node* node) noexcept;
    size_t getHeight(const Node* root) const noexcept;
    size_t height(Node* node);

    void free(Node* node);

    Node* erase(Node* node, const Key& key);
    Node* removeNode(Node* node);
    Node* findMinNode(Node* node);
  };
}

using namespace taskaev;
template < typename Key, typename Value >
using value_t = std::pair< Key, Value >;

template < typename Key, typename Value, typename Comparator>
class taskaev::BSTree< Key, Value, Comparator>::ConstIterator
{
  friend class BSTree;
public:
  ConstIterator();
  ConstIterator(Node* node, Node* root);
  ConstIterator(const ConstIterator&) = default;
  ~ConstIterator() = default;

  ConstIterator& operator=(const ConstIterator&) = default;

  ConstIterator& operator++();
  ConstIterator operator++(int);
  ConstIterator& operator--();
  ConstIterator operator--(int);

  const value_t& operator*() const;
  const value_t* operator->() const;

  bool operator!=(const ConstIterator& rhs) const;
  bool operator==(const ConstIterator& rhs) const;

private:
  Node* node_;
  Node* root_;
};

template< typename Key, typename Value, typename Comparator >
BSTree< Key, Value, Comparator >::ConstIterator::ConstIterator() :
  node_(nullptr),
  root_(nullptr)
{};

template< typename Key, typename Value, typename Comparator >
BSTree< Key, Value, Comparator >::ConstIterator::ConstIterator(Node* node, Node* root) :
  node_(node),
  root_(root)
{}

template< typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::ConstIterator& BSTree< Key, Value, Comparator >::ConstIterator::operator++()
{
  assert(node_ != nullptr);
  if (node_->right_ != nullptr)
  {
    node_ = node_->right_;
    while (node_->left_ != nullptr)
    {
      node_ = node_->left_;
    }
  }
  else
  {
    while (node_->parent_ != nullptr && node_ == node_->parent_->right_)
    {
      node_ = node_->parent_;
    }
    node_ = node_->parent_;
  }
  return *this;
}

template< typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::ConstIterator BSTree< Key, Value, Comparator >::ConstIterator::operator++(int)
{
  assert(node_ != nullptr);
  ConstIterator result(*this);
  ++(*this);
  return result;
}

template< typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::ConstIterator& BSTree< Key, Value, Comparator >::ConstIterator::operator--()
{
  assert(node_ != nullptr);
  if (node_->left_ != nullptr)
  {
    node_ = node_->left_;
    while (node_->right_ != nullptr)
    {
      node_ = node_->right_;
    }
  }
  else
  {
    Node* tempNode = node_;
    node_ = node_->parent_;
    while (node_ && tempNode == node_->left_)
    {
      tempNode = node_;
      if (node_->parent_)
      {
        node_ = node_->parent_;
      }
      else
      {
        break;
      }
    }
  }
  return *this;
}

template< typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::ConstIterator BSTree< Key, Value, Comparator >::ConstIterator::operator--(int)
{
  assert(node_ != nullptr);
  ConstIterator result(*this);
  --(*this);
  return result;
}

template< typename Key, typename Value, typename Comparator >
const value_t< Key, Value >& BSTree< Key, Value, Comparator >::ConstIterator::operator*() const
{
  assert(node_ != nullptr);
  return node_->data_;
}
template< typename Key, typename Value, typename Comparator >
const value_t< Key, Value >* BSTree< Key, Value, Comparator >::ConstIterator::operator->() const
{
  assert(node_ != nullptr);
  return std::addressof(node_->data_);
}

template< typename Key, typename Value, typename Comparator >
bool BSTree< Key, Value, Comparator >::ConstIterator::operator!=(const ConstIterator& rhs) const
{
  return !(rhs == *this);
}

template< typename Key, typename Value, typename Comparator >
bool BSTree< Key, Value, Comparator >::ConstIterator::operator==(const ConstIterator& rhs) const
{
  return node_ == rhs.node_;
}

template< typename Key, typename Value, typename Comparator >
class BSTree< Key, Value, Comparator >::Iterator
{
public:
  friend class BSTree;
  Iterator();
  Iterator(ConstIterator someIterator);
  ~Iterator() = default;
  Iterator(const Iterator&) = default;
  Iterator& operator=(const Iterator&) = default;
  Iterator operator++();
  Iterator operator++(int);
  Iterator operator--();
  Iterator operator--(int);

  value_t& operator*();
  value_t* operator->();

  bool operator!=(const Iterator& rhs) const;
  bool operator==(const Iterator& rhs) const;
private:
  ConstIterator iterator_;
};

template< typename Key, typename Value, typename Comparator >
BSTree< Key, Value, Comparator >::Iterator::Iterator() :
  iterator_(nullptr)
{};

template< typename Key, typename Value, typename Comparator >
BSTree< Key, Value, Comparator >::Iterator::Iterator(ConstIterator iter) :
  iterator_(iter)
{}

template< typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::Iterator::Iterator BSTree< Key, Value, Comparator >::Iterator::operator++()
{
  assert(iterator_.node_ != nullptr);
  iterator_++;
  return iterator_;
}

template< typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::Iterator::Iterator BSTree< Key, Value, Comparator >::Iterator::operator++(int)
{
  ++iterator_;
  return iterator_;
}

template< typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::Iterator::Iterator BSTree< Key, Value, Comparator >::Iterator::operator--()
{
  iterator_--;
  return iterator_;
}

template< typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::Iterator::Iterator BSTree< Key, Value, Comparator >::Iterator::operator--(int)
{
  --iterator_;
  return iterator_;
}

template< typename Key, typename Value, typename Comparator >
value_t< Key, Value >& BSTree< Key, Value, Comparator >::Iterator::operator*()
{
  return iterator_.node_->data_;
}
template< typename Key, typename Value, typename Comparator >
value_t< Key, Value >* BSTree< Key, Value, Comparator >::Iterator::operator->()
{
  return std::addressof(iterator_.node_->data_);
}

template< typename Key, typename Value, typename Comparator >
bool BSTree< Key, Value, Comparator >::Iterator::operator!=(const Iterator& rhs) const
{
  return !(rhs == *this);
}

template< typename Key, typename Value, typename Comparator >
bool BSTree< Key, Value, Comparator >::Iterator::operator==(const Iterator& rhs) const
{
  return iterator_ == rhs.iterator_;
}

template< typename Key, typename Value, typename Comparator >
BSTree< Key, Value, Comparator >::BSTree():
  root_(nullptr),
  comp_(Comparator()),
  size_(0)
{}

template< typename Key, typename Value, typename Comparator >
BSTree< Key, Value, Comparator >::BSTree(const BSTree& rhs) :
  root_(nullptr),
  comp_(rhs.comp_),
  size_(rhs.size_)
{
  for (auto it = rhs.cbegin(); it != rhs.cend(); ++it)
  {
    insert(it->first, it->second);
  }
}

template< typename Key, typename Value, typename Comparator >
BSTree< Key, Value, Comparator >::BSTree(BSTree&& rhs) :
  root_(rhs.root_),
  comp_(rhs.comp_),
  size_(rhs.size_)
{
  rhs.root_ = nullptr;
  rhs.size_ = 0;
}

template< typename Key, typename Value, typename Comparator >
BSTree< Key, Value, Comparator >::~BSTree()
{
  clear();
}

template< typename Key, typename Value, typename Comparator >
Value& BSTree< Key, Value, Comparator >::at(const Key& key)
{
  Node* newRoot = root_;
  while (newRoot != nullptr)
  {
    if (key < newRoot->data_.first)
    {
      newRoot = newRoot->left_;
    }
    else if (key > newRoot->data_.first)
    {
      newRoot = newRoot->right_;
    }
    else
    {
      return newRoot->data_.second;
    }
  }
  std::cerr << "Error: not key!\n";
}

template< typename Key, typename Value, typename Comparator >
bool BSTree< Key, Value, Comparator >::empty() const noexcept
{
  return root_ == nullptr;
}

template< typename Key, typename Value, typename Comparator >
size_t BSTree< Key, Value, Comparator >::size() const noexcept
{
  return size_;
}

template< typename Key, typename Value, typename Comparator >
void BSTree< Key, Value, Comparator >::swap(BSTree& rhs)
{
  std::swap(root_, rhs.root_);
  std::swap(comp_, rhs.comp_);
  size_ = rhs.size_;
}

template< typename Key, typename Value, typename Comparator >
void BSTree< Key, Value, Comparator >::insert(const value_t& val)
{
  insert(val.first, val.second);
}

template < typename Key, typename Value, typename Comparator >
void BSTree< Key, Value, Comparator >::insert(const Key& key, const Value& val)
{
  if (!empty())
  {
    Node* newRoot = root_;
    Node* nodes = nullptr;
    while (newRoot)
    {
      nodes = newRoot;
      if (key < newRoot->data_.first)
      {
        newRoot = newRoot->left_;
      }
      else if (key > newRoot->data_.first)
      {
        newRoot = newRoot->right_;
      }
      else
      {
        return;
      }
    }
    Node* newNodes = new Node({ key, val }, nodes);
    if (key > nodes->data_.first)
    {
      nodes->right_ = newNodes;
    }
    else
    {
      nodes->left_ = newNodes;
    }
    balance(newNodes);
    size_++;
  }
  else
  {
    root_ = new Node({ key, val });
    size_++;
    return;
  }
}

template< typename Key, typename Value, typename Compare >
void BSTree< Key, Value, Compare >::updHeight(Node* node) noexcept
{
  node->height_ = std::max(getHeight(node->left_), getHeight(node->right_)) + 1;
}

template< typename Key, typename Value, typename Compare >
size_t BSTree< Key, Value, Compare >::getHeight(const Node* node) const noexcept
{
  return (node == nullptr) ? 0 : node->height_;
}

template< typename Key, typename Value, typename Compare >
size_t BSTree< Key, Value, Compare >::height(Node* node)
{
  return ((node->left_ != nullptr) ? node->left_->height_ : 0) - ((node->right_ != nullptr) ? node->right_->height_ : 0);
}

template< typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::Node* BSTree< Key, Value, Comparator >::balance(Node* node)
{

  updHeight(node);
  int flag = height(node);
  if (flag > 1)
  {
    if (height(node->left_) < 0)
    {
      node->left_ = rotateLeft(node->left_);
    }
    return rotateRight(node);
  }
  else if (flag < -1)
  {
    if (height(node->right_) > 0)
    {
      node->right_ = rotateRight(node->right_);
    }
    return rotateLeft(node);
  }
  return node;
}

template< typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::Node* BSTree< Key, Value, Comparator >::rotateRight(Node* node)
{
  if (node == nullptr)
  {
    return nullptr;
  }
  Node* newRoot = node->left_;
  if (newRoot == nullptr)
  {
    return node;
  }
  node->left_ = newRoot->right_;
  if (node->left_ != nullptr)
  {
    node->left_->parent_ = node;
  }
  newRoot->parent_ = node->parent_;
  if (node->parent_ == nullptr)
  {
    root_ = newRoot;
  }
  else if (node == node->parent_->left_)
  {
    node->parent_->left_ = newRoot;
  }
  else
  {
    node->parent_->right_ = newRoot;
  }
  newRoot->right_ = node;
  node->parent_ = newRoot;
  updHeight(node);
  updHeight(newRoot);
  return newRoot;
}

template< typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::Node* BSTree< Key, Value, Comparator >::rotateLeft(Node* node)
{
  if (node == nullptr)
  {
    return nullptr;
  }
  Node* newRoot = node->right_;
  if (newRoot == nullptr)
  {
    return node;
  }
  node->right_ = newRoot->left_;
  if (node->right_ != nullptr)
  {
    node->right_->parent_ = node;
  }
  newRoot->parent_ = node->parent_;
  if (node->parent_ == nullptr)
  {
    root_ = newRoot;
  }
  else
  {
    if (node == node->parent_->left_)
    {
      node->parent_->left_ = newRoot;
    }
    else
    {
      node->parent_->right_ = newRoot;
    }
  }
  newRoot->left_ = node;
  node->parent_ = newRoot;
  updHeight(node);
  updHeight(newRoot);
  return newRoot;
}

template < typename Key, typename Value, typename Comparator >
void BSTree< Key, Value, Comparator >::clear()
{
  free(root_);
  root_ = nullptr;
}

template < typename Key, typename Value, typename Comparator >
void BSTree< Key, Value, Comparator >::free(Node* node)
{
  if (node == nullptr)
  {
    return;
  }
  if (node->left_)
  {
    free(node->left_);
    node->left_ = nullptr;
  }
  if (node->right_)
  {
    free(node->right_);
    node->right_ = nullptr;
  }
  delete node;
}

template< typename Key, typename Value, typename Comparator >
void BSTree< Key, Value, Comparator >::erase(const Key& key)
{
  root_ = erase(root_, key);
  size_--;

}
template< typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::Node* BSTree< Key, Value, Comparator >::erase(Node* node, const Key& key)
{
  if (node == nullptr)
  {
    return nullptr;
  }
  else if (comp_(key, node->data_.first))
  {
    node->left_ = erase(node->left_, key);
  }
  else if (comp_(node->data_.first, key))
  {
    node->right_ = erase(node->right_, key);
  }
  else
  {
    return removeNode(node);
  }
  return node;
}
template< typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::Node* BSTree< Key, Value, Comparator >::removeNode(Node* node)
{
  if (node->right_ == nullptr)
  {
    Node* newRoot = node->left_;
    delete newRoot;
    return newRoot;
  }
  else if (node->left_ == nullptr)
  {
    Node* newRoot = node->right_;
    delete newRoot;
    return newRoot;
  }
  Node* newNode = findMinNode(node->right_);
  node->data_ = newNode->data_;
  node->right_ = erase(node->right_, newNode->data_.first);
  return node;
}
template< typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::Node* BSTree< Key, Value, Comparator >::findMinNode(Node* node)
{
  while (node->left_ != nullptr)
  {
    node = node->left_;
  }
  return node;
}

template < typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::ConstIterator BSTree< Key, Value, Comparator >::find(const Key& key) const
{
  Node* newRoot = root_;
  while (newRoot != nullptr)
  {
    if (!(key < newRoot->data_.first) || (key > newRoot->data_.first))
    {
      return Iterator(newRoot);
    }
    else if (key < newRoot->data_.first)
    {
      newRoot = newRoot->left_;
    }
    else
    {
      newRoot = newRoot->right_;
    }
  }
  return end();
}

template < typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::ConstIterator BSTree< Key, Value, Comparator >::cbegin() const
{
  if (root_ == nullptr)
  {
    return cend();
  }
  Node* newRoot = root_;
  while (newRoot->left_)
  {
    newRoot = newRoot->left_;
  }
  return ConstIterator(newRoot, root_);
}

template < typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::ConstIterator BSTree< Key, Value, Comparator >::cend() const
{
  return ConstIterator(nullptr, root_);
}

template < typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::Iterator BSTree< Key, Value, Comparator >::begin()
{
  return Iterator(cbegin());
}

template < typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator>::Iterator BSTree< Key, Value, Comparator >::end()
{
  return Iterator(cend());
}

#endif
