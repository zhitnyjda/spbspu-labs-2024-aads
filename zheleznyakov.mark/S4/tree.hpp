#ifndef TREE_HPP
#define TREE_HPP
#include <utility>
#include <iostream>
#include <stdexcept>
#include <functional>

namespace zheleznyakov {
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  class Tree {
  public:
    using data_t = typename std::pair< Key, Value >;

    Tree();
    Tree(const Tree & other);
    ~Tree();

    Tree & operator=(const Tree & other);

    size_t size() const;
    bool empty() const;

    Value at(const Key & k);

    void push(const Key &, const Value &);
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
        right(newRight)
      {}
      ~Node() = default;

      data_t data;
      Node * parent;
      Node * left;
      Node * right;
    };

    Node * root_;

    size_t size(Node * node) const;
    void clear(Node * node);
  };
}

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
zheleznyakov::Tree< Key, Value, Compare >::Tree():
  root_{nullptr}
{}

template < typename Key, typename Value, typename Compare >
size_t zheleznyakov::Tree<Key, Value, Compare>::size(Node* node) const
{
  return node != nullptr ? 1 + size(node->left) + size(node->right) : 0;
}

template < typename Key, typename Value, typename Compare >
size_t zheleznyakov::Tree<Key, Value, Compare>::size() const
{
  return size(root_);
}

template < typename Key, typename Value, typename Compare >
bool zheleznyakov::Tree<Key, Value, Compare>::empty() const
{
  return root_ == nullptr;
}

template < typename Key, typename Value, typename Compare >
Value zheleznyakov::Tree< Key, Value, Compare >::at(const Key & k) {
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
void zheleznyakov::Tree<Key, Value, Compare>::push(const Key & k, const Value & v) {
  Node * new_node = new Node();
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
}

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare >::~Tree()
{
  clear(root_);
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
#endif
