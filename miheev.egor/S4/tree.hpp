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

    Tree& operator=(const Tree&);

    // lookup
    void printKeys(std::ostream& = std::cout) const;
    void printValues(std::ostream& = std::cout) const;

    // element access
    Value& operator[](const Key&);
    Value& at(const Key&);
    const Value& at (const Key&) const;

    // capacity
    size_t size() const;
    bool empty() const noexcept;

    //modifiers
    void insert(const Key&, const Value&);
    void insert(std::pair< const Key&, const Value& >);
    void erase(const Key&);
    void clear();
    void swap(const Tree&);

    //operations
    Iterator find(const Key&);
    ConstIterator find(const Key&) const;

    ~Tree();

    void push(Key k, Value v);
    Value get(Key k);

  private:
    Key key_;
    Value value_;

    size_t height_;
    bool isEmpty_;

    Tree* left_;
    Tree* right_;

    // balancing
    size_t getHeight() const;
    void rebalanceSelf();
    bool isBalanced() const;
    int getDiff() const;
    void swapNodes(Tree*, Tree*);
    void updateHeight();

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
    // void rotateLR();
    // void rotateRL();
  };
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
  height_(0),
  isEmpty_(true),
  left_(nullptr),
  right_(nullptr)
{}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator>::Tree(const Key& key, const Value& value):
  key_(key),
  value_(value),
  height_(1),
  isEmpty_(false),
  left_(nullptr),
  right_(nullptr)
{}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator>::Tree(const miheev::Tree< Key, Value, Comparator >& rhs):
  key_(rhs.key_),
  value_(rhs.value_),
  height_(rhs.height_),
  isEmpty_(rhs.isEmpty_),
  left_(nullptr),
  right_(nullptr)
{
  if (rhs.left_)
  {
    left_ = new Tree(*rhs.left_);
  }
  if (rhs.right_)
  {
    right_ = new Tree(*rhs.right_);
  }
}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >& miheev::Tree< Key, Value, Comparator>::operator=(const miheev::Tree< Key, Value, Comparator >& rhs)
{
  clear();
  key_ = rhs.key_;
  value_ = rhs.value_;
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
  isEmpty_ = true;
  height_ = 0;
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::insert(const Key& key, const Value& value)
{
  rawInsert(key, value);
  updateHeight();
  rebalanceSelf();
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
  rebalanceSelf();
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
  size_t leftHeight = left_ ? left_->getHeight() + 1 : 0;
  size_t rightHeight = right_ ? right_->getHeight() + 1 : 0;
  height_ = std::max(leftHeight, rightHeight);
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
{ // нужен только тогда, когда в левом дереве как минимум 2 элемента слева
  swapNodes(right_, this);
  Tree* buff = left_;
  left_ = right_;
  right_ = left_->right_;
  left_->right_ = left_->left_;
  left_->left_ = buff;
  left_->updateHeight();
  updateHeight();
}

#endif
