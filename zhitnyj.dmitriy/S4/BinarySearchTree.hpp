#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

template< typename Key, typename Value, typename Compare = std::less< Key > >
class bsTree {
public:
  class Iterator;
  class ConstIterator;

  bsTree();
  bsTree(const bsTree &other);
  bsTree(bsTree &&other) noexcept;
  ~bsTree();

  bsTree &operator=(const bsTree &other);
  bsTree &operator=(bsTree &&other) noexcept;

  void push(Key k, Value v);
  Value get(Key k) const;
  Value drop(Key k);

  bool empty() const;
  size_t size() const;
  void clear();
  void swap(bsTree &other);

  ConstIterator begin() const;
  ConstIterator end() const;

  Iterator begin();
  Iterator end();

  ConstIterator find(const Key &k) const;
  Iterator find(const Key &k);

  std::pair< Iterator, bool > insert(const std::pair< Key, Value > &kv);
  void insert(const Key &k, const Value &v);
  void erase(Iterator pos);
  size_t erase(const Key &k);

  std::pair< ConstIterator, ConstIterator > equal_range(const Key &k) const;
  size_t count(const Key &k) const;

private:
  struct Node {
    std::pair< Key, Value > data;
    Node *left;
    Node *right;
    Node *parent;

    Node(Key k, Value v, Node *p = nullptr) :
      data(std::make_pair(k, v)),
      left(nullptr),
      right(nullptr),
      parent(p)
      {}
  };

  Node *root;
  Compare comp;
  size_t node_count;

  void push(Node *&node, Key k, Value v, Node *parent);
  Value get(Node *node, Key k) const;
  Node *drop(Node *&node, Key k);
  void deleteTree(Node *node);
  Node *findMin(Node *node) const;
  Node *removeMin(Node *node);
  Node *copyTree(Node *node, Node *parent) const;

  template< typename Func >
  void inorder(Node *node, Func func) const;
};

template< typename Key, typename Value, typename Compare >
class bsTree< Key, Value, Compare >::ConstIterator {
public:
  friend class bsTree< Key, Value, Compare >;

  ConstIterator();
  explicit ConstIterator(Node *node);
  const std::pair< Key, Value > &operator*() const;
  const std::pair< Key, Value > *operator->() const;
  ConstIterator &operator++();
  bool operator==(const ConstIterator &other) const;
  bool operator!=(const ConstIterator &other) const;

private:
  Node *current;
  std::pair< Key, Value > pair;

  Node *findNext(Node *node) const;
};

template< typename Key, typename Value, typename Compare >
bsTree< Key, Value, Compare >::ConstIterator::ConstIterator() : current(nullptr)
{}

template< typename Key, typename Value, typename Compare >
bsTree< Key, Value, Compare >::ConstIterator::ConstIterator(Node *node) : current(node) {
  if (current) {
    pair = current->data;
  }
}

template< typename Key, typename Value, typename Compare >
const std::pair< Key, Value > &bsTree< Key, Value, Compare >::ConstIterator::operator*() const {
  return pair;
}

template< typename Key, typename Value, typename Compare >
const std::pair< Key, Value > *bsTree< Key, Value, Compare >::ConstIterator::operator->() const {
  return &pair;
}

template< typename Key, typename Value, typename Compare >
typename bsTree< Key, Value, Compare >::ConstIterator &
bsTree< Key, Value, Compare >::ConstIterator::operator++() {
  current = findNext(current);
  if (current) {
    pair = current->data;
  }
  return *this;
}

template< typename Key, typename Value, typename Compare >
bool bsTree< Key, Value, Compare >::ConstIterator::operator==(const ConstIterator &other) const {
  return current == other.current;
}

template< typename Key, typename Value, typename Compare >
bool bsTree< Key, Value, Compare >::ConstIterator::operator!=(const ConstIterator &other) const {
  return current != other.current;
}

template< typename Key, typename Value, typename Compare >
typename bsTree< Key, Value, Compare >::Node *
bsTree< Key, Value, Compare >::ConstIterator::findNext(Node *node) const {
  if (node == nullptr) {
    return nullptr;
  }
  if (node->right) {
    node = node->right;
    while (node->left) {
      node = node->left;
    }
    return node;
  }
  while (node->parent && node->parent->right == node) {
    node = node->parent;
  }
  return node->parent;
}

template< typename Key, typename Value, typename Compare >
class bsTree< Key, Value, Compare >::Iterator {
public:
  friend class bsTree< Key, Value, Compare >;

  Iterator();
  explicit Iterator(ConstIterator constIter);

  std::pair< Key, Value > &operator*() const;
  std::pair< Key, Value > *operator->() const;
  Iterator &operator++();
  Iterator operator++(int);
  Iterator &operator--();
  Iterator operator--(int);

  bool operator==(const Iterator &other) const;
  bool operator!=(const Iterator &other) const;

private:
  ConstIterator constIter_;
};

template< typename Key, typename Value, typename Compare >
bsTree< Key, Value, Compare >::Iterator::Iterator() : constIter_() {
}

template< typename Key, typename Value, typename Compare >
bsTree< Key, Value, Compare >::Iterator::Iterator(ConstIterator constIter) : constIter_(constIter) {
}

template< typename Key, typename Value, typename Compare >
std::pair< Key, Value > &bsTree< Key, Value, Compare >::Iterator::operator*() const {
  return const_cast<std::pair< Key, Value > &>(*constIter_);
}

template< typename Key, typename Value, typename Compare >
std::pair< Key, Value > *bsTree< Key, Value, Compare >::Iterator::operator->() const {
  return const_cast<std::pair< Key, Value > *>(constIter_.operator->());
}

template< typename Key, typename Value, typename Compare >
typename bsTree< Key, Value, Compare >::Iterator &
bsTree< Key, Value, Compare >::Iterator::operator++() {
  ++constIter_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename bsTree< Key, Value, Compare >::Iterator
bsTree< Key, Value, Compare >::Iterator::operator++(int) {
  Iterator temp = *this;
  ++(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
typename bsTree< Key, Value, Compare >::Iterator &
bsTree< Key, Value, Compare >::Iterator::operator--() {
  --constIter_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename bsTree< Key, Value, Compare >::Iterator
bsTree< Key, Value, Compare >::Iterator::operator--(int) {
  Iterator temp = *this;
  --(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
bool bsTree< Key, Value, Compare >::Iterator::operator==(const Iterator &other) const {
  return constIter_ == other.constIter_;
}

template< typename Key, typename Value, typename Compare >
bool bsTree< Key, Value, Compare >::Iterator::operator!=(const Iterator &other) const {
  return !(*this == other);
}

template< typename Key, typename Value, typename Compare >
bsTree< Key, Value, Compare >::bsTree() : root(nullptr), node_count(0) {
}

template< typename Key, typename Value, typename Compare >
bsTree< Key, Value, Compare >::bsTree(const bsTree &other):
  root(copyTree(other.root, nullptr)),
  node_count(other.node_count)
{}

template< typename Key, typename Value, typename Compare >
bsTree< Key, Value, Compare >::bsTree(bsTree &&other) noexcept:
  root(other.root),
  node_count(other.node_count) {
  other.root = nullptr;
  other.node_count = 0;
}

template< typename Key, typename Value, typename Compare >
bsTree< Key, Value, Compare >::~bsTree() {
  deleteTree(root);
}

template< typename Key, typename Value, typename Compare >
bsTree< Key, Value, Compare > &bsTree< Key, Value, Compare >::operator=(const bsTree &other) {
  if (this != &other) {
    deleteTree(root);
    root = copyTree(other.root, nullptr);
    node_count = other.node_count;
  }
  return *this;
}

template< typename Key, typename Value, typename Compare >
bsTree< Key, Value, Compare > &bsTree< Key, Value, Compare >::operator=(bsTree &&other) noexcept {
  if (this != &other) {
    deleteTree(root);
    root = other.root;
    node_count = other.node_count;
    other.root = nullptr;
    other.node_count = 0;
  }
  return *this;
}

template< typename Key, typename Value, typename Compare >
void bsTree< Key, Value, Compare >::push(Node *&node, Key k, Value v, Node *parent) {
  if (node == nullptr) {
    node = new Node(k, v, parent);
    ++node_count;
  }
  else if (comp(k, node->data.first)) {
    push(node->left, k, v, node);
  }
  else if (comp(node->data.first, k)) {
    push(node->right, k, v, node);
  }
  else {
    node->data.second = v;
  }
}

template< typename Key, typename Value, typename Compare >
void bsTree< Key, Value, Compare >::push(Key k, Value v) {
  push(root, k, v, nullptr);
}

template< typename Key, typename Value, typename Compare >
Value bsTree< Key, Value, Compare >::get(Node *node, Key k) const {
  if (node == nullptr) {
    return Value();
  }
  else if (comp(k, node->data.first)) {
    return get(node->left, k);
  }
  else if (comp(node->data.first, k)) {
    return get(node->right, k);
  }
  else {
    return node->data.second;
  }
}

template< typename Key, typename Value, typename Compare >
Value bsTree< Key, Value, Compare >::get(Key k) const {
  return get(root, k);
}

template< typename Key, typename Value, typename Compare >
typename bsTree< Key, Value, Compare >::Node *
bsTree< Key, Value, Compare >::findMin(Node *node) const {
  return node->left ? findMin(node->left) : node;
}

template< typename Key, typename Value, typename Compare >
typename bsTree< Key, Value, Compare >::Node *
bsTree< Key, Value, Compare >::removeMin(Node *node) {
  if (node->left == nullptr) {
    return node->right;
  }
  node->left = removeMin(node->left);
  return node;
}

template< typename Key, typename Value, typename Compare >
typename bsTree< Key, Value, Compare >::Node *
bsTree< Key, Value, Compare >::drop(Node *&node, Key k) {
  if (node == nullptr) {
    return nullptr;
  }
  if (comp(k, node->data.first)) {
    node->left = drop(node->left, k);
  }
  else if (comp(node->data.first, k)) {
    node->right = drop(node->right, k);
  }
  else {
    Node *left = node->left;
    Node *right = node->right;
    delete node;
    --node_count;
    if (!right) {
      return left;
    }
    Node *min = findMin(right);
    min->right = removeMin(right);
    min->left = left;
    return min;
  }
  return node;
}

template< typename Key, typename Value, typename Compare >
Value bsTree< Key, Value, Compare >::drop(Key k) {
  Value v = get(k);
  root = drop(root, k);
  return v;
}

template< typename Key, typename Value, typename Compare >
void bsTree< Key, Value, Compare >::deleteTree(Node *node) {
  if (node == nullptr) {
    return;
  }
  deleteTree(node->left);
  deleteTree(node->right);
  delete node;
}

template< typename Key, typename Value, typename Compare >
typename bsTree< Key, Value, Compare >::Node *
bsTree< Key, Value, Compare >::copyTree(Node *node, Node *parent) const {
  if (node == nullptr) {
    return nullptr;
  }
  Node *newNode = new Node(node->data.first, node->data.second, parent);
  newNode->left = copyTree(node->left, newNode);
  newNode->right = copyTree(node->right, newNode);
  return newNode;
}

template< typename Key, typename Value, typename Compare >
bool bsTree< Key, Value, Compare >::empty() const {
  return node_count == 0;
}

template< typename Key, typename Value, typename Compare >
size_t bsTree< Key, Value, Compare >::size() const {
  return node_count;
}

template< typename Key, typename Value, typename Compare >
void bsTree< Key, Value, Compare >::clear() {
  deleteTree(root);
  root = nullptr;
  node_count = 0;
}

template< typename Key, typename Value, typename Compare >
void bsTree< Key, Value, Compare >::swap(bsTree &other) {
  Node *tempRoot = root;
  root = other.root;
  other.root = tempRoot;

  size_t tempCount = node_count;
  node_count = other.node_count;
  other.node_count = tempCount;
}

template< typename Key, typename Value, typename Compare >
typename bsTree< Key, Value, Compare >::ConstIterator
bsTree< Key, Value, Compare >::begin() const {
  if (root == nullptr) {
    return end();
  }
  Node *root_ = root;
  while (root_->left) {
    root_ = root_->left;
  }
  return ConstIterator(root_);
}

template< typename Key, typename Value, typename Compare >
typename bsTree< Key, Value, Compare >::ConstIterator
bsTree< Key, Value, Compare >::end() const {
  return ConstIterator();
}

template< typename Key, typename Value, typename Compare >
typename bsTree< Key, Value, Compare >::Iterator
bsTree< Key, Value, Compare >::begin() {
  if (root == nullptr) {
    return end();
  }
  Node *root_ = root;
  while (root_->left) {
    root_ = root_->left;
  }
  return Iterator(ConstIterator(root_));
}

template< typename Key, typename Value, typename Compare >
typename bsTree< Key, Value, Compare >::Iterator
bsTree< Key, Value, Compare >::end() {
  return Iterator(ConstIterator());
}

template< typename Key, typename Value, typename Compare >
typename bsTree< Key, Value, Compare >::ConstIterator
bsTree< Key, Value, Compare >::find(const Key &k) const {
  Node *current = root;
  while (current) {
    if (comp(k, current->data.first)) {
      current = current->left;
    }
    else if (comp(current->data.first, k)) {
      current = current->right;
    }
    else {
      return ConstIterator(current);
    }
  }
  return end();
}

template< typename Key, typename Value, typename Compare >
typename bsTree< Key, Value, Compare >::Iterator
bsTree< Key, Value, Compare >::find(const Key &k) {
  Node *current = root;
  while (current) {
    if (comp(k, current->data.first)) {
      current = current->left;
    }
    else if (comp(current->data.first, k)) {
      current = current->right;
    }
    else {
      return Iterator(ConstIterator(current));
    }
  }
  return end();
}

template< typename Key, typename Value, typename Compare >
std::pair< typename bsTree< Key, Value, Compare >::Iterator, bool >
bsTree< Key, Value, Compare >::insert(const std::pair< Key, Value > &kv) {
  Node *parent = nullptr;
  Node *current = root;
  bool isLeftChild = false;

  while (current) {
    parent = current;
    if (comp(kv.first, current->data.first)) {
      current = current->left;
      isLeftChild = true;
    }
    else if (comp(current->data.first, kv.first)) {
      current = current->right;
      isLeftChild = false;
    }
    else {
      return {Iterator(ConstIterator(current)), false};
    }
  }

  Node *newNode = new Node(kv.first, kv.second, parent);
  if (parent == nullptr) {
    root = newNode;
  }
  else if (isLeftChild) {
    parent->left = newNode;
  }
  else {
    parent->right = newNode;
  }

  ++node_count;
  return {Iterator(ConstIterator(newNode)), true};
}

template< typename Key, typename Value, typename Compare >
void bsTree< Key, Value, Compare >::insert(const Key &k, const Value &v) {
  insert(std::make_pair(k, v));
}

template< typename Key, typename Value, typename Compare >
void bsTree< Key, Value, Compare >::erase(Iterator pos) {
  if (pos.constIter.current == nullptr) {
    return;
  }
  root = drop(root, pos.constIter.current->data.first);
}

template< typename Key, typename Value, typename Compare >
size_t bsTree< Key, Value, Compare >::erase(const Key &k) {
  if (find(k) == end()) {
    return 0;
  }
  drop(root, k);
  return 1;
}

template< typename Key, typename Value, typename Compare >
std::pair< typename bsTree< Key, Value, Compare >::ConstIterator, typename bsTree< Key, Value, Compare >::ConstIterator >
bsTree< Key, Value, Compare >::equal_range(const Key &k) const {
  return {find(k), find(k)};
}

template< typename Key, typename Value, typename Compare >
size_t bsTree< Key, Value, Compare >::count(const Key &k) const {
  return find(k) != end() ? 1 : 0;
}

template< typename Key, typename Value, typename Compare >
template< typename Func >
void bsTree< Key, Value, Compare >::inorder(Node *node, Func func) const {
  if (node == nullptr) {
    return;
  }
  inorder(node->left, func);
  func(node->data.first, node->data.second);
  inorder(node->right, func);
}

#endif
