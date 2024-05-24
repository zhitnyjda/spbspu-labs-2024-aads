#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <utility>
#include <algorithm>
#include <stdexcept>

namespace sobolevsky
{
  template< typename Key, typename Value, typename Compare >
  class AVLtree
  {
  public:
    class Iterator;
    class ConstIterator;

    AVLtree();
    AVLtree(const AVLtree< Key, Value, Compare > &tree);
    AVLtree(AVLtree< Key, Value, Compare > &&rhs) noexcept;
    ~AVLtree() = default;

    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;

    size_t size();
    bool empty();

    Value &operator[](const Key &key);
    Value &at(const Key &key);

    void insert(const std::pair< Key, Value > &pair);
    void erase(const Key &key);
    void erase(ConstIterator position);
    void clear();
    void swap(AVLtree &x);

    Iterator find(const Key &key);
    size_t count(const Key &key);
    std::pair<Iterator,Iterator> equal_range (const Key &key);
  private:
    class Node;

    Node *push(const Key &key, const Value &value, Node *node_);
    Node *RightRotate(Node *node_);
    Node *LeftRotate(Node *node_);
    Node *LeftRightRotate(Node *node_);
    Node *RightLeftRotate(Node *node_);
    Node *delet(const Key &key, Node *node_);
    size_t height(Node *node_);
    void recurionDeleteAll(Node *node);

    Node *root;
    size_t size_;
  };
}

template< typename Key, typename Value, typename Compare >
class sobolevsky::AVLtree< Key, Value, Compare >::Node
{
  friend class AVLtree;
public:
  Node(const Key key, const Value value):
    left(nullptr),
    right(nullptr),
    parent(nullptr),
    height(1),
    data(std::pair< Key, Value >(key, value))
  {}
private:
  Node *left;
  Node *right;
  Node *parent;
  size_t height;
  std::pair< Key, Value > data;
};

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::AVLtree()
{
  root = nullptr;
  size_ = 0;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::AVLtree(const AVLtree< Key, Value, Compare > &tree)
{
  root = tree.root;
  size_ = tree.size_;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::AVLtree(AVLtree< Key, Value, Compare > &&rhs) noexcept
{
  root(rhs.root);
  size_ = std::move(rhs.size_);
}

template< typename Key, typename Value, typename Compare >
size_t sobolevsky::AVLtree< Key, Value, Compare >::size()
{
  return size_;
}

template< typename Key, typename Value, typename Compare >
bool sobolevsky::AVLtree< Key, Value, Compare >::empty()
{
  return size_ == 0;
}

template< typename Key, typename Value, typename Compare >
Value &sobolevsky::AVLtree< Key, Value, Compare >::operator[](const Key &key)
{
  Iterator iter(find(key));
  if (iter == end())
  {
    insert(std::pair< Key, Value>(key, Value()));
    iter = find(key);
  }
  return iter->second;
}

template< typename Key, typename Value, typename Compare >
Value &sobolevsky::AVLtree< Key, Value, Compare >::at(const Key &key)
{
  if (find(key) == end())
  {
    throw std::out_of_range("Such key does not exist\n");
  }
  else
  {
    return (find(key))->second;
  }
}

template< typename Key, typename Value, typename Compare >
void sobolevsky::AVLtree< Key, Value, Compare >::insert(const std::pair< Key, Value > &pair)
{
  root = push(pair.first, pair.second, root);
  size_++;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Node *sobolevsky::AVLtree< Key, Value, Compare >::push
(const Key &key, const Value &value, Node *node_)
{
  if (node_ == nullptr)
  {
    node_ = new Node(key, value);
  }
  else if (key < node_->data.first)
  {
    node_->left = push(key, value, node_->left);
    node_->left->parent = node_;
    node_->height++;
    if (height(node_->left) - height(node_->right) > 1)
    {
      if (node_->right == nullptr || key < node_->left->data.first)
      {
        node_ = RightRotate(node_);
      }
      else
      {
        node_ = LeftRightRotate(node_);
      }
    }
  }
  else if (key > node_->data.first)
  {
    node_->right = push(key, value, node_->right);
    node_->right->parent = node_;
    node_->height++;
    if ((height(node_->right) - height(node_->left)) > 1)
    {
      if (node_->left == nullptr || key > node_->right->data.first)
      {
        node_ = LeftRotate(node_);
      }
      else
      {
        node_ = RightLeftRotate(node_);
      }
    }
  }
  return node_;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Node *sobolevsky::AVLtree< Key, Value, Compare >::RightRotate(Node *node_)
{
  Node *temp = node_->left;
  node_->left = temp->right;
  if (node_->left != nullptr)
  {
    node_->left->parent = node_;
  }
  temp->parent = node_->parent;
  node_->parent = temp;
  temp->right = node_;
  node_->height = std::max(height(node_->left), height(node_->right)) + 1;
  temp->height = std::max(node_->height, height(temp->left)) + 1;
  return temp;
}


template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Node *sobolevsky::AVLtree< Key, Value, Compare >::LeftRotate(Node *node_)
{
  Node *temp = node_->right;
  node_->right = temp->left;
  if (node_->right != nullptr)
  {
    node_->right->parent = node_;
  }
  temp->parent = node_->parent;
  node_->parent = temp;
  temp->left = node_;
  node_->height = std::max(height(node_->left), height(node_->right)) + 1;
  temp->height = std::max(node_->height, height(temp->right)) + 1;
  return temp;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Node *sobolevsky::AVLtree< Key, Value, Compare >::LeftRightRotate(Node *node_)
{
  node_->left = LeftRotate(node_->left);
  return RightRotate(node_);
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Node *sobolevsky::AVLtree< Key, Value, Compare >::RightLeftRotate(Node *node_)
{
  node_->right = RightRotate(node_->right);
  return LeftRotate(node_);
}

template< typename Key, typename Value, typename Compare >
void sobolevsky::AVLtree< Key, Value, Compare >::erase(const Key &key)
{
  root = delet(key, root);
  size_--;
}

template< typename Key, typename Value, typename Compare >
void sobolevsky::AVLtree< Key, Value, Compare >::erase(ConstIterator position)
{
  root = delet(position->data.first, root);
  size_--;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Node *sobolevsky::AVLtree< Key, Value, Compare >::delet(const Key &key, Node *node_)
{
  if (node_ == nullptr)
  {
    return nullptr;
  }
  else if (key < node_->data.first)
  {
    node_->left = delet(key, node_->left);
  }
  else if (key > node_->data.first)
  {
    node_->right = delet(key, node_->right);
  }
  else if (node_->left && node_->right)
  {
    Node *temp = node_->right;
    while (temp->left != nullptr)
    {
      temp = temp->left;
    }
    node_->data = temp->data;
    node_->right = delet(node_->data.first, node_->right);
  }
  else
  {
    Node *temp = node_;
    if (node_->left == nullptr)
    {
      node_ = node_->right;
    }
    else if (node_->right== nullptr)
    {
      node_ = node_->left;
    }
  }

  if (node_ == nullptr)
  {
    return nullptr;
  }

  node_->height = std::max(height(node_->left), height(node_->right)) + 1;

  if (height(node_->left) - height(node_->right) > 1 && (node_->right != nullptr) && (node_->left != nullptr))
  {
    if (height(node_->left->left) - height(node_->left->right) > 0)
    {
      return LeftRotate(node_);
    }
    else if (node_->right != nullptr)
    {
      return RightLeftRotate(node_);
    }
  }
  else if (height(node_->right) - height(node_->left) > 1 && (node_->right != nullptr) && (node_->left != nullptr))
  {
    if (height(node_->right->right) - height(node_->right->left) > 0)
    {
      return RightRotate(node_);
    }
    else if (node_->left != nullptr)
    {
      return LeftRightRotate(node_);
    }
  }
  return node_;
}

template< typename Key, typename Value, typename Compare >
size_t sobolevsky::AVLtree< Key, Value, Compare >::height(Node *node_)
{
  return (node_ == nullptr ? 0 : node_->height);
}

template< typename Key, typename Value, typename Compare >
void sobolevsky::AVLtree< Key, Value, Compare >::recurionDeleteAll(Node *node)
{
  if (node != nullptr)
  {
    recurionDeleteAll(node->left);
    recurionDeleteAll(node->right);
    delete node;
  }
}

template< typename Key, typename Value, typename Compare >
void sobolevsky::AVLtree< Key, Value, Compare >::clear()
{
  recurionDeleteAll(root);
  root = nullptr;
  size_ = 0;
}

template< typename Key, typename Value, typename Compare >
void sobolevsky::AVLtree< Key, Value, Compare >::swap(AVLtree &x)
{
  std::swap(root, x.root);
  std::swap(size_, x.size_);
}

template< typename Key, typename Value, typename Compare >
size_t sobolevsky::AVLtree< Key, Value, Compare >::count(const Key &key)
{
  if (find(key) == end())
  {
    return 0;
  }
  return 1;
}

template< typename Key, typename Value, typename Compare >
std::pair< typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator, typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator > sobolevsky::AVLtree< Key, Value, Compare >::equal_range (const Key &key)
{
  if (find(key) == end())
  {
    Iterator iter(begin());
    while (iter != end())
    {
      if ((*iter).first > key)
      {
        break;
      }
      iter++;
    }
    return std::make_pair(iter, iter);
  }
  else
  {
    return std::make_pair(find(key), find(key)++);
  }
}

template< typename Key, typename Value, typename Compare >
class sobolevsky::AVLtree< Key, Value, Compare >::Iterator
{
  friend class AVLtree;
public:
  Iterator();
  Iterator(Node *node);
  Iterator(const Iterator &iter);
  ~Iterator() = default;

  Iterator &operator=(const Iterator &iter);
  Iterator &operator=(Iterator &&rhs);
  std::pair< Key, Value > &operator*();
  std::pair< Key, Value > *operator->();
  Iterator &operator++();
  Iterator operator++(int);
  Iterator &operator--();
  Iterator operator--(int);
  bool operator==(const Iterator &rhs) const;
  bool operator!=(const Iterator &rhs) const;
private:
  Node *node_;
};

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::Iterator::Iterator()
{
  node_(nullptr);
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::Iterator::Iterator(Node *node)
{
  node_ = node;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::Iterator::Iterator(const Iterator &iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator &sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator=(const Iterator &iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator &sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator=(Iterator &&rhs)
{
  node_ = rhs.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
std::pair< Key, Value > &sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator*()
{
  return node_->data;
}

template< typename Key, typename Value, typename Compare >
std::pair< Key, Value > *sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator->()
{
  return std::addressof(node_->data);
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator &sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator++()
{
  if (node_ == nullptr)
  {
    return *this;
  }
  else if (node_->right == nullptr)
  {
    Node *temp = node_->parent;
    while (temp != nullptr && node_ == temp->right)
    {
      node_ = temp;
      temp = node_->parent;
    }
    node_ = temp;
    return *this;
  }
  else
  {
    node_ = node_->right;
    if (node_->left == nullptr)
    {
      return *this;
    }
    while (node_->left != nullptr)
    {
      node_ = node_->left;
    }
    return *this;
  }
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator++(int)
{
  Iterator temp(*this);
  ++(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator &sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator--()
{
  if (node_ == nullptr)
  {
    return *this;
  }
  else if (node_->left == nullptr)
  {
    Node *temp = node_->parent;
    while (temp != nullptr && node_ == temp->left)
    {
      node_ = temp;
      temp = node_->parent;
    }
    node_ = temp;
    return *this;
  }
  else
  {
    node_ = node_->left;
    while (node_->right != nullptr)
    {
      node_ = node_->right;
    }
    return *this;
  }
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator--(int)
{
  Iterator temp(*this);
  --(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
bool sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator==(const Iterator &rhs) const
{
  return node_ == rhs.node_;
}

template< typename Key, typename Value, typename Compare >
bool sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator!=(const Iterator &rhs) const
{
  return node_ != rhs.node_;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator sobolevsky::AVLtree< Key, Value, Compare >::begin() noexcept
{
  Node *temp = root;
  while (temp->left != nullptr)
  {
    temp = temp->left;
  }
  return Iterator(temp);
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator sobolevsky::AVLtree< Key, Value, Compare >::end() noexcept
{
  return Iterator(nullptr);
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator sobolevsky::AVLtree< Key, Value, Compare >::cbegin() const noexcept
{
  Node *temp = root;
  while (temp->left != nullptr)
  {
    temp = temp->left;
  }
  return ConstIterator(temp);
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator sobolevsky::AVLtree< Key, Value, Compare >::cend() const noexcept
{
  return ConstIterator(nullptr);
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator sobolevsky::AVLtree< Key, Value, Compare >::find(const Key &key)
{
  Node *temp = root;
  while (temp)
  {
    if (temp->data.first == key)
    {
      return Iterator(temp);
    }
    else if (key > temp->data.first)
    {
      temp = temp->right;
    }
    else if (key < temp->data.first)
    {
      temp = temp->left;
    }
  }
  return end();
}

template< typename Key, typename Value, typename Compare >
class sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator
{
  friend class AVLtree;
public:
  ConstIterator();
  explicit ConstIterator(const Node *node);
  ConstIterator(const ConstIterator &iter);
  ~ConstIterator() = default;

  ConstIterator &operator=(const ConstIterator &iter);
  ConstIterator &operator=(ConstIterator &&rhs);
  const std::pair< Key, Value > &operator*() const;
  const std::pair< Key, Value > *operator->() const;
  ConstIterator &operator++();
  ConstIterator operator++(int);
  ConstIterator &operator--();
  ConstIterator operator--(int);
  bool operator==(const ConstIterator &rhs) const;
  bool operator!=(const ConstIterator &rhs) const;
private:
  const Node *node_;
};

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::ConstIterator()
{
  node_(nullptr);
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::ConstIterator(const Node *node)
{
  node_ = node;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::ConstIterator(const ConstIterator &iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator &sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::operator=(const ConstIterator &iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator &sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::operator=(ConstIterator &&rhs)
{
  node_(rhs.node_);
  return *this;
}

template< typename Key, typename Value, typename Compare >
const std::pair< Key, Value > &sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::operator*() const
{
  return node_->data;
}

template< typename Key, typename Value, typename Compare >
const std::pair< Key, Value > *sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::operator->() const
{
  return std::addressof(node_->data);
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator &sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::operator++()
{
  if (node_ == nullptr)
  {
    return *this;
  }
  else if (node_->right == nullptr)
  {
    Node *temp = node_->parent;
    while (temp != nullptr && node_ == temp->right)
    {
      node_ = temp;
      temp = node_->parent;
    }
    node_ = temp;
    return *this;
  }
  else
  {
    node_ = node_->right;
    if (node_->left == nullptr)
    {
      return *this;
    }
    while (node_->left != nullptr)
    {
      node_ = node_->left;
    }
    return *this;
  }
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::operator++(int)
{
  ConstIterator temp(*this);
  ++(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator &sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::operator--()
{
  if (node_ == nullptr)
  {
    return *this;
  }
  else if (node_->left == nullptr)
  {
    Node *temp = node_->parent;
    while (temp != nullptr && node_ == temp->left)
    {
      node_ = temp;
      temp = node_->parent;
    }
    node_ = temp;
    return *this;
  }
  else
  {
    node_ = node_->left;
    while (node_->right != nullptr)
    {
      node_ = node_->right;
    }
    return *this;
  }
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::operator--(int)
{
  ConstIterator temp(*this);
  --(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
bool sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::operator==(const ConstIterator &rhs) const
{
  return node_ == rhs.node_;
}

template< typename Key, typename Value, typename Compare >
bool sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::operator!=(const ConstIterator &rhs) const
{
  return node_ != rhs.node_;
}

#endif
