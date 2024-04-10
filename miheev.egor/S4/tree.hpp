#ifndef TREE_HPP
#define TREE_HPP

namespace miheev
{
  template< typename Key, typename Value, typename Compare >
  class BinarySearchTree
  {
  private:
    Key key_;
    Value value_;
    bool isFictive_ = true;
    Compare cmp_;
    BinarySearchTree* left_;
    BinarySearchTree* right_;
  public:
    BinarySearchTree() = default;
    BinarySearchTree(Key key, Value value, Compare cmp);
    ~BinarySearchTree();

    void push(Key k, Value v);
    Value get(Key k);
    Value drop(Key k);
  };
}

template< typename K, typename V, typename C >
miheev::BinarySearchTree< K, V, C >::~BinarySearchTree()
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

template< typename K, typename V, typename C >
miheev::BinarySearchTree< K, V, C>::BinarySearchTree(K key, V value, C cmp):
  key_(key),
  value_(value),
  isFictive_(false),
  cmp_(cmp)
{}

template< typename K, typename V, typename C >
void miheev::BinarySearchTree< K, V, C>::push(K k, V v)
{
  if (isFictive_)
  {
    key_ = k;
    value_ = v;
  }
}

#endif