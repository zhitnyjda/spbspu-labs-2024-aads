#ifndef TREE_HPP
#define TREE_HPP

#include <utility>
#include <cstddef>
#include <iostream>
#include <functional>

namespace miheev
{
  template< typename Key, typename Value, typename Comparator = std::less< Key > >
  class Tree
  {
  public:
    class Iterator;
    class ConstIterator;

    Tree();
    Tree(const Key& key, const Value& value);
    Tree(const Tree&);
    ~Tree();

    Tree& operator=(const Tree&);

    // lookup
    void printKeys(std::ostream& = std::cout) const;
    void printValues(std::ostream& = std::cout) const;

    // element access
    Value& operator[](const Key&);
    const Value& operator[](const Key&) const;
    Value& at(const Key&);
    const Value& at (const Key&) const;

    // capacity
    size_t size() const;
    bool empty() const noexcept;

    //modifiers
    void insert(const Key&, const Value&);
    void insert(const std::pair< Key, Value >& pair);
    void erase(const Key&);
    void clear();
    void swap(Tree&);

    //operations
    Iterator find(const Key&);
    ConstIterator find(const Key&) const;
    bool contains(const Key&) const;

    Iterator begin();
    Iterator end();
    ConstIterator cbegin();
    ConstIterator cend();

  private:
    Key key_;
    Value value_;
    std::pair< Key&, Value& > pair_;

    size_t height_;
    bool isEmpty_;

    Tree* left_;
    Tree* right_;

    Tree* parrent_;

    // search
    Tree* findNextNode(const Key&) const;

    // balancing
    size_t getHeight() const;
    void rebalanceSelf();
    bool isBalanced() const;
    int getDiff() const;
    void swapNodes(Tree*, Tree*);
    void updateHeight();
    void updateParrentsLocally();

    // lookups and node search
    Tree* getMaxNode();
    Tree* getMinNode();

    // insertions
    void safeInsert(const Key&, const Value&, Tree* ptr);
    void rawInsert(const Key&, const Value&);
    void rawDelete(const Key&);
    void rawDeleteSelf();

    // rotations
    void rotateRR();
    void rotateLL();
  };
}

template< typename Key, typename Value, typename Comparator >
class miheev::Tree< Key, Value, Comparator >::Iterator
{
public:

  using kv_pair = std::pair< Key&, Value& >;

  Iterator();
  Iterator(Tree*);
  Iterator(const Iterator&) = default;
  ~Iterator() = default;

  Iterator& operator=(const Iterator&) = default;
  Iterator& operator++();
  Iterator operator++(int);
  Iterator& operator--();
  Iterator operator--(int);

  kv_pair& operator*() const;
  kv_pair* operator->() const;

  bool operator!=(const Iterator&) const;
  bool operator==(const Iterator&) const;

private:
  Tree* cur_;
  bool isDeadEnd_;

  Iterator(Tree*, bool);

  bool weAreOnRight();
};

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >::Iterator::Iterator():
  cur_(nullptr),
  isDeadEnd_(true)
{}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >::Iterator::Iterator(Tree* init):
  cur_(nullptr)
{
  cur_ = init;
  if (init)
  {
    isDeadEnd_ = false;
  }
  else
  {
    isDeadEnd_ = true;
  }
}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >::Iterator::Iterator(Tree* init, bool isDeadEnd):
  cur_(init),
  isDeadEnd_(isDeadEnd)
{
  if (isDeadEnd)
  {
    cur_ = init->getMaxNode();
  }
}

template< typename Key, typename Value, typename Comparator >
bool miheev::Tree< Key, Value, Comparator >::Iterator::weAreOnRight()
{
  Comparator comparator;
  if (!cur_->parrent_)
  {
    return false;
  }
  return comparator(cur_->parrent_->key_, cur_->key_);
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::Iterator& miheev::Tree< Key, Value, Comparator >::Iterator::operator++()
{
  if (isDeadEnd_)
  {
    throw std::out_of_range("iterator is out of range");
  }
  if (cur_->right_)
  {
    cur_ = cur_->right_->getMinNode();
  }
  else
  {
    while (cur_->parrent_ && weAreOnRight())
    {
      cur_ = cur_->parrent_;
    }
    if (!cur_->parrent_)
    {
      isDeadEnd_ = true;
    }
    else
    {
      cur_ = cur_->parrent_;
    }
  }
  return *this;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::Iterator miheev::Tree< Key, Value, Comparator >::Iterator::operator++(int)
{
  Iterator iter(*this);
  ++(*this);
  return iter;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::Iterator& miheev::Tree< Key, Value, Comparator >::Iterator::operator--()
{
  if (isDeadEnd_)
  {
    isDeadEnd_ = false;
  }
  else if (cur_->left_)
  {
    cur_ = cur_->left_->getMaxNode();
  }
  else
  {
    while (cur_->parrent_ && !weAreOnRight())
    {
      cur_ = cur_->parrent_;
    }
    if (cur_->parrent_)
    {
      cur_ = cur_->parrent_;
    }
  }
  return *this;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::Iterator miheev::Tree< Key, Value, Comparator >::Iterator::operator--(int)
{
  Iterator iter(*this);
  --(*this);
  return iter;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::Iterator::kv_pair& miheev::Tree< Key, Value, Comparator >::Iterator::operator*() const
{
  return cur_->pair_;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::Iterator::kv_pair* miheev::Tree< Key, Value, Comparator >::Iterator::operator->() const
{
  return std::addressof(cur_->pair_);
}

template< typename Key, typename Value, typename Comparator >
bool miheev::Tree< Key, Value, Comparator >::Iterator::operator==(const Iterator& rhs) const
{
  return cur_ == rhs.cur_ && isDeadEnd_ == rhs.isDeadEnd_;
}

template< typename Key, typename Value, typename Comparator >
bool miheev::Tree< Key, Value, Comparator >::Iterator::operator!=(const Iterator& rhs) const
{
  return !(*this == rhs);
}

template< typename Key, typename Value, typename Comparator >
class miheev::Tree< Key, Value, Comparator >::ConstIterator
{
public:

  using kv_pair = std::pair< Key&, Value& >;

  ConstIterator();
  ConstIterator(Iterator);
  ConstIterator(const ConstIterator&) = default;
  ~ConstIterator() = default;

  ConstIterator& operator=(const ConstIterator&) = default;
  ConstIterator& operator++();
  ConstIterator operator++(int);
  ConstIterator& operator--();
  ConstIterator operator--(int);

  const kv_pair& operator*() const;
  const kv_pair* operator->() const;

  bool operator!=(const ConstIterator&) const;
  bool operator==(const ConstIterator&) const;

private:
  Iterator iter_;
};

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >::ConstIterator::ConstIterator(Iterator iter):
  iter_(iter)
{}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::ConstIterator& miheev::Tree< Key, Value, Comparator >::ConstIterator::operator++()
{
  return ++iter_;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::ConstIterator miheev::Tree< Key, Value, Comparator >::ConstIterator::operator++(int)
{
  return iter_++;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::ConstIterator& miheev::Tree< Key, Value, Comparator >::ConstIterator::operator--()
{
  return --iter_;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::ConstIterator miheev::Tree< Key, Value, Comparator >::ConstIterator::operator--(int)
{
  return iter_--;
}

template< typename Key, typename Value, typename Comparator >
bool miheev::Tree< Key, Value, Comparator >::ConstIterator::operator==(const ConstIterator& rhs) const
{
  return *this == rhs.iter_;
}

template< typename Key, typename Value, typename Comparator >
bool miheev::Tree< Key, Value, Comparator >::ConstIterator::operator!=(const ConstIterator& rhs) const
{
  return *this != rhs.iter_;
}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >::~Tree()
{
  clear();
}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator>::Tree():
  key_(Key()),
  value_(Value()),
  pair_(key_, value_),
  height_(0),
  isEmpty_(true),
  left_(nullptr),
  right_(nullptr),
  parrent_(nullptr)
{}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator>::Tree(const Key& key, const Value& value):
  key_(key),
  value_(value),
  pair_(key_, value_),
  height_(1),
  isEmpty_(false),
  left_(nullptr),
  right_(nullptr),
  parrent_(nullptr)
{}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator>::Tree(const miheev::Tree< Key, Value, Comparator >& rhs):
  key_(rhs.key_),
  value_(rhs.value_),
  pair_(key_, value_),
  height_(rhs.height_),
  isEmpty_(rhs.isEmpty_),
  left_(nullptr),
  right_(nullptr),
  parrent_(nullptr)
{
  if (rhs.left_)
  {
    left_ = new Tree(*rhs.left_);
    left_->parrent_ = this;
  }
  if (rhs.right_)
  {
    right_ = new Tree(*rhs.right_);
    right_->parrent_ = this;
  }
}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >& miheev::Tree< Key, Value, Comparator>::operator=(const miheev::Tree< Key, Value, Comparator >& rhs)
{
  clear();
  key_ = rhs.key_;
  value_ = rhs.value_;
  pair_.first = key_;
  pair_.second = value_;
  height_ = rhs.height_;
  isEmpty_ = rhs.isEmpty_;
  if (rhs.left_)
  {
    left_ = new Tree(*rhs.left_);
  }
  if (rhs.right_)
  {
    right_ = new Tree(*rhs.right_);
  }
  return *this;
}

// element access
template< typename Key, typename Value, typename Comparator >
Value& miheev::Tree< Key, Value, Comparator>::at(const Key& key)
{
  Comparator comparator;
  if (key == key_)
  {
    return value_;
  }
  if (comparator(key_, key))
  {
    if (!right_)
    {
      throw std::out_of_range("No key");
    }
    return right_->at(key);
  }
  else
  {
    if (!left_)
    {
      throw std::out_of_range("No key");
    }
    return left_->at(key);
  }
}

template< typename Key, typename Value, typename Comparator >
const Value& miheev::Tree< Key, Value, Comparator>::at(const Key& key) const
{
  return at(key);
}

// modifyers
template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::clear()
{
  if (left_)
  {
    delete left_;
    left_ = nullptr;
  }
  if (right_)
  {
    delete right_;
    right_ = nullptr;
  }
  parrent_ = nullptr;
  isEmpty_ = true;
  height_ = 0;
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::insert(const Key& key, const Value& value)
{
  rawInsert(key, value);
  updateHeight();
  updateParrentsLocally();
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::insert(const std::pair< Key, Value >& pair)
{
  insert(pair->first, pair->second);
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::swap(Tree& tree)
{
  Tree temp = tree;
  temp = *this;
  *this = temp;
}

// printings
template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::printKeys(std::ostream& out) const
{
  if (isEmpty_)
  {
    return;
  }
  if (left_)
  left_->printKeys(out);
  out << key_ << ' ';
  if (right_)
  right_->printKeys(out);
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::printValues(std::ostream& out) const
{
  if (isEmpty_)
  {
    return;
  }
  if (left_)
  left_->printValues(out);
  out << value_ << ' ';
  if (right_)
  right_->printValues(out);
}

// insertions
template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::rawInsert(const Key& key, const Value& value)
{
  Comparator comparator;
  if (isEmpty_)
  {
    *this = Tree(key, value);
    return;
  }
  if(comparator(key, key_))
  {
    if (left_)
    {
      left_->rawInsert(key, value);
    }
    else
    {
      left_ = new Tree(key, value);
    }
  }
  else
  {
    if (right_)
    {
      right_->rawInsert(key, value);
    }
    else
    {
      right_ = new Tree(key, value);
    }
  }
  updateHeight();
  rebalanceSelf();
  updateParrentsLocally();
}

//lookups
template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >* miheev::Tree< Key, Value, Comparator>::getMaxNode()
{
  return right_ ? right_->getMaxNode() : this;
}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >* miheev::Tree< Key, Value, Comparator>::getMinNode()
{
  return left_ ? left_->getMinNode() : this;
}

template< typename Key, typename Value, typename Comparator >
bool miheev::Tree< Key, Value, Comparator>::empty() const noexcept
{
  return isEmpty_;
}

template< typename Key, typename Value, typename Comparator >
size_t miheev::Tree< Key, Value, Comparator>::size() const
{
  size_t leftSize = left_ ? left_->size() : 0;
  size_t rightSize = right_ ? right_->size() : 0;
  return leftSize + rightSize + 1;
}

//delitions

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::erase(const Key& key)
{
  rawDelete(key);
  updateHeight();
  // updateParrentsLocally();
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::rawDelete(const Key& key)
{
  Comparator comparator;
  if (isEmpty_)
  {
    return;
  }
  if (key == key_)
  {
    rawDeleteSelf();
  }
  else
  {
    if (comparator(key, key_) && left_)
    {
      left_->rawDelete(key);
    }
    else if (!comparator(key, key_) && right_)
    {
      right_->rawDelete(key);
    }
  }
  updateHeight();
  rebalanceSelf();
  updateParrentsLocally();
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::rawDeleteSelf()
{
  // о да, минимум 10 тестов на покрытие этого кода)
  if (!left_ && !right_)
  {
    clear();
  }
  else if (!left_ && right_)
  {
    Tree temp = *right_;
    *this = temp;
  }
  else if (left_ && !right_)
  {
    Tree temp = *left_;
    *this = temp;
  }
  else
  {
    Tree temp = *left_->getMaxNode();
    rawDelete(temp.key_);
    key_ = temp.key_;
    value_ = temp.value_;
  }
}

// rebalancings
template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::rebalanceSelf()
{
  if (left_)
  {
    left_->rebalanceSelf();
  }
  if (right_)
  {
    right_->rebalanceSelf();
  }
  int diff = getDiff();
  if (diff == -2)
  {
    if (left_->getDiff() == 1)
    {
      left_->rotateLL();
    }
    rotateRR();
  }
  else if (diff == 2)
  {
    if (right_->getDiff() == -1)
    {
      right_->rotateRR();
    }
    rotateLL();
  }
  updateParrentsLocally();
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::updateParrentsLocally()
{
  if (left_)
  {
    left_->parrent_ = this;
  }
  if (right_)
  {
    right_->parrent_ = this;
  }
}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >* miheev::Tree< Key, Value, Comparator>::findNextNode(const Key& key) const
{
  Comparator comparator;
  if (comparator(key_, key))
  {
    return right_;
  }
  else
  {
    return left_;
  }
}

template< typename Key, typename Value, typename Comparator >
size_t miheev::Tree< Key, Value, Comparator>::getHeight() const
{
  return height_;
}

template< typename Key, typename Value, typename Comparator >
int miheev::Tree< Key, Value, Comparator>::getDiff() const
{
  int leftHeight = left_ ? left_->getHeight() : 0;
  int rightHeight = right_ ? right_->getHeight() : 0;
  return rightHeight - leftHeight;
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::updateHeight()
{
  size_t leftHeight = left_ ? left_->getHeight() : 0;
  size_t rightHeight = right_ ? right_->getHeight() : 0;
  height_ = std::max(leftHeight, rightHeight) + 1;
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::swapNodes(miheev::Tree< Key, Value, Comparator >* lhs, miheev::Tree< Key, Value, Comparator >* rhs)
{
  Key tempKey = lhs->key_;
  lhs->key_ = rhs->key_;
  rhs->key_ = tempKey;
  Value tempValue = lhs->value_;
  lhs->value_ = rhs->value_;
  rhs->value_ = tempValue;
}

//rotations
template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::rotateRR()
{ // нужен только тогда, когда в левом дереве как минимум 2 элемента слева
  swapNodes(left_, this);
  Tree* buff = right_;
  right_ = left_;
  left_ = right_->left_;
  right_->left_ = right_->right_;
  right_->right_ = buff;
  right_->updateHeight();
  updateHeight();
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::rotateLL()
{ // нужен только тогда, когда в левом дереве как минимум 2 элемента справа
  swapNodes(right_, this);
  Tree* buff = left_;
  left_ = right_;
  right_ = left_->right_;
  left_->right_ = left_->left_;
  left_->left_ = buff;
  left_->updateHeight();
  updateHeight();
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::Iterator miheev::Tree< Key, Value, Comparator >::begin()
{
  return getMinNode();
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::Iterator miheev::Tree< Key, Value, Comparator >::end()
{
  return Iterator(this, true);
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::Iterator miheev::Tree< Key, Value, Comparator >::find(const Key& key)
{
  if (key == key_)
  {
    return this;
  }
  Tree* next = findNextNode(key);
  if (next)
  {
    return next->find(key);
  }
  else
  {
    throw std::out_of_range("No such key in list");
  }
  // else if (comparator(key_, key))
  // {
  //   if (!right_)
  //   {
  //     throw std::out_of_range("No such key in list");
  //   }
  //   return right_->find(key);
  // }
  // else
  // {
  //   if (!left_)
  //   {
  //     throw std::out_of_range("No such key in list");
  //   }
  //   return left_->find(key);
  // }
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::ConstIterator miheev::Tree< Key, Value, Comparator >::find(const Key& key) const
{
  return find(key);
}

template< typename Key, typename Value, typename Comparator >
bool miheev::Tree< Key, Value, Comparator >::contains(const Key& key) const
{
  if (key == key_)
  {
    return true;
  }
  const Tree* next = findNextNode(key);
  if (next)
  {
    return next->contains(key);
  }
  else
  {
    return false;
  }
}

template< typename Key, typename Value, typename Comparator >
Value& miheev::Tree< Key, Value, Comparator >::operator[](const Key& key)
{
  try
  {
    return find(key)->second;
  }
  catch (const std::out_of_range&)
  {
    insert(key, Value());
    return find(key)->second;
  }
}

template< typename Key, typename Value, typename Comparator >
const Value& miheev::Tree< Key, Value, Comparator >::operator[](const Key& key) const
{
  try
  {
    return find(key)->second;
  }
  catch (const std::out_of_range&)
  {
    return Value();
  }
}

#endif
