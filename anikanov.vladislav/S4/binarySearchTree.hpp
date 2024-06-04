#ifndef BinarySearchTree_HPP
#define BinarySearchTree_HPP

#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <iosfwd>
//#include <list.hpp>
#include "../common/list.hpp"

namespace anikanov {
  template< typename Key, typename Value, typename Compare >
  class BinarySearchTree;
}

template< typename Key, typename Value, typename Compare >
std::ostream &operator<<(std::ostream &os, const anikanov::BinarySearchTree< Key, Value, Compare > &tree)
{
  anikanov::List< std::pair< Key, Value > > list;
  tree.inOrder(tree.root.get(), list);
  for (size_t i = 0; i < list.size(); ++i) {
    auto p = list[i];
    os << p.first << " " << p.second;
    if (i != list.size() - 1){
      os << " ";
    }
  }
  return os;
}

namespace anikanov {
  template< typename Key, typename Value, typename Compare >
  class BinarySearchTree {
  public:
    struct Node {
      std::pair< Key, Value > data;
      std::shared_ptr< Node > left;
      std::shared_ptr< Node > right;
      std::weak_ptr< Node > parent;
      int height;

      Node(const Key &key, const Value &value, std::shared_ptr< Node > parent = nullptr) : data(key, value),
                                                                                           left(nullptr),
                                                                                           right(nullptr),
                                                                                           parent(parent),
                                                                                           height(1)
      {}

      Node(std::shared_ptr< Node > &node) : data(node->data),
                                            left(std::move(node->left)),
                                            right(std::move(node->right)),
                                            parent(node->parent.lock()),
                                            height(node->height)
      {}
    };

    BinarySearchTree() : root(nullptr), nodeCount(0)
    {}

    ~BinarySearchTree();
    BinarySearchTree(const BinarySearchTree &other);
    BinarySearchTree(BinarySearchTree &&other) noexcept;
    BinarySearchTree &operator=(const BinarySearchTree &other);
    BinarySearchTree &operator=(BinarySearchTree &&other) noexcept;

    class Iterator {
    private:
      Node *current;
      Node *findNext(Node *node) const;
      Node *findPrev(Node *node) const;
    public:
      Iterator();
      explicit Iterator(Node *node);
      std::pair< Key, Value > &operator*();
      std::pair< Key, Value > *operator->();
      Iterator &operator++();
      Iterator operator++(int);
      Iterator &operator--();
      Iterator operator--(int);
      bool operator==(const Iterator &other) const;
      bool operator!=(const Iterator &other) const;
    };

    class ConstIterator {
    private:
      Iterator iter;
    public:
      ConstIterator(Iterator it);
      const std::pair< Key, Value > &operator*() const;
      const std::pair< Key, Value > *operator->() const;
      ConstIterator &operator++();
      ConstIterator operator++(int);
      ConstIterator &operator--();
      ConstIterator operator--(int);
      bool operator==(const ConstIterator &other) const;
      bool operator!=(const ConstIterator &other) const;
    };

    void push(const Key &key, const Value &value);
    Value &operator[](const Key &key);
    const Value &operator[](const Key &key) const;
    void drop(const Key &key);
    bool empty() const;
    size_t size() const;
    void clear();
    void swap(BinarySearchTree &other);
    ConstIterator begin() const;
    ConstIterator end() const;
    Iterator begin();
    Iterator end();
    ConstIterator find(const Key &key) const;
    std::pair< ConstIterator, ConstIterator > equalRange(const Key &key) const;
    size_t count(const Key &key) const;
    void insert(const std::pair< Key, Value > &pair);
    void erase(const Key &key);
    void print() const;
    friend std::ostream &operator
    <<< Key, Value, Compare >(
    std::ostream &os,
    const BinarySearchTree &tree
    );

  private:
    std::shared_ptr< Node > root;
    size_t nodeCount;
    Compare comp;
    int height(Node *n) const;
    int balanceFactor(Node *n) const;
    void updateHeight(Node *n);
    std::shared_ptr< Node > rotateRight(std::shared_ptr< Node > y);
    std::shared_ptr< Node > rotateLeft(std::shared_ptr< Node > x);
    std::shared_ptr< Node > balance(std::shared_ptr< Node > n);
    std::shared_ptr< Node >
    insert(std::shared_ptr< Node > node, const Key &key, const Value &value, std::shared_ptr< Node > parent);
    std::shared_ptr< Node > erase(std::shared_ptr< Node > node, const Key &key);
    Node *minValueNode(Node *node) const;
    Node *find(Node *node, const Key &key) const;
    void inOrder(Node *node, List< std::pair< Key, Value >> &list) const;
    std::shared_ptr< Node > clone(const Node *node) const;
  };
}

template< typename Key, typename Value, typename Compare >
anikanov::BinarySearchTree< Key, Value, Compare >::~BinarySearchTree()
{
  clear();
}

template< typename Key, typename Value, typename Compare >
anikanov::BinarySearchTree< Key, Value, Compare >::BinarySearchTree(const BinarySearchTree &other) :
    nodeCount(other.nodeCount),
    comp(other.comp)
{
  nodeCount = other.nodeCount;
  comp = other.comp;
  root = clone(other.root.get());
}

template< typename Key, typename Value, typename Compare >
anikanov::BinarySearchTree< Key, Value, Compare >::BinarySearchTree(BinarySearchTree &&other) noexcept
{
  root = std::move(other.root);
  nodeCount = other.nodeCount;
  comp = std::move(other.comp);
  other.nodeCount = 0;
}

template< typename Key, typename Value, typename Compare >
anikanov::BinarySearchTree< Key, Value, Compare > &
anikanov::BinarySearchTree< Key, Value, Compare >::operator=(const BinarySearchTree &other)
{
  if (this == &other) return *this;
  root = clone(other.root.get());
  nodeCount = other.nodeCount;
  comp = other.comp;
  return *this;
}

template< typename Key, typename Value, typename Compare >
anikanov::BinarySearchTree< Key, Value, Compare > &
anikanov::BinarySearchTree< Key, Value, Compare >::operator=(BinarySearchTree &&other) noexcept
{
  if (this == &other) return *this;
  root = std::move(other.root);
  nodeCount = other.nodeCount;
  comp = std::move(other.comp);
  other.nodeCount = 0;
  return *this;
}

template< typename Key, typename Value, typename Compare >
void anikanov::BinarySearchTree< Key, Value, Compare >::push(const Key &key, const Value &value)
{
  root = insert(std::move(root), key, value, nullptr);
}

template< typename Key, typename Value, typename Compare >
const Value &anikanov::BinarySearchTree< Key, Value, Compare >::operator[](const Key &key) const
{
  Node *node = find(root.get(), key);
  if (!node) throw std::runtime_error("Key not found");
  return node->data.second;
}

template< typename Key, typename Value, typename Compare >
Value &anikanov::BinarySearchTree< Key, Value, Compare >::operator[](const Key &key)
{
  Node *node = find(root.get(), key);
  if (!node) {
    root = insert(std::move(root), key, Value());
    node = find(root.get(), key);
  }
  return node->data.second;
}

template< typename Key, typename Value, typename Compare >
void anikanov::BinarySearchTree< Key, Value, Compare >::drop(const Key &key)
{
  root = erase(std::move(root), key);
}

template< typename Key, typename Value, typename Compare >
bool anikanov::BinarySearchTree< Key, Value, Compare >::empty() const
{
  return nodeCount == 0;
}

template< typename Key, typename Value, typename Compare >
size_t anikanov::BinarySearchTree< Key, Value, Compare >::size() const
{
  return nodeCount;
}

template< typename Key, typename Value, typename Compare >
void anikanov::BinarySearchTree< Key, Value, Compare >::swap(BinarySearchTree &other)
{
  std::swap(root, other.root);
  std::swap(nodeCount, other.nodeCount);
  std::swap(comp, other.comp);
}

template< typename Key, typename Value, typename Compare >
anikanov::BinarySearchTree< Key, Value, Compare >::Iterator::Iterator()
{
  current = nullptr;
}

template< typename Key, typename Value, typename Compare >
anikanov::BinarySearchTree< Key, Value, Compare >::Iterator::Iterator(
    BinarySearchTree< Key, Value, Compare >::Node *node)
{
  current = node;
}

template< typename Key, typename Value, typename Compare >
std::pair< Key, Value > &anikanov::BinarySearchTree< Key, Value, Compare >::Iterator::operator*()
{
  return current->data;
}

template< typename Key, typename Value, typename Compare >
std::pair< Key, Value > *anikanov::BinarySearchTree< Key, Value, Compare >::Iterator::operator->()
{
  return &current->data;
}

template< typename Key, typename Value, typename Compare >
typename anikanov::BinarySearchTree< Key, Value, Compare >::Iterator &
anikanov::BinarySearchTree< Key, Value, Compare >::Iterator::operator++()
{
  current = findNext(current);
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename anikanov::BinarySearchTree< Key, Value, Compare >::Iterator
anikanov::BinarySearchTree< Key, Value, Compare >::Iterator::operator++(int)
{
  Iterator temp = *this;
  ++(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
typename anikanov::BinarySearchTree< Key, Value, Compare >::Iterator &
anikanov::BinarySearchTree< Key, Value, Compare >::Iterator::operator--()
{
  current = findPrev(current);
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename anikanov::BinarySearchTree< Key, Value, Compare >::Iterator
anikanov::BinarySearchTree< Key, Value, Compare >::Iterator::operator--(int)
{
  ConstIterator temp = *this;
  --(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
bool
anikanov::BinarySearchTree< Key, Value, Compare >::Iterator::operator!=(const BinarySearchTree::Iterator &other) const
{
  return current != other.current;
}

template< typename Key, typename Value, typename Compare >
bool
anikanov::BinarySearchTree< Key, Value, Compare >::Iterator::operator==(const BinarySearchTree::Iterator &other) const
{
  return current == other.current;
}

template< typename Key, typename Value, typename Compare >
typename anikanov::BinarySearchTree< Key, Value, Compare >::Node *
anikanov::BinarySearchTree< Key, Value, Compare >::Iterator::findNext(Node *node) const
{
  if (node == nullptr) {
    return nullptr;
  }

  if (node->right) {
    node = node->right.get();
    while (node->left) {
      node = node->left.get();
    }
    return node;
  }

  while (node->parent.lock() && node->parent.lock()->right.get() == node) {
    node = node->parent.lock().get();
  }

  return node->parent.lock().get();
}

template< typename Key, typename Value, typename Compare >
typename anikanov::BinarySearchTree< Key, Value, Compare >::Node *
anikanov::BinarySearchTree< Key, Value, Compare >::Iterator::findPrev(Node *node) const
{
  if (node == nullptr) {
    return nullptr;
  }
  if (node->left) {
    node = node->left;
    while (node->right) {
      node = node->right;
    }
    return node;
  }
  while (node->parent && node->parent->left == node) {
    node = node->parent;
  }
  return node->parent;
}

template< typename Key, typename Value, typename Compare >
anikanov::BinarySearchTree< Key, Value, Compare >::ConstIterator::ConstIterator(
    BinarySearchTree::Iterator it) : iter(it)
{}

template< typename Key, typename Value, typename Compare >
const std::pair< Key, Value > &anikanov::BinarySearchTree< Key, Value, Compare >::ConstIterator::operator*() const
{
  return *iter;
}

template< typename Key, typename Value, typename Compare >
const std::pair< Key, Value > *anikanov::BinarySearchTree< Key, Value, Compare >::ConstIterator::operator->() const
{
  return &(*iter);
}

template< typename Key, typename Value, typename Compare >
typename anikanov::BinarySearchTree< Key, Value, Compare >::ConstIterator &
anikanov::BinarySearchTree< Key, Value, Compare >::ConstIterator::operator++()
{
  ++iter;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename anikanov::BinarySearchTree< Key, Value, Compare >::ConstIterator
anikanov::BinarySearchTree< Key, Value, Compare >::ConstIterator::operator++(int)
{
  ConstIterator tmp = *this;
  ++iter;
  return tmp;
}

template< typename Key, typename Value, typename Compare >
typename anikanov::BinarySearchTree< Key, Value, Compare >::ConstIterator &
anikanov::BinarySearchTree< Key, Value, Compare >::ConstIterator::operator--()
{
  --iter;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename anikanov::BinarySearchTree< Key, Value, Compare >::ConstIterator
anikanov::BinarySearchTree< Key, Value, Compare >::ConstIterator::operator--(int)
{
  ConstIterator tmp = *this;
  --iter;
  return tmp;
}

template< typename Key, typename Value, typename Compare >
bool anikanov::BinarySearchTree< Key, Value, Compare >::ConstIterator::operator==(
    const BinarySearchTree::ConstIterator &other) const
{
  return iter == other.iter;
}

template< typename Key, typename Value, typename Compare >
bool anikanov::BinarySearchTree< Key, Value, Compare >::ConstIterator::operator!=(
    const BinarySearchTree::ConstIterator &other) const
{
  return iter != other.iter;
}

template< typename Key, typename Value, typename Compare >
void anikanov::BinarySearchTree< Key, Value, Compare >::clear()
{
  root.reset();
  nodeCount = 0;
}

template< typename Key, typename Value, typename Compare >
typename anikanov::BinarySearchTree< Key, Value, Compare >::ConstIterator
anikanov::BinarySearchTree< Key, Value, Compare >::begin() const
{
  List< std::pair< Key, Value > > list;
  inOrder(root.get(), list);
  return ConstIterator(Iterator(list.begin()));
}

template< typename Key, typename Value, typename Compare >
typename anikanov::BinarySearchTree< Key, Value, Compare >::ConstIterator
anikanov::BinarySearchTree< Key, Value, Compare >::end() const
{
  return ConstIterator(Iterator());
}

template< typename Key, typename Value, typename Compare >
typename anikanov::BinarySearchTree< Key, Value, Compare >::Iterator
anikanov::BinarySearchTree< Key, Value, Compare >::begin()
{
  if (!root) {
    return Iterator();
  }
  return Iterator(minValueNode(root.get()));
}

template< typename Key, typename Value, typename Compare >
typename anikanov::BinarySearchTree< Key, Value, Compare >::Iterator
anikanov::BinarySearchTree< Key, Value, Compare >::end()
{
  return Iterator();
}

template< typename Key, typename Value, typename Compare >
typename anikanov::BinarySearchTree< Key, Value, Compare >::ConstIterator
anikanov::BinarySearchTree< Key, Value, Compare >::find(const Key &key) const
{
  Node *current = root.get();
  while (current) {
    if (comp(key, current->data.first)) {
      current = current->left.get();
    } else if (comp(current->data.first, key)) {
      current = current->right.get();
    } else {
      return ConstIterator(Iterator(current));
    }
  }
  return end();
}

template< typename Key, typename Value, typename Compare >
std::pair<
    typename anikanov::BinarySearchTree< Key, Value, Compare >::ConstIterator,
    typename anikanov::BinarySearchTree< Key, Value, Compare >::ConstIterator
> anikanov::BinarySearchTree< Key, Value, Compare >::equalRange(const Key &key) const
{
  anikanov::List< std::pair< Key, Value > > list;
  inOrder(root.get(), list);
  auto lower = list.begin();
  while (lower != list.end() && comp(lower->first, key)) {
    ++lower;
  }
  auto upper = lower;
  while (upper != list.end() && !comp(key, upper->first)) {
    ++upper;
  }
  return std::make_pair(ConstIterator(lower), ConstIterator(upper));
}

template< typename Key, typename Value, typename Compare >
size_t anikanov::BinarySearchTree< Key, Value, Compare >::count(const Key &key) const
{
  return find(key) != end() ? 1 : 0;
}

template< typename Key, typename Value, typename Compare >
void anikanov::BinarySearchTree< Key, Value, Compare >::insert(const std::pair< Key, Value > &pair)
{
  push(pair.first, pair.second);
}

template< typename Key, typename Value, typename Compare >
void anikanov::BinarySearchTree< Key, Value, Compare >::erase(const Key &key)
{
  drop(key);
}

template< typename Key, typename Value, typename Compare >
void anikanov::BinarySearchTree< Key, Value, Compare >::print() const
{
  anikanov::List< std::pair< Key, Value>> list;
  inOrder(root.get(), list);
  for (const auto &p: list) {
    std::cout << p.first << " " << p.second << " ";
  }
  std::cout << std::endl;
}

template< typename Key, typename Value, typename Compare >
int anikanov::BinarySearchTree< Key, Value, Compare >::height(BinarySearchTree::Node *n) const
{
  return n ? n->height : 0;
}

template< typename Key, typename Value, typename Compare >
int anikanov::BinarySearchTree< Key, Value, Compare >::balanceFactor(BinarySearchTree::Node *n) const
{
  return n ? height(n->left.get()) - height(n->right.get()) : 0;
}

template< typename Key, typename Value, typename Compare >
void anikanov::BinarySearchTree< Key, Value, Compare >::updateHeight(BinarySearchTree::Node *n)
{
  if (n) {
    n->height = 1 + std::max(height(n->left.get()), height(n->right.get()));
  }
}

template< typename Key, typename Value, typename Compare >
std::shared_ptr< typename anikanov::BinarySearchTree< Key, Value, Compare >::Node >
anikanov::BinarySearchTree< Key, Value, Compare >::rotateRight(std::shared_ptr< Node > y)
{
  std::shared_ptr< Node > x = std::move(y->left);
  y->left = std::move(x->right);
  if (y->left) {
    y->left->parent = y;
  }
  x->right = std::move(y);
  x->right->parent = x;
  updateHeight(x->right.get());
  updateHeight(x.get());
  x->parent = x->right->parent.lock();
  return x;
}

template< typename Key, typename Value, typename Compare >
std::shared_ptr< typename anikanov::BinarySearchTree< Key, Value, Compare >::Node >
anikanov::BinarySearchTree< Key, Value, Compare >::rotateLeft(std::shared_ptr< Node > x)
{
  std::shared_ptr< Node > y = std::move(x->right);
  x->right = std::move(y->left);
  if (x->right) {
    x->right->parent = x;
  }
  y->left = std::move(x);
  y->left->parent = y;
  updateHeight(y->left.get());
  updateHeight(y.get());
  y->parent = y->left->parent.lock();
  return y;
}

template< typename Key, typename Value, typename Compare >
std::shared_ptr< typename anikanov::BinarySearchTree< Key, Value, Compare >::Node >
anikanov::BinarySearchTree< Key, Value, Compare >::balance(std::shared_ptr< Node > n)
{
  updateHeight(n.get());
  if (balanceFactor(n.get()) > 1) {
    if (balanceFactor(n->left.get()) < 0) {
      n->left = rotateLeft(std::move(n->left));
    }
    auto newRoot = rotateRight(std::move(n));
    newRoot->parent.reset();
    return newRoot;
  }
  if (balanceFactor(n.get()) < -1) {
    if (balanceFactor(n->right.get()) > 0) {
      n->right = rotateRight(std::move(n->right));
    }
    auto newRoot = rotateLeft(std::move(n));
    newRoot->parent.reset();
    return newRoot;
  }
  return n;
}

template< typename Key, typename Value, typename Compare >
std::shared_ptr< typename anikanov::BinarySearchTree< Key, Value, Compare >::Node >
anikanov::BinarySearchTree< Key, Value, Compare >::insert(std::shared_ptr< Node > node, const Key &key,
                                                          const Value &value, std::shared_ptr< Node > parent)
{
  if (!node) {
    ++nodeCount;
    return std::make_shared< Node >(key, value, parent);
  }
  if (comp(key, node->data.first)) {
    node->left = insert(node->left, key, value, node);
  } else if (comp(node->data.first, key)) {
    node->right = insert(node->right, key, value, node);
  } else {
    node->data.second = value;
  }
  return balance(node);
}

template< typename Key, typename Value, typename Compare >
std::shared_ptr< typename anikanov::BinarySearchTree< Key, Value, Compare >::Node >
anikanov::BinarySearchTree< Key, Value, Compare >::erase(std::shared_ptr< Node > node, const Key &key)
{
  if (!node) return nullptr;
  if (comp(key, node->data.first)) {
    node->left = erase(std::move(node->left), key);
  } else if (comp(node->data.first, key)) {
    node->right = erase(std::move(node->right), key);
  } else {
    if (!node->left) return std::move(node->right);
    if (!node->right) return std::move(node->left);
    Node *min = minValueNode(node->right.get());
    node->data.second = std::move(min->data.second);
    node->data.first = min->data.first;
    node->right = erase(std::move(node->right), min->data.first);
  }
  return balance(std::move(node));
}

template< typename Key, typename Value, typename Compare >
typename anikanov::BinarySearchTree< Key, Value, Compare >::Node *
anikanov::BinarySearchTree< Key, Value, Compare >::minValueNode(BinarySearchTree::Node *node) const
{
  while (node->left) {
    node = node->left.get();
  }
  return node;
}

template< typename Key, typename Value, typename Compare >
typename anikanov::BinarySearchTree< Key, Value, Compare >::Node *
anikanov::BinarySearchTree< Key, Value, Compare >::find(BinarySearchTree::Node *node, const Key &key) const
{
  if (!node) return nullptr;
  if (comp(key, node->data.first)) return find(node->left.get(), key);
  if (comp(node->data.first, key)) return find(node->right.get(), key);
  return node;
}

template< typename Key, typename Value, typename Compare >
void anikanov::BinarySearchTree< Key, Value, Compare >::inOrder(BinarySearchTree::Node *node,
                                                                anikanov::List< std::pair< Key, Value>> &list) const
{
  if (node) {
    inOrder(node->left.get(), list);
    list.push_back(node->data);
    inOrder(node->right.get(), list);
  }
}

template< typename Key, typename Value, typename Compare >
std::shared_ptr< typename anikanov::BinarySearchTree< Key, Value, Compare >::Node >
anikanov::BinarySearchTree< Key, Value, Compare >::clone(const BinarySearchTree::Node *node) const
{
  if (!node) return nullptr;
  auto newNode = std::make_unique< Node >(node->data.first, node->data.second);
  newNode->left = clone(node->left.get());
  newNode->right = clone(node->right.get());
  return newNode;
}

#endif
