#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include <utility>
#include <stdexcept>

namespace redko
{
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  class BSTree
  {
  public:

    class Iterator;
    class ConstIterator;

    using value_t = typename std::pair< Key, Value >;

    using iterator = Iterator;
    using const_iterator = ConstIterator;

    BSTree();
    BSTree(const BSTree & other);
    BSTree(BSTree && other);
    BSTree(std::initializer_list< value_t > init);
    ~BSTree();

    Value & at(const Key & key);
    const Value & at(const Key & key) const;
    Value & operator[](const Key & key);
    Value & operator[](Key && key);

    bool empty() const;
    size_t size() const;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    void clear();
    iterator insert(const value_t & value);
    iterator insert(value_t && value);

    void swap(BSTree & other) noexcept;

    iterator find(const Key & key);
    const_iterator find(const Key & key) const;

  private:
    struct Node
    {
      explicit Node(value_t value, Node * p = nullptr, Node * r = nullptr, Node * l = nullptr):
        elem(value),
        parent(p),
        right(r),
        left(l)
      {}

      value_t elem;
      Node * parent;
      Node * right;
      Node * left;
    };

    Node * root_;
    Compare cmp_;

    void deleteSubtree(Node * root);

    size_t getCountNode(Node * root) const;
    size_t getHeight(Node * node);
    int getDiff(Node * node);

    Node * rotateRR(Node * node);
    Node * rotateLL(Node * node);
    Node * rotateRL(Node * node);
    Node * rotateLR(Node * node);
    Node * balance(Node * node);
    Node * insertTo(Node * node, const value_t & value);
    Node * insertTo(Node * node, value_t && value);
  };
}

template < typename Key, typename Value, typename Compare >
class redko::BSTree< Key, Value, Compare >::Iterator: public std::iterator< std::bidirectional_iterator_tag, value_t >
{
  friend class BSTree;
public:

  using this_t = Iterator;

  Iterator();
  Iterator(ConstIterator);
  Iterator(const this_t &) = default;
  ~Iterator() = default;

  this_t & operator=(const this_t &) = default;
  this_t & operator++();
  this_t operator++(int);

  value_t & operator*();
  value_t * operator->();
  const value_t & operator*() const;
  const value_t * operator->() const;

  bool operator==(const this_t &) const;
  bool operator!=(const this_t &) const;

private:
  Node * node_;
  Iterator(Node * ptr);
};

template < typename Key, typename Value, typename Compare >
using iterator = typename redko::BSTree< Key, Value, Compare >::Iterator;

template < typename Key, typename Value >
using value_t = typename std::pair< Key, Value >;

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::Iterator::Iterator():
  node_(nullptr)
{}

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::Iterator::Iterator(ConstIterator iter):
  node_(iter.iter_.node_)
{}

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::Iterator::Iterator(Node * ptr):
  node_(ptr)
{}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::Iterator & redko::BSTree< Key, Value, Compare >::Iterator::operator++()
{
  if (node_ == nullptr)
  {
    throw std::logic_error("Error: unable to increment");
  }
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
    Node * parent = node_->parent;
    while (parent != nullptr && node_ == parent->right) {
      node_ = parent;
      parent = parent->parent;
    }
    node_ = parent;
  }
  return *this;
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::Iterator redko::BSTree< Key, Value, Compare >::Iterator::operator++(int)
{
  Iterator result(*this);
  ++(*this);
  return result;
}

template < typename Key, typename Value, typename Compare >
value_t< Key, Value > & redko::BSTree< Key, Value, Compare >::Iterator::operator*()
{
  return node_->elem;
}

template < typename Key, typename Value, typename Compare >
value_t< Key, Value > * redko::BSTree< Key, Value, Compare >::Iterator::operator->()
{
  return std::addressof(node_->elem);
}

template < typename Key, typename Value, typename Compare >
const value_t< Key, Value > & redko::BSTree< Key, Value, Compare >::Iterator::operator*() const
{
  return node_->elem;
}

template < typename Key, typename Value, typename Compare >
const value_t< Key, Value > * redko::BSTree< Key, Value, Compare >::Iterator::operator->() const
{
  return std::addressof(node_->elem);
}

template < typename Key, typename Value, typename Compare >
bool redko::BSTree< Key, Value, Compare >::Iterator::operator==(const this_t & rhs) const
{
  return node_ == rhs.node_;
}

template < typename Key, typename Value, typename Compare >
bool redko::BSTree< Key, Value, Compare >::Iterator::operator!=(const this_t & rhs) const
{
  return !(rhs == *this);
}

template < typename Key, typename Value, typename Compare >
class redko::BSTree< Key, Value, Compare >::ConstIterator
{
  friend class BSTree;
public:

  using this_t = ConstIterator;

  ConstIterator();
  ConstIterator(Iterator);
  ConstIterator(const this_t &) = default;
  ~ConstIterator() = default;

  this_t & operator=(const this_t &) = default;
  this_t & operator++();
  this_t operator++(int);

  const value_t & operator*() const;
  const value_t * operator->() const;

  bool operator==(const this_t &) const;
  bool operator!=(const this_t &) const;

private:
  Iterator iter_;
};

template < typename Key, typename Value, typename Compare >
using const_iterator = typename redko::BSTree< Key, Value, Compare >::ConstIterator;

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::ConstIterator::ConstIterator():
  iter_(Iterator())
{}

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::ConstIterator::ConstIterator(Iterator iter):
  iter_(iter)
{}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::ConstIterator & redko::BSTree< Key, Value, Compare >::ConstIterator::operator++()
{
  ++iter_;
  return *this;
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::ConstIterator redko::BSTree< Key, Value, Compare >::ConstIterator::operator++(int)
{
  ConstIterator result(iter_);
  ++(iter_);
  return result;
}

template < typename Key, typename Value, typename Compare >
const value_t< Key, Value > & redko::BSTree< Key, Value, Compare >::ConstIterator::operator*() const
{
  return *iter_;
}

template < typename Key, typename Value, typename Compare >
const value_t< Key, Value > * redko::BSTree< Key, Value, Compare >::ConstIterator::operator->() const
{
  return std::addressof(iter_.node_->elem);
}

template < typename Key, typename Value, typename Compare >
bool redko::BSTree< Key, Value, Compare >::ConstIterator::operator==(const this_t & rhs) const
{
  return iter_.node_ == rhs.iter_.node_;
}

template < typename Key, typename Value, typename Compare >
bool redko::BSTree< Key, Value, Compare >::ConstIterator::operator!=(const this_t & rhs) const
{
  return !(rhs == *this);
}

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::BSTree():
  root_(nullptr),
  cmp_(Compare())
{}

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::BSTree(const BSTree & other):
  root_(nullptr),
  cmp_(other.cmp_)
{
  for (Iterator it = other.begin(); it != end(); ++it)
  {
    insert(*it);
  }
}

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::BSTree(BSTree && other):
  root_(nullptr),
  cmp_(std::move(other.cmp_))
{
  for (auto it = other.begin(); it != end(); ++it)
  {
    insert(std::move(*it));
  }
}

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::BSTree(std::initializer_list< value_t > init)
{
  for (auto value: init)
  {
    insert(value);
  }
}

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::~BSTree()
{
  clear();
}

template < typename Key, typename Value, typename Compare >
Value & redko::BSTree< Key, Value, Compare >::at(const Key & key)
{
  Node * curr = root_;
  while (curr != nullptr)
  {
    if (cmp_(curr->elem.first, key))
    {
      curr = curr->right;
    }
    else if (cmp_(key, curr->elem.first))
    {
      curr = curr->left;
    }
    else
    {
      return curr->elem.second;
    }
  }
  throw std::out_of_range("Error: no such element exists");
}

template < typename Key, typename Value, typename Compare >
const Value & redko::BSTree< Key, Value, Compare >::at(const Key & key) const
{
  Node * curr = root_;
  while (curr != nullptr)
  {
    if (cmp_(curr->elem.first, key))
    {
      curr = curr->right;
    }
    else if (cmp_(key, curr->elem.first))
    {
      curr = curr->left;
    }
    else
    {
      return curr->elem.second;
    }
  }
  throw std::out_of_range("Error: no such element exists");
}

template < typename Key, typename Value, typename Compare >
Value & redko::BSTree< Key, Value, Compare >::operator[](const Key & key)
{
  Node * curr = root_;
  while (curr != nullptr)
  {
    if (cmp_(curr->elem.first, key))
    {
      curr = curr->right;
    }
    else if (cmp_(key, curr->elem.first))
    {
      curr = curr->left;
    }
    else
    {
      return curr->elem.second;
    }
  }
  throw std::out_of_range("Error: no such element exists");
}

template < typename Key, typename Value, typename Compare >
Value & redko::BSTree< Key, Value, Compare >::operator[](Key && key)
{
  Node * curr = root_;
  while (curr != nullptr)
  {
    if (cmp_(curr->elem.first, key))
    {
      curr = curr->right;
    }
    else if (cmp_(key, curr->elem.first))
    {
      curr = curr->left;
    }
    else
    {
      return curr->elem.second;
    }
  }
  throw std::out_of_range("Error: no such element exists");
}

template < typename Key, typename Value, typename Compare >
bool redko::BSTree< Key, Value, Compare >::empty() const
{
  return (root_ == nullptr);
}

template < typename Key, typename Value, typename Compare >
size_t redko::BSTree< Key, Value, Compare >::size() const
{
  return getCountNode(root_);
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::iterator redko::BSTree< Key, Value, Compare >::begin() noexcept
{
  Node * curr = root_;
  while (curr != nullptr &&  curr->left != nullptr)
  {
    curr = curr->left;
  }
  return Iterator(curr);
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::const_iterator redko::BSTree< Key, Value, Compare >::begin() const noexcept
{
  Node * curr = root_;
  while (curr != nullptr && curr->left != nullptr)
  {
    curr = curr->left;
  }
  return ConstIterator(curr);
}
template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::const_iterator redko::BSTree< Key, Value, Compare >::cbegin() const noexcept
{
  Node * curr = root_;
  while (curr != nullptr)
  {
    curr = curr->left;
  }
  return ConstIterator(curr);
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::iterator redko::BSTree< Key, Value, Compare >::end() noexcept
{
  return Iterator(nullptr);
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::const_iterator redko::BSTree< Key, Value, Compare >::end() const noexcept
{
  return ConstIterator(nullptr);
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::const_iterator redko::BSTree< Key, Value, Compare >::cend() const noexcept
{
  return ConstIterator(nullptr);
}

template < typename Key, typename Value, typename Compare >
void redko::BSTree< Key, Value, Compare >::clear()
{
  deleteSubtree(root_);
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::iterator redko::BSTree< Key, Value, Compare >::insert(const value_t & value)
{
  root_ = insertTo(root_, value);
  return find(value.first);
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::iterator redko::BSTree< Key, Value, Compare >::insert(value_t && value)
{
  root_ = insertTo(root_, std::move(value));
  return find(value.first);
}

template < typename Key, typename Value, typename Compare >
void redko::BSTree< Key, Value, Compare >::swap(BSTree & other) noexcept
{
  Node * tmp = root_;
  root_ = other.root_;
  other.root_ = tmp;
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::iterator redko::BSTree< Key, Value, Compare >::find(const Key & key)
{
  Node * curr = root_;
  while (curr != nullptr)
  {
    if (cmp_(curr->elem.first, key))
    {
      curr = curr->right;
    }
    else if (cmp_(key, curr->elem.first))
    {
      curr = curr->left;
    }
    else
    {
      return Iterator(curr);
    }
  }
  return end();
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::const_iterator redko::BSTree< Key, Value, Compare >::find(const Key & key) const
{
  Node * curr = root_;
  while (curr != nullptr)
  {
    if (cmp_(curr->elem.first, key))
    {
      curr = curr->right;
    }
    else if (cmp_(key, curr->elem.first))
    {
      curr = curr->left;
    }
    else
    {
      return ConstIterator(curr->elem);
    }
  }
  return cend();
}

template < typename Key, typename Value, typename Compare >
void redko::BSTree< Key, Value, Compare >::deleteSubtree(Node * root)
{
  if (root != nullptr)
  {
    deleteSubtree(root->left);
    deleteSubtree(root->right);
    delete root;
    root = nullptr;
  }
}

template < typename Key, typename Value, typename Compare >
size_t redko::BSTree< Key, Value, Compare >::getCountNode(Node * root) const
{
  if (root == nullptr)
  {
    return 0;
  }
  return (1 + getCountNode(root->left) + getCountNode(root->right));
}

template < typename Key, typename Value, typename Compare >
size_t redko::BSTree< Key, Value, Compare >::getHeight(Node * node)
{
  size_t height = 0;
  if (node != nullptr)
  {
    size_t lHeight = getHeight(node->left);
    size_t rHeight = getHeight(node->right);
    height = std::max(lHeight, rHeight) + 1;
  }
  return height;
}

template < typename Key, typename Value, typename Compare >
int redko::BSTree< Key, Value, Compare >::getDiff(Node * node)
{
  if (node == nullptr)
  {
    return 0;
  }
  return getHeight(node->left) - getHeight(node->right);
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::Node * redko::BSTree< Key, Value, Compare >::rotateLL(Node * node)
{
  Node * tmp = node->right;
  Node * parent = node->parent;
  node->right = tmp->left;
  tmp->left = node;
  tmp->left->parent = tmp;
  tmp->parent = parent;
  return tmp;
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::Node * redko::BSTree< Key, Value, Compare >::rotateRR(Node * node)
{
  Node * tmp = node->left;
  Node * parent = node->parent;
  node->left = tmp->right;
  tmp->right = node;
  tmp->right->parent = tmp;
  tmp->parent = parent;
  return tmp;
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::Node * redko::BSTree< Key, Value, Compare >::rotateRL(Node * node)
{
  node->right = rotateRR(node->right);
  return rotateLL(node);
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::Node * redko::BSTree< Key, Value, Compare >::rotateLR(Node * node)
{
  node->left = rotateLL(node->left);
  return rotateRR(node);
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::Node * redko::BSTree< Key, Value, Compare >::balance(Node * node)
{
  int bFactor = getDiff(node);
  if (bFactor == 2)
  {
    if (getDiff(node->left) > 0)
    {
      node = rotateRR(node);
    }
    else
    {
      node = rotateLR(node);
    }
  }
  else if (bFactor == -2)
  {
    if (getDiff(node->right) > 0)
    {
      node = rotateRL(node);
    }
    else
    {
      node = rotateLL(node);
    }
  }
  return node;
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::Node * redko::BSTree< Key, Value, Compare >::insertTo(Node * node, const value_t & value)
{
  if (node == nullptr)
  {
    node = new Node(value);
    return node;
  }
  else {
    if (cmp_(value.first, node->elem.first))
    {
      node->left = insertTo(node->left, value);
      node->left->parent = node;
    }
    else if (cmp_(node->elem.first, value.first))
    {
      node->right = insertTo(node->right, value);
      node->right->parent = node;
    }
  }
  node = balance(node);
  return node;
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::Node * redko::BSTree< Key, Value, Compare >::insertTo(Node * node, value_t && value)
{
  if (node == nullptr)
  {
    node = new Node(std::move(value));
    return node;
  }
  else {
    if (cmp_(value.first, node->elem.first))
    {
      node->left = insertTo(node->left, std::move(value));
      node->left->parent = node;
    }
    else if (cmp_(node->elem.first, value.first))
    {
      node->right = insertTo(node->right, std::move(value));
      node->right->parent = node;
    }
  }
  node = balance(node);
  return node;
}

#endif
