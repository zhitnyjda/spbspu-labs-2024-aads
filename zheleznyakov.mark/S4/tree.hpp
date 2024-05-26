#ifndef TREE_HPP
#define TREE_HPP
#include <utility>
#include <iostream>
#include <stdexcept>
#include <functional>

namespace zheleznyakov
{
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  class Tree
  {
  public:
    class Iterator;

    using data_t = typename std::pair< Key, Value >;

    Tree();
    Tree(const Tree &);
    ~Tree();

    Tree & operator=(const Tree &);

    size_t size() const;
    bool empty() const;

    Value at(const Key &);

    Value & operator[](const Key& key);
    const Value & operator[](const Key& key) const;

    void push(const Key &, const Value &);
    void clear();

    Iterator begin();
    Iterator end();

  private:
    struct Node
    {
      Node(
        Node * newParent = nullptr,
        Node * newLeft = nullptr,
        Node * newRight = nullptr
      ):
        parent(newParent),
        left(newLeft),
        right(newRight),
        height(1)
      {}
      ~Node() = default;

      data_t data;
      Node * parent;
      Node * left;
      Node * right;
      size_t height;
    };

    Node * root_;

    size_t size(Node *) const;
    void clear(Node *);
    size_t getHeight(Node *);
    int getBalance(Node *);
    Node * rotateRight(Node *);
    Node * rotateLeft(Node *);
    Node * balance(Node *);
  };
}

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare >::Tree():
  root_{nullptr}
{}

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare >::Tree(const Tree & other):
  root_(nullptr)
{
  Node * node_ = other.root_;
  while (node_ != nullptr)
  {
    push(node_->data.first, node_->data.second);
    if (node_->right != nullptr)
    {
      node_ = node_->right;
      while (node_->left != nullptr)
      {
        node_ = node_->left;
      }
    }
    else
    {
      while (node_->parent != nullptr && node_ == node_->parent->right)
      {
        node_ = node_->parent;
      }
      node_ = node_->parent;
    }
  }
}

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare > & zheleznyakov::Tree< Key, Value, Compare >::operator=(const Tree & other)
{
  if (&other != this)
  {
    clear(root_);
    Node * node_ = other.root_;
    while (node_ != nullptr)
    {
      push(node_->data.first, node_->data.second);
      if (node_->right != nullptr)
      {
        node_ = node_->right;
        while (node_->left != nullptr)
        {
          node_ = node_->left;
        }
      }
      else
      {
        while (node_->parent != nullptr && node_ == node_->parent->right)
        {
          node_ = node_->parent;
        }
        node_ = node_->parent;
      }
    }
  }
  return *this;
}

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare >::~Tree()
{
  clear(root_);
}

template < typename Key, typename Value, typename Compare >
class zheleznyakov::Tree< Key, Value, Compare >::Iterator
{
public:
  Iterator();
  Iterator(Node *);
  Iterator(const Iterator&) = default;
  ~Iterator() = default;

  Iterator & operator++();
  Iterator operator++(int);

  bool operator==(const Iterator &) const;
  bool operator!=(const Iterator &) const;

  data_t & operator*();
  data_t * operator->();
private:
  Node * current_;
};

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare >::Iterator::Iterator():
  current_(nullptr)
{}

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare >::Iterator::Iterator(Node * newCurrent):
  current_(newCurrent)
{}

template <typename Key, typename Value, typename Compare>
typename zheleznyakov::Tree<Key, Value, Compare>::Iterator & zheleznyakov::Tree<Key, Value, Compare>::Iterator::operator++()
{
  if (current_ == nullptr) {
    return *this;
  }
  if (current_->right != nullptr) {
    current_ = current_->right;
    while (current_->left != nullptr) {
      current_ = current_->left;
    }
  } else {
    Node * parent = current_->parent;
    while (parent != nullptr && current_ == parent->right) {
      current_ = parent;
      parent = parent->parent;
    }
    current_ = parent;
  }
  return *this;
}

template <typename Key, typename Value, typename Compare>
typename zheleznyakov::Tree<Key, Value, Compare>::Iterator zheleznyakov::Tree<Key, Value, Compare>::Iterator::operator++(int)
{
  Iterator temp = *this;
  ++(*this);
  return temp;
}

template <typename Key, typename Value, typename Compare>
bool zheleznyakov::Tree<Key, Value, Compare>::Iterator::operator==(const Iterator &other) const
{
  return current_ == other.current_;
}

template <typename Key, typename Value, typename Compare>
bool zheleznyakov::Tree<Key, Value, Compare>::Iterator::operator!=(const Iterator &other) const
{
  return current_ != other.current_;
}

template <typename Key, typename Value, typename Compare>
typename zheleznyakov::Tree<Key, Value, Compare>::data_t & zheleznyakov::Tree<Key, Value, Compare>::Iterator::operator*()
{
  return current_->data;
}

template <typename Key, typename Value, typename Compare>
typename zheleznyakov::Tree<Key, Value, Compare>::data_t * zheleznyakov::Tree<Key, Value, Compare>::Iterator::operator->()
{
  return &current_->data;
}

template < typename Key, typename Value, typename Compare >
size_t zheleznyakov::Tree< Key, Value, Compare >::size(Node* node) const
{
  return node != nullptr ? 1 + size(node->left) + size(node->right) : 0;
}

template < typename Key, typename Value, typename Compare >
size_t zheleznyakov::Tree< Key, Value, Compare >::size() const
{
  return size(root_);
}

template < typename Key, typename Value, typename Compare >
bool zheleznyakov::Tree< Key, Value, Compare >::empty() const
{
  return root_ == nullptr;
}

template <typename Key, typename Value, typename Compare>
Value& zheleznyakov::Tree<Key, Value, Compare>::operator[](const Key& key) {
  Node* current = root_;
  Node* parent = nullptr;

  while (current != nullptr)
  {
    parent = current;
    if (key == current->data.first)
    {
      return current->data.second;
    }
    else if (key < current->data.first)
    {
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }

  current = new Node(parent, nullptr, nullptr);
  current->data.first = key;
  current->data.second = Value();
  if (parent == nullptr)
  {
      root_ = current;
  }
  else if (key < parent->data.first)
  {
      parent->left = current;
  }
  else
  {
      parent->right = current;
  }

  return current->data.second;
}

template <typename Key, typename Value, typename Compare>
const Value & zheleznyakov::Tree<Key, Value, Compare>::operator[](const Key& key) const {
  Node * current = root_;
  while (current != nullptr) {
    if (key == current->data.first) {
      return current->data.second;
    } else if (key < current->data.first) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  throw std::out_of_range("No such key");
}


template < typename Key, typename Value, typename Compare >
Value zheleznyakov::Tree< Key, Value, Compare >::at(const Key & k)
{
  Node * current = root_;
  Compare cmp;

  while (current != nullptr)
  {
    if (cmp(current->data.first, k))
    {
      current = current->right;
    }
    else if (cmp(k, current->data.first))
    {
      current = current->left;
    }
    else
    {
      return current->data.second;
    }
  }
  throw std::out_of_range("No such key");
}

template < typename Key, typename Value, typename Compare >
void zheleznyakov::Tree< Key, Value, Compare >::push(const Key& k, const Value& v)
{
  Node* new_node = new Node();
  new_node->data = std::make_pair(k, v);

  Compare cmp;

  if (root_ == nullptr)
  {
    root_ = new_node;
    return;
  }

  Node* current = root_;
  Node* parent = nullptr;

  while (current != nullptr)
  {
    parent = current;
    if (cmp(k, current->data.first))
    {
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }

  new_node->parent = parent;
  if (cmp(k, parent->data.first))
  {
    parent->left = new_node;
  }
  else
  {
    parent->right = new_node;
  }

  root_ = balance(root_);
}

template < typename Key, typename Value, typename Compare >
void zheleznyakov::Tree< Key, Value, Compare>::clear()
{
  if (!empty())
  {
    clear(root_);
  }
}

template < typename Key, typename Value, typename Compare >
void zheleznyakov::Tree< Key, Value, Compare >::clear(Node * node)
{
  if (!node)
  {
    return;
  }
  clear(node->left);
  clear(node->right);
  delete node;
}

template <typename Key, typename Value, typename Compare>
size_t zheleznyakov::Tree< Key, Value, Compare >::getHeight(Node* node)
{
  return node == nullptr ? 0 : node->height;
}

template <typename Key, typename Value, typename Compare>
int zheleznyakov::Tree< Key, Value, Compare >::getBalance(Node* node)
{
  return node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
}

template <typename Key, typename Value, typename Compare>
typename zheleznyakov::Tree< Key, Value, Compare >::Node * zheleznyakov::Tree< Key, Value, Compare >::rotateRight(Node * y)
{
  Node* x = y->left;
  Node* T = x->right;
  x->right = y;
  y->left = T;
  y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
  x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
  return x;
}

template <typename Key, typename Value, typename Compare>
typename zheleznyakov::Tree< Key, Value, Compare >::Node * zheleznyakov::Tree< Key, Value, Compare >::rotateLeft(Node * x)
{
  Node* y = x->right;
  Node* T = y->left;
  y->left = x;
  x->right = T;
  x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
  y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
  return y;
}

template <typename Key, typename Value, typename Compare>
typename zheleznyakov::Tree< Key, Value, Compare >::Node* zheleznyakov::Tree< Key, Value, Compare >::balance(Node * node)
{
  if (node == nullptr)
  {
    return node;
  }
  int balance = getBalance(node);
  if (balance > 1 && getBalance(node->left) >= 0)
  {
    return rotateRight(node);
  }
  if (balance < -1 && getBalance(node->right) <= 0)
  {
    return rotateLeft(node);
  }
  if (balance > 1 && getBalance(node->left) < 0)
  {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }
  if (balance < -1 && getBalance(node->right) > 0)
  {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }
  return node;
}

template <typename Key, typename Value, typename Compare>
typename zheleznyakov::Tree<Key, Value, Compare>::Iterator zheleznyakov::Tree<Key, Value, Compare>::begin()
{
  Node* current = root_;
  while (current != nullptr && current->left != nullptr) {
    current = current->left;
  }
  return Iterator(current);
}

template <typename Key, typename Value, typename Compare>
typename zheleznyakov::Tree<Key, Value, Compare>::Iterator zheleznyakov::Tree<Key, Value, Compare>::end()
{
  return Iterator(nullptr);
}
#endif
