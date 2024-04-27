#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include <functional>
#include <utility>
#include <iterator>
#include <cmath>

namespace khoroshkin
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class Map
  {
  public:
    class Node;
    class Iterator;
    class ConstIterator;

    using iterator = Iterator;
    using const_iterator = ConstIterator;
    using value_type = std::pair< const Key, Value >;

    Map();
    Map(const Map & rhs);
    ~Map();

    void insert(Key key, Value value);
    void insert(value_type pair);
    iterator find(const Key & key);
    Value & operator[](const Key & key);
    void clear();

    bool isEmpty() const;
    size_t getSize() const;

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

  private:
    Node * root;
    size_t size;

    Node * insert(Key k, Value v, Node * node, Node * prev);
    iterator find(const Key & key, Node * node);
    void clear(Node * node);

    int getHeight(Node * node);
    void updateHeight(Node * node);
    int checkBalance(Node * node);
    Node * isBalanced(Node * node);

    void leftRotate(Node * node);
    void rightRotate(Node * node);
    void rightLeftRotate(Node * node);
    void leftRightRotate(Node * node);

    Node * copyMap(Node * node, Node * parent);
  };
}

template< typename Key, typename Value, typename Compare >
class khoroshkin::Map< Key, Value, Compare >::Node
{
public:
  friend class Map;

  Node(Key key_, Value data_, Node * parent = nullptr, int height_ = 0, Node * left_ = nullptr, Node * right_ = nullptr);

private:
  value_type kv_pair;
  Node * left;
  Node * right;
  Node * parent;
  int height;
};

template< typename Key, typename Value, typename Compare >
khoroshkin::Map< Key, Value, Compare >::Node::Node(Key key_, Value data_, Node * parent_, int height_, Node * left_, Node * right_) :
  kv_pair(std::make_pair(key_, data_)), parent(parent_), left(left_), right(right_), height(height_)
{}

template< typename Key, typename Value, typename Compare >
typename khoroshkin::Map< Key,Value,Compare >::Node * khoroshkin::Map< Key,Value,Compare >::insert(Key k, Value v, Node* node, Node * prev)
{
  Compare comp;
  if (node == nullptr)
  {
    node = new Node(k, v, prev);
    size++;
  }
  else if (comp(k, node->kv_pair.first))
  {
    node->left = insert(k, v, node->left, node);
  }
  else if (!comp(k, node->kv_pair.first))
  {
    node->right = insert(k, v, node->right, node);
  }
  return node;
}

template< typename Key, typename Value, typename Compare >
typename khoroshkin::Map< Key, Value, Compare >::iterator khoroshkin::Map< Key, Value, Compare >::find(const Key & key, Node * node)
{
  Compare comp;
  if (node == nullptr)
  {
    return Iterator(ConstIterator(nullptr, root));
  }
  if (node->kv_pair.first == key)
  {
    return Iterator(ConstIterator(node, root));
  }
  else if (comp(key, node->kv_pair.first))
  {
    return find(key, node->left);
  }
  else if (!comp(key, node->kv_pair.first))
  {
    return find(key, node->right);
  }
  throw std::logic_error("such element not exist");
}

template< typename Key, typename Value, typename Compare >
void khoroshkin::Map< Key, Value, Compare >::clear(Node * node)
{
  if (node == nullptr)
  {
    return;
  }
  clear(node->left);
  clear(node->right);
  delete node;
}

template< typename Key, typename Value, typename Compare >
class khoroshkin::Map< Key, Value, Compare >::ConstIterator : public std::iterator< std::bidirectional_iterator_tag, value_type >
{
  public:
    friend class Map< Key, Value, Compare >;
    using this_t = ConstIterator;

    ConstIterator();
    ConstIterator(const this_t&) = default;
    ~ConstIterator() = default;

    this_t & operator=(const this_t &) = default;
    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);

    const value_type & operator*() const;
    const value_type * operator->() const;

    bool operator!=(const this_t & rhs) const;
    bool operator==(const this_t & rhs) const;

  private:
    Node * node_;
    Node * root_;
    ConstIterator(Node * node, Node * root);
};

template< typename Key, typename Value, typename Compare >
khoroshkin::Map< Key, Value, Compare >::ConstIterator::ConstIterator() :
  node_(nullptr), root_(nullptr)
{}

template< typename Key, typename Value, typename Compare >
khoroshkin::Map< Key, Value, Compare >::ConstIterator::ConstIterator(Node * node, Node * root) :
  node_(node), root_(root)
{}

template< typename Key, typename Value, typename Compare >
typename khoroshkin::Map< Key, Value, Compare >::ConstIterator & khoroshkin::Map< Key, Value, Compare >::ConstIterator::operator++()
{
  if (node_->right)
  {
    node_ = node_->right;
    while (node_->left)
    {
      node_ = node_->left;
    }
  }
  else
  {
    Node * tempParent = node_->parent;
    while (tempParent && node_ == tempParent->right)
    {
      node_ = tempParent;
      tempParent = node_->parent;
    }
    node_ = tempParent;
  }
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename khoroshkin::Map< Key, Value, Compare >::ConstIterator khoroshkin::Map< Key, Value, Compare >::ConstIterator::operator++(int)
{
  this_t result(*this);
  ++(*this);
  return result;
}

template< typename Key, typename Value, typename Compare >
typename khoroshkin::Map< Key, Value, Compare >::ConstIterator & khoroshkin::Map< Key, Value, Compare >::ConstIterator::operator--()
{
  if (node_ == nullptr)
  {
    node_ = root_;
    while (node_->right)
    {
      node_ = node_->right;
    }
  }
  else
  {
    if (node_->left)
    {
      node_ = node_->left;
      while (node_->right)
      {
        node_ = node_->right;
      }
    }
    else
    {
      Node * tempParent = node_->parent;
      while (tempParent && node_ == tempParent->left)
      {
        node_ = tempParent;
        tempParent = node_->parent;
      }
      node_ = tempParent;
    }
  }
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename khoroshkin::Map< Key, Value, Compare >::ConstIterator khoroshkin::Map< Key, Value, Compare >::ConstIterator::operator--(int)
{
  this_t result(*this);
  --(*this);
  return result;
}

template < typename Key, typename Value, typename Compare >
const typename khoroshkin::Map< Key,Value,Compare >::value_type & khoroshkin::Map< Key,Value,Compare >::ConstIterator::operator*() const
{
  return node_->kv_pair;
}

template < typename Key, typename Value, typename Compare >
const typename khoroshkin::Map< Key,Value,Compare >::value_type * khoroshkin::Map< Key,Value,Compare >::ConstIterator::operator->() const
{
  return std::addressof(node_->kv_pair);
}

template < typename Key, typename Value, typename Compare >
bool khoroshkin::Map< Key, Value, Compare >::ConstIterator::operator==(const this_t & rhs) const
{
  return node_ == rhs.node_;
}

template < typename Key, typename Value, typename Compare >
bool khoroshkin::Map< Key, Value, Compare >::ConstIterator::operator!=(const this_t & rhs) const
{
  return !(*this == rhs);
}

template< typename Key, typename Value, typename Compare >
class khoroshkin::Map< Key, Value, Compare >::Iterator : public std::iterator< std::bidirectional_iterator_tag, Key, Value, Compare >
{
  public:
    friend class Map< Key, Value, Compare >;
    using this_t = Iterator;
    Iterator();
    Iterator(ConstIterator iter);
    Iterator(const this_t &) = default;
    ~Iterator() = default;

    this_t & operator=(const this_t &) = default;
    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);

    value_type & operator*();
    value_type * operator->();
    const value_type & operator*() const;
    const value_type * operator->() const;

    bool operator!=(const this_t&) const;
    bool operator==(const this_t&) const;

  private:
    ConstIterator iter_;
};

template< typename Key, typename Value, typename Compare >
khoroshkin::Map< Key, Value, Compare >::Iterator::Iterator() :
  iter_(ConstIterator())
{}

template< typename Key, typename Value, typename Compare >
khoroshkin::Map< Key, Value, Compare >::Iterator::Iterator(ConstIterator iter) :
  iter_(iter)
{}

template< typename Key, typename Value, typename Compare >
typename khoroshkin::Map< Key, Value, Compare >::Iterator::this_t & khoroshkin::Map< Key, Value, Compare >::Iterator::operator++()
{
  ++iter_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename khoroshkin::Map< Key, Value, Compare >::Iterator::this_t khoroshkin::Map< Key, Value, Compare >::Iterator::operator++(int)
{
  this_t result = iter_;
  ++iter_;
  return result;
}

template< typename Key, typename Value, typename Compare >
typename khoroshkin::Map< Key, Value, Compare >::Iterator & khoroshkin::Map< Key, Value, Compare >::Iterator::operator--()
{
  --iter_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename khoroshkin::Map< Key, Value, Compare >::Iterator khoroshkin::Map< Key, Value, Compare >::Iterator::operator--(int)
{
  this_t result = iter_;
  --iter_;
  return result;
}

template< typename Key, typename Value, typename Compare >
typename khoroshkin::Map< Key, Value, Compare >::value_type & khoroshkin::Map< Key, Value, Compare >::Iterator::operator*()
{
  return iter_.node_->kv_pair;
}

template< typename Key, typename Value, typename Compare >
typename khoroshkin::Map< Key, Value, Compare >::value_type * khoroshkin::Map< Key, Value, Compare >::Iterator::operator->()
{
  return std::addressof(iter_.node_->kv_pair);
}

template< typename Key, typename Value, typename Compare >
const typename khoroshkin::Map< Key, Value, Compare >::value_type & khoroshkin::Map< Key, Value, Compare >::Iterator::operator*() const
{
  return iter_.node_->kv_pair;
}

template< typename Key, typename Value, typename Compare >
const typename khoroshkin::Map< Key, Value, Compare >::value_type * khoroshkin::Map< Key, Value, Compare >::Iterator::operator->() const
{
  return std::addressof(iter_.node_->kv_pair);
}

template< typename Key, typename Value, typename Compare >
bool khoroshkin::Map< Key, Value, Compare >::Iterator::operator!=(const this_t & rhs) const
{
  return !(rhs == *this);
}

template< typename Key, typename Value, typename Compare >
bool khoroshkin::Map< Key, Value, Compare >::Iterator::operator==(const this_t & rhs) const
{
  return iter_ == rhs.iter_;
}

template< typename Key, typename Value, typename Compare >
khoroshkin::Map< Key, Value, Compare >::Map() :
  root(nullptr), size(0)
{}

template< typename Key, typename Value, typename Compare >
khoroshkin::Map< Key, Value, Compare >::Map(const Map & rhs) :
  root(nullptr), size(0)
{
  root = copyMap(rhs.root, nullptr);
  size = rhs.size;
}

template< typename Key, typename Value, typename Compare >
khoroshkin::Map< Key, Value, Compare >::~Map()
{
  clear();
  root = nullptr;
}

template< typename Key, typename Value, typename Compare >
void khoroshkin::Map< Key, Value, Compare >::insert(khoroshkin::Map< Key, Value, Compare >::value_type pair)
{
  insert(pair.first, pair.second);
}

template< typename Key, typename Value, typename Compare >
void khoroshkin::Map< Key, Value, Compare >::insert(Key key, Value value)
{
  root = insert(key, value, root, nullptr);
  updateHeight(find(key).iter_.node_);
  Node * overweight = isBalanced(find(key).iter_.node_);
  while (overweight)
  {
    if (checkBalance(overweight) == 2)
    {
      if (checkBalance(overweight->right) >= 0)
      {
        leftRotate(overweight);
      }
      else
      {
        rightLeftRotate(overweight);
      }
    }
    else
    {
      if (checkBalance(overweight->left) < 0)
      {
        rightRotate(overweight);
      }
      else
      {
        leftRightRotate(overweight);
      }
    }
    overweight = isBalanced(overweight);
  }
}

template< typename Key, typename Value, typename Compare >
void khoroshkin::Map< Key, Value, Compare >::leftRotate(Node * node)
{
  if (node->parent)
  {
    Node * parent = node->parent;
    Node * newChild;
    if (parent->right == node)
    {
      parent->right = node->right;
      newChild = parent->right;
    }
    else
    {
      parent->left = node->right;
      newChild = parent->left;
    }
    node->right = node->right->left;
    newChild->left = node;
    updateHeight(node);
    updateHeight(newChild);
  }
  else
  {
    Node * temp = node;
    root = node->right;
    temp->right = root->right->left;
    root->left = temp;
    temp->parent = root;
    root->parent = nullptr;
    updateHeight(root->left);
    updateHeight(root);
  }
}

template< typename Key, typename Value, typename Compare >
void khoroshkin::Map< Key, Value, Compare >::rightRotate(Node * node)
{
  if (node->parent)
  {
    Node * parent = node->parent;
    Node * newChild;
    if (parent->left == node)
    {
      parent->left = node->left;
      newChild = parent->left;
    }
    else
    {
      parent->right = node->left;
      newChild = parent->right;
    }
    node->left = node->left->right;
    newChild->right = node;
    updateHeight(node);
    updateHeight(newChild);
  }
  else
  {
    Node * temp = node;
    root = node->left;
    temp->left = root->left->right;
    root->right = temp;
    temp->parent = root;
    root->parent = nullptr;
    updateHeight(root->right);
    updateHeight(root);
  }
}

template< typename Key, typename Value, typename Compare >
void khoroshkin::Map< Key, Value, Compare >::rightLeftRotate(Node * node)
{
  rightRotate(node->right);
  leftRotate(node);
}

template< typename Key, typename Value, typename Compare >
void khoroshkin::Map< Key, Value, Compare >::leftRightRotate(Node * node)
{
  leftRotate(node->left);
  rightRotate(node);
}

template< typename Key, typename Value, typename Compare >
typename khoroshkin::Map< Key, Value, Compare >::iterator khoroshkin::Map< Key, Value, Compare >::find(const Key & key)
{
  return find(key, root);
}

template< typename Key, typename Value, typename Compare >
Value & khoroshkin::Map< Key, Value, Compare >::operator[](const Key & key)
{
  return (*find(key, root)).second;
}

template< typename Key, typename Value, typename Compare >
void khoroshkin::Map< Key, Value, Compare >::clear()
{
  clear(root);
}

template< typename Key, typename Value, typename Compare >
bool khoroshkin::Map< Key, Value, Compare >::isEmpty() const
{
  return !size;
}

template< typename Key, typename Value, typename Compare >
size_t khoroshkin::Map< Key, Value, Compare >::getSize() const
{
  return size;
}

template< typename Key, typename Value, typename Compare >
typename khoroshkin::Map< Key, Value, Compare >::iterator khoroshkin::Map< Key, Value, Compare >::begin() noexcept
{
  if (isEmpty())
  {
    return cend();
  }
  Node * temp = root;
  while (temp->left != nullptr)
  {
    temp = temp->left;
  }
  return Iterator(ConstIterator(temp, root));
}

template< typename Key, typename Value, typename Compare >
typename khoroshkin::Map< Key, Value, Compare >::iterator khoroshkin::Map< Key, Value, Compare >::end() noexcept
{
  return Iterator(ConstIterator(nullptr, root));
}

template< typename Key, typename Value, typename Compare >
typename khoroshkin::Map< Key, Value, Compare >::const_iterator khoroshkin::Map< Key, Value, Compare >::cbegin() const noexcept
{
  if (isEmpty())
  {
    return cend();
  }
  Node * temp = root;
  while (temp->left != nullptr)
  {
    temp = temp->left;
  }
  return ConstIterator(temp, root);
}

template< typename Key, typename Value, typename Compare >
typename khoroshkin::Map< Key, Value, Compare >::const_iterator khoroshkin::Map< Key, Value, Compare >::cend() const noexcept
{
  return ConstIterator(nullptr, root);
}

template< typename Key, typename Value, typename Compare >
int khoroshkin::Map< Key, Value, Compare >::getHeight(Node * node)
{
  return (node) ? node->height : 0;
}

template< typename Key, typename Value, typename Compare >
void khoroshkin::Map< Key, Value, Compare >::updateHeight(Node * node)
{
  if (!node)
  {
    return;
  }
  if (!node->left && !node->right)
  {
    node->height = 1;
  }
  else
  {
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
  }
  updateHeight(node->parent);
}

template< typename Key, typename Value, typename Compare >
int khoroshkin::Map< Key, Value, Compare >::checkBalance(Node * node)
{
  return getHeight(node->right) - getHeight(node->left);
}

template< typename Key, typename Value, typename Compare >
typename khoroshkin::Map< Key, Value, Compare >::Node * khoroshkin::Map< Key, Value, Compare >::isBalanced(Node * node)
{
  Node * temp = node;
  while (temp)
  {
    if (std::abs(checkBalance(temp)) > 1)
    {
      return temp;
    }
    temp = temp->parent;
  }
  return nullptr;
}

template< typename Key, typename Value, typename Compare >
typename khoroshkin::Map< Key, Value, Compare >::Node * khoroshkin::Map< Key, Value, Compare >::copyMap(Node * node, Node * parent)
{
  if (node == nullptr)
  {
    return nullptr;
  }
  Node * newnode = new Node(node->kv_pair.first, node->kv_pair.second, parent, node->height);
  newnode->left = copyMap(node->left, newnode);
  newnode->right = copyMap(node->right, newnode);
  return newnode;
}

#endif
