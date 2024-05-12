#ifndef TREE_HPP
#define TREE_HPP

#include <utility>
#include <cstddef>
#include <iostream>
#include <functional>

namespace miheev
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class Tree
  {
  public:
    class Iterator;
    class ConstIterator;

    Tree() = default;
    Tree(const Key& key, const Value& value);
    Tree(const Tree&);

    Tree& operator=(const Tree&);

    // lookup
    void printKeys(std::ostream& = std::cout);
    void printValues(std::ostream& = std::cout);

    // element access
    Value& operator[](const Key&);
    Value& at(const Key&);
    const Value& at (const Key&) const;

    // capacity
    size_t size() const noexcept;
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

    size_t size_;
    size_t height_;
    bool isEmpty_ = true;

    Tree* parent_;
    Tree* left_;
    Tree* right_;

    // balancing
    size_t getHeight() const;
    void rebalance();
    void rebalanceSelf();
    bool isBalanced() const;
    int getDiff() const;

    // lookups and node search
    Tree* getMaxNode();
    Tree* getMinNode();

    // insertions
    void rawInsert(const Key&, const Value&);
    void rawDelete(const Key&);
    void rawDeleteSelf();

    // rotations
    Tree* rotateRR(Tree*);
    Tree* rotateLL(Tree*);
    Tree* rotateLR(Tree*);
    Tree* rotateRL(Tree*);
  };
}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >::~Tree()
{
  if (left_)
  {
    delete left_;
  }
  if (right_)
  {
    delete right_;
  }
}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator>::Tree(const Key& key, const Value& value):
  key_(key),
  value_(value),
  size_(1),
  height_(1),
  isEmpty_(false)
{
  left_ = new Tree();
  left_->parent_ = this;
  right_ = new Tree();
  right_->parent_ = this;
}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >& miheev::Tree< Key, Value, Comparator>::operator=(const miheev::Tree< Key, Value, Comparator >& rhs)
{
  key_ = rhs.key_;
  value_ = rhs.value_;
  size_ = rhs.size_;
  height_ = rhs.height_;
  isEmpty_ = rhs.isEmpty_;
  if (!rhs.isEmpty_)
  {
    right_ = new Tree();
    *right_ = *rhs.right_;
    left_ = new Tree();
    *left_ = *rhs.left_;
  }
  return *this;
}
// printings
template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::printKeys(std::ostream& out)
{
  if (isEmpty_)
  {
    return;
  }
  left_->printKeys(out);
  out << key_ << ' ';
  right_->printKeys(out);
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::printValues(std::ostream& out)
{
  if (isEmpty_)
  {
    return;
  }
  left_->printValues(out);
  out << value_ << ' ';
  right_->printValues(out);
}
// insertions
template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::rawInsert(const Key& key, const Value& value)
{
  Comparator comparator;
  if (isEmpty_)
  {
    // key_ = key;
    // value_ = value;
    // isEmpty_ = false;
    // size_ = 1;
    // height_ = 1;
    // left_ = new Tree();
    // right_ = new Tree();
    *this = Tree(key, value);
    return;
  }
  if(comparator(key, key_))
  {
    left_->rawInsert(key, value);
  }
  else
  {
    right_->rawInsert(key, value);
  }
  height_ = std::max(left_->getHeight(), right_->getHeight());
  size_++;
}

//lookups
template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >* miheev::Tree< Key, Value, Comparator>::getMaxNode()
{
  return right_->empty() ? this : right_->getMaxNode();
}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >* miheev::Tree< Key, Value, Comparator>::getMinNode()
{
  return left_->empty() ? this : left_->getMinNode();
}

//delitions
template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::rawDelete(const Key& key)
{
  Comparator comparator;
  if (isEmpty_)
  {
    return;
  }
  if (key != key_)
  {
    if (comparator(key, key_))
    {
      left_->rawDelete(key);
    }
    else
    {
      right_->rawDelete(key);
    }
  }
  height_ = std::max(left_->getHeight(), right_->getHeight());
  size_--;
  // Не забудь обновить высоту
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::rawDeleteSelf()
{
  if (left_->empty() && !right_->empty())
  {
    *this = *right_;
    delete right_;
  }
  else if (!left_->empty() && right_->empty())
  {
    *this = *left_;
    delete left_;
  }
  else
  {
  }
}


// rebalancings
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
  return leftHeight - rightHeight;
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::rebalance()
{
  if (size_ == 1) // is a leave
  {
    return;
  }
  left_->rebalance();
  right_->rebalance();
  rebalanceSelf();
}

#endif