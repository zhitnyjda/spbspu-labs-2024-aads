#ifndef AVLTREE_HPP
#define AVLTREE_HPP
#include <utility>
#include <iterator>
#include <initializer_list>
#include <functional>
#include <iostream>

namespace mihalchenko
{
  template <typename Key, typename Value, typename Compare = std::less<Key>>
  class AVLTree
  {
  public:
    class ConstIterator;
    class Iterator;

    AVLTree();

    template <class InputIt>
    AVLTree(InputIt start, InputIt stop);

    AVLTree(size_t count, std::pair<const Key, Value> &pairKeyVal);
    AVLTree(std::initializer_list<std::pair<const Key, Value>> initAVL);
    AVLTree(const AVLTree &copy);
    AVLTree(AVLTree &&move);
    ~AVLTree();

    void insert(Key key, Value value);
    using value_std_pair = std::pair<const Key, Value>;
    void insert(std::pair<const Key, Value> pairKeyVal);
    bool empty() const noexcept;
    size_t getSize() const noexcept;
    size_t erase(const Key &key);
    void clear();

    Value &operator[](const Key &key);
    Iterator find(const Key &key);
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;
    Iterator begin() noexcept;
    Iterator end() noexcept;

  private:
    class Node
    {
    public:
      friend class AVLTree;
      Node(Key key, Value data, int height = 0, Node *left = nullptr, Node *right = nullptr, Node *previous = nullptr);

    private:
      std::pair<const Key, Value> pairOfKeyVal_;
      int height_;
      Node *left_;
      Node *right_;
      Node *previous_;
    };

    Node *insertNode(Key key, Value val, Node *node);
    Iterator findNode(const Key &key, Node *node);

    void leftSpin(Node *node);
    void leftRightSpin(Node *node);
    void rightSpin(Node *node);
    void rightLeftSpin(Node *node);

    int calcHeight(Node *node);
    Node *SearchHiHeight(Node *node);

    //----------------------------------
    size_t updateHeight(Node *node);
    int checkBalance(Node *node);
    Node *isBalanced(Node *node);
    void doBalance(Node *overweight);
    int getHeight(Node *node);
    //----------------------------------

    Node *copyTree(Node *node, Node *previous);
    void doStableTree(Node *checkNode);
    void clear(Node *node);
    // void recombinateLinksRight(Node * deletedNode, Node * prevDelNode);
    // void recombinateLinksLeft(Node * deletedNode, Node * prevDelNode);

    Node *root_;
    size_t size_ = 0;
  };
}

template <typename Key, typename Value, typename Compare>
class mihalchenko::AVLTree<Key, Value, Compare>::ConstIterator : public std::iterator<std::bidirectional_iterator_tag, std::pair<const Key, Value>>
{
public:
  friend class AVLTree<Key, Value, Compare>;
  ConstIterator();
  ConstIterator(Node *node, Node *root);
  ConstIterator(const ConstIterator &) = default;
  ~ConstIterator() = default;

  ConstIterator &operator++();
  ConstIterator operator++(int);
  ConstIterator &operator--();
  ConstIterator operator--(int);

  const std::pair<const Key, Value> &operator*() const;
  const std::pair<const Key, Value> *operator->() const;

  bool operator!=(const ConstIterator &rhs) const;
  bool operator==(const ConstIterator &rhs) const;

  ConstIterator &operator=(const ConstIterator &) = default;

private:
  Node *node_;
  Node *root_;
};

template <typename Key, typename Value, typename Compare>
class mihalchenko::AVLTree<Key, Value, Compare>::Iterator : public std::iterator<std::bidirectional_iterator_tag, Key, Value, Compare>
{
public:
  friend class AVLTree<Key, Value, Compare>;
  Iterator();
  Iterator(ConstIterator iter);
  Iterator(const Iterator &) = default;
  ~Iterator() = default;

  Iterator &operator++();
  Iterator operator++(int);
  Iterator &operator--();
  Iterator operator--(int);
  Iterator &operator=(const Iterator &) = default;

  std::pair<const Key, Value> &operator*();
  std::pair<const Key, Value> *operator->();
  const std::pair<const Key, Value> &operator*() const;
  const std::pair<const Key, Value> *operator->() const;

  bool operator!=(const Iterator &rhs) const;
  bool operator==(const Iterator &rhs) const;

private:
  ConstIterator constIter_;
};

template <typename Key, typename Value, typename Compare>
mihalchenko::AVLTree<Key, Value, Compare>::Node::Node(Key key, Value data, int height, Node *left, Node *right, Node *previous) : pairOfKeyVal(std::make_pair(key, data)), height_(height), left_(left), right_(right), previous_(previous)
{
}

template <typename Key, typename Value, typename Compare>
typename mihalchenko::AVLTree<Key, Value, Compare>::Node *mihalchenko::AVLTree<Key, Value, Compare>::insertNode(Key key, Value val, Node *node)
{
  // std::cout << "мы в инит size_=" << size_ << "key=" << key << std::endl;
  Node *newNode = new Node(key, val, 0, nullptr, nullptr, nullptr);
  if (!node)
  {
    root_ = newNode;
    size_++;
    return root_;
  }
  Compare compare;
  if ((node) && !compare(key, node->pairOfKeyVal_.first) && !compare(node->pairOfKeyVal_.first, key))
  {
    return node;
  }
  Node *preview = nullptr;
  bool existNode = true;
  while (existNode)
  {
    if (compare(key, node->pairOfKeyVal_.first))
    {
      if (!node->left_)
      {
        node->left_ = newNode;
        newNode->previous_ = node;
        size_++;
        existNode = false;
      }
      node = node->left_;
    }
    else
    {
      if (!node->right_)
      {
        node->right_ = newNode;
        newNode->previous_ = node;
        size_++;
        existNode = false;
      }
      node = node->right_;
    }
  }
  // balance(newNode);
  return newNode;
}

template <typename Key, typename Value, typename Compare>
mihalchenko::AVLTree<Key, Value, Compare>::AVLTree()
{
  root_ = nullptr;
  size_ = 0;
}

template <typename Key, typename Value, typename Compare>
mihalchenko::AVLTree<Key, Value, Compare>::AVLTree(size_t count, std::pair<const Key, Value> &pairKeyVal)
{
  root_ = nullptr;
  size_ = 0;
  for (size_t i = 0; i < count; ++i)
  {
    insert(pairKeyVal);
    size_++;
  }
}

template <typename Key, typename Value, typename Compare>
template <class InputIt>
mihalchenko::AVLTree<Key, Value, Compare>::AVLTree(InputIt start, InputIt stop)
{
  root_ = nullptr;
  size_ = 0;
  for (InputIt it = start; it != stop; ++it)
  {
    insert(*it);
    size_++;
  }
}

template <typename Key, typename Value, typename Compare>
mihalchenko::AVLTree<Key, Value, Compare>::AVLTree(std::initializer_list<std::pair<const Key, Value>> initAVL)
{
  root_ = nullptr;
  size_ = 0;
  for (auto it = initAVL.begin(); it != initAVL.end(); ++it)
  {
    insert(*it);
    size_++;
  }
}

template <typename Key, typename Value, typename Compare>
mihalchenko::AVLTree<Key, Value, Compare>::AVLTree(const AVLTree &copy)
{
  // root_ = nullptr;
  // size_ = 0;
  root_ = copyTree(copy.root_, nullptr);
}

template <typename Key, typename Value, typename Compare>
mihalchenko::AVLTree<Key, Value, Compare>::AVLTree(AVLTree &&move)
//  root_(nullptr), size_(std::move(move.size_))
{
  // root_ = nullptr;
  // size_ = 0;
  root_ = copyTree(std::move(move.root_), nullptr);
  move.clear();
  move.root_ = nullptr;
  move.size_ = 0;
}

template <typename Key, typename Value, typename Compare>
void mihalchenko::AVLTree<Key, Value, Compare>::insert(mihalchenko::AVLTree<Key, Value, Compare>::value_std_pair pair)
{
  insert(pair.first, pair.second);
}

template <typename Key, typename Value, typename Compare>
void mihalchenko::AVLTree<Key, Value, Compare>::insert(Key key, Value value)
{
  // Node * node = insertNode(key, value, root_, nullptr);
  /*  root_ = insertNode(key, value, root_, nullptr);
    updateHeight(root_);
    Node * overweight = isBalanced(find(key).constIter_.node_);
    doBalance(overweight);
    return;
    */
  Node *node = insertNode(key, value, root_);
  if (node != nullptr)
  {
    size_t value1 = (node->left_) ? node->left_->height_ : 0;
    size_t value2 = (node->right_) ? node->right_->height_ : 0;
    node->height_ = std::max(value1, value2) + 1;
  }
  Node *checkNode = SearchHiHeight(find(key).constIter_.node_);
  doStableTree(checkNode);
  return;
}

template <typename Key, typename Value, typename Compare>
typename mihalchenko::AVLTree<Key, Value, Compare>::Iterator mihalchenko::AVLTree<Key, Value, Compare>::find(const Key &key)
{
  return findNode(key, root_);
}

template <typename Key, typename Value, typename Compare>
Value &mihalchenko::AVLTree<Key, Value, Compare>::operator[](const Key &key)
{
  return (*findNode(key, root_)).second;
}

template <typename Key, typename Value, typename Compare>
void mihalchenko::AVLTree<Key, Value, Compare>::clear()
{
  clear(root_);
}

template <typename Key, typename Value, typename Compare>
bool mihalchenko::AVLTree<Key, Value, Compare>::empty() const noexcept
{
  return root_ == nullptr;
}

template <typename Key, typename Value, typename Compare>
size_t mihalchenko::AVLTree<Key, Value, Compare>::getSize() const noexcept
{
  return size_;
}

template <typename Key, typename Value, typename Compare>
typename mihalchenko::AVLTree<Key, Value, Compare>::Iterator mihalchenko::AVLTree<Key, Value, Compare>::begin() noexcept
{
  if (empty())
  {
    return cend();
  }
  Node *temp = root_;
  while (temp->left_ != nullptr)
  {
    temp = temp->left_;
  }
  return Iterator(ConstIterator(temp, root_));
}

template <typename Key, typename Value, typename Compare>
typename mihalchenko::AVLTree<Key, Value, Compare>::Iterator mihalchenko::AVLTree<Key, Value, Compare>::end() noexcept
{
  return ConstIterator(nullptr, root_);
}

template <typename Key, typename Value, typename Compare>
typename mihalchenko::AVLTree<Key, Value, Compare>::ConstIterator mihalchenko::AVLTree<Key, Value, Compare>::cbegin() const noexcept
{
  if (empty())
  {
    return cend();
  }
  Node *temp = root_;
  while (temp->left != nullptr)
  {
    temp = temp->left;
  }
  return ConstIterator(temp, root_);
}

template <typename Key, typename Value, typename Compare>
typename mihalchenko::AVLTree<Key, Value, Compare>::ConstIterator mihalchenko::AVLTree<Key, Value, Compare>::cend() const noexcept
{
  return ConstIterator(nullptr, root_);
}

template <typename Key, typename Value, typename Compare>
mihalchenko::AVLTree<Key, Value, Compare>::ConstIterator::ConstIterator()
{
  node_ = nullptr;
  root_ = nullptr;
}

template <typename Key, typename Value, typename Compare>
mihalchenko::AVLTree<Key, Value, Compare>::ConstIterator::ConstIterator(Node *node, Node *root)
{
  node_ = node;
  root_ = root;
}

template <typename Key, typename Value, typename Compare> //
typename mihalchenko::AVLTree<Key, Value, Compare>::ConstIterator &mihalchenko::AVLTree<Key, Value, Compare>::ConstIterator::operator++()
{
  if (node_->right_)
  {
    node_ = node_->right_;
    while (node_->left_)
    {
      node_ = node_->left_;
    }
  }
  else
  {
    Node *tempNode = node_->previous_;
    while (tempNode && node_ == tempNode->right_)
    {
      node_ = tempNode;
      tempNode = node_->previous_;
    }
    node_ = tempNode;
  }
  return *this;
}

template <typename Key, typename Value, typename Compare>
typename mihalchenko::AVLTree<Key, Value, Compare>::ConstIterator mihalchenko::AVLTree<Key, Value, Compare>::ConstIterator::operator++(int)
{
  ConstIterator result(*this);
  ++(*this);
  return result;
}

template <typename Key, typename Value, typename Compare>
typename mihalchenko::AVLTree<Key, Value, Compare>::ConstIterator &mihalchenko::AVLTree<Key, Value, Compare>::ConstIterator::operator--()
{
  if (node_ == nullptr)
  {
    node_ = root_;
    while (node_->right_)
    {
      node_ = node_->right_;
    }
  }
  else
  {
    if (node_->left_)
    {
      node_ = node_->left_;
      while (node_->right_)
      {
        node_ = node_->right_;
      }
    }
    else
    {
      Node *tempNode = node_->previous_;
      while (tempNode && node_ == tempNode->left_)
      {
        node_ = tempNode;
        tempNode = node_->previous_;
      }
      node_ = tempNode;
    }
  }
  return *this;
}

template <typename Key, typename Value, typename Compare>
typename mihalchenko::AVLTree<Key, Value, Compare>::ConstIterator mihalchenko::AVLTree<Key, Value, Compare>::ConstIterator::operator--(int)
{
  ConstIterator result(*this);
  --(*this);
  return result;
}

template <typename Key, typename Value, typename Compare>
const typename mihalchenko::AVLTree<Key, Value, Compare>::value_std_pair &mihalchenko::AVLTree<Key, Value, Compare>::ConstIterator::operator*() const
{
  // return node_->data_;  - было
  return node_->pairOfKeyVal;
}

template <typename Key, typename Value, typename Compare>
const typename mihalchenko::AVLTree<Key, Value, Compare>::value_std_pair *mihalchenko::AVLTree<Key, Value, Compare>::ConstIterator::operator->() const
{
  // return std::addressof(node_->data_);  - было
  return std::addressof(node_->pairOfKeyVal);
}

template <typename Key, typename Value, typename Compare>
bool mihalchenko::AVLTree<Key, Value, Compare>::ConstIterator::operator==(const ConstIterator &rhs) const
{
  return node_ == rhs.node_;
}

template <typename Key, typename Value, typename Compare>
bool mihalchenko::AVLTree<Key, Value, Compare>::ConstIterator::operator!=(const ConstIterator &rhs) const
{
  return !(*this == rhs);
}

template <typename Key, typename Value, typename Compare>
mihalchenko::AVLTree<Key, Value, Compare>::Iterator::Iterator() : constIter_(ConstIterator())
// constIter_(value) - было
{
}

template <typename Key, typename Value, typename Compare>
mihalchenko::AVLTree<Key, Value, Compare>::Iterator::Iterator(ConstIterator iter) : constIter_(iter)
{
}

template <typename Key, typename Value, typename Compare>
typename mihalchenko::AVLTree<Key, Value, Compare>::Iterator &mihalchenko::AVLTree<Key, Value, Compare>::Iterator::operator++()
//::Iterator::this_t &
{
  ++constIter_;
  return *this;
}

template <typename Key, typename Value, typename Compare>
// typename mihalchenko::AVLTree < Key, Value, Compare >::Iterator::this_t mihalchenko::Tree< Key, Value, Compare >::Iterator::operator++(int)
typename mihalchenko::AVLTree<Key, Value, Compare>::Iterator mihalchenko::AVLTree<Key, Value, Compare>::Iterator::operator++(int)
{
  Iterator result = constIter_;
  // this_t result = iter_;
  ++constIter_;
  return result;
}

template <typename Key, typename Value, typename Compare>
typename mihalchenko::AVLTree<Key, Value, Compare>::Iterator &mihalchenko::AVLTree<Key, Value, Compare>::Iterator::operator--()
{
  --constIter_;
  return *this;
}

template <typename Key, typename Value, typename Compare>
typename mihalchenko::AVLTree<Key, Value, Compare>::Iterator mihalchenko::AVLTree<Key, Value, Compare>::Iterator::operator--(int)
{
  Iterator result = constIter_;
  --constIter_;
  return result;
}

template <typename Key, typename Value, typename Compare>
typename mihalchenko::AVLTree<Key, Value, Compare>::value_std_pair &mihalchenko::AVLTree<Key, Value, Compare>::Iterator::operator*()
{
  return constIter_.node_->pairOfKeyVal;
  // return constIter_.node_->data_;   std::pair< const Key, Value >
}

template <typename Key, typename Value, typename Compare>
typename mihalchenko::AVLTree<Key, Value, Compare>::value_std_pair *mihalchenko::AVLTree<Key, Value, Compare>::Iterator::operator->()
{
  return std::addressof(constIter_.node_->pairOfKeyVal);
  //  return std::addressof(constIter_.node_->data_);
}

template <typename Key, typename Value, typename Compare>
bool mihalchenko::AVLTree<Key, Value, Compare>::Iterator::operator!=(const Iterator &rhs) const
{
  return !(rhs == *this);
  // return !(rhs.constIter_ == constIter_);
}

template <typename Key, typename Value, typename Compare>
bool mihalchenko::AVLTree<Key, Value, Compare>::Iterator::operator==(const Iterator &rhs) const
{
  return constIter_ == rhs.constIter_;
}

#endif
