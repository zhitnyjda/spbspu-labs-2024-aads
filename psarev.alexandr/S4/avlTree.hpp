#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP
#include <utility>

namespace psarev
{
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  class avlTree
  {
  public:
    class ConstIterator;
    class Iterator;

    using cIter = ConstIterator;
    using iter = Iterator;
    using dataType = std::pair< Key, Value >;

    avlTree();
    avlTree(const avlTree& that);
    avlTree(size_t& initSize, dataType& initData);
    ~avlTree();

    avlTree& operator=(const avlTree& that);
    void clear();

    iter begin() noexcept;
    cIter begin() const noexcept;
    iter end() noexcept;
    cIter end() const noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;

    iter find(Key& key);
    iter insert(dataType& data);
    iter insert(dataType&& data);
    Value& at(const Key& key);
    Value& operator[](const Key& key);
    //void push(Key k, Value v);
    //Value get(Key k);
    //Value drop(Key k);

  private:

    struct Unit
    {
      friend class avlTree;

      dataType data;
      Unit* ancest;
      Unit* left;
      Unit* right;
      size_t hgt;

      Unit(dataType data_, Unit* ancest_ = nullptr, int hgt_ = 0, Unit* left_ = nullptr, Unit* right_ = nullptr)
      {
        this->data = data_;
        this->ancest = ancest_;
        this->left = left_;
        this->right = right_;
        this->hgt = hgt_;
      }
    };

    Unit* treeRoot;
    size_t treeSize;

    void delUnit(Unit* unit);
    size_t getHeight(Unit* unit);

    Unit* llTurn(Unit* moveU);
    Unit* lrTurn(Unit* moveU);
    Unit* rrTurn(Unit* moveU);
    Unit* rlTurn(Unit* moveU);

    Unit* updData(Unit* unit, const dataType& data);
    Unit* updData(Unit* unit, dataType&& data);
  };
}

template < typename Key, typename Value, typename Compare >
class psarev::avlTree< Key, Value, Compare >::ConstIterator : public std::iterator< std::bidirectional_iterator_tag, dataType >
{
public:
  friend class avlTree< Key, Value, Compare >;
  using this_t = ConstIterator;

  ConstIterator();
  ConstIterator(Iterator that);
  ConstIterator(const this_t&) = default;
  ~ConstIterator() = default;

  this_t& operator=(const this_t&) = default;

  this_t& operator++();
  this_t operator++(int);
  this_t& operator--();
  this_t operator--(int);

  const dataType& operator*() const;
  const dataType* operator->() const;

  bool operator==(const this_t& rhs) const;
  bool operator!=(const this_t& rhs) const;

private:
  Unit* unit;
  Unit* root;
  ConstIterator(Unit* unit, Unit* root);
};

template < typename Key, typename Value, typename Compare >
psarev::avlTree< Key, Value, Compare >::ConstIterator::ConstIterator() :
  unit(nullptr),
  root(nullptr)
{}

template < typename Key, typename Value, typename Compare >
psarev::avlTree< Key, Value, Compare >::ConstIterator::ConstIterator(Iterator that) :
  unit(that.imIter.unit),
  root(that.imIter.root)
{}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::ConstIterator& psarev::avlTree< Key, Value, Compare >::ConstIterator::operator++()
{
  if (unit->right != nullptr)
  {
    unit = unit->right;
    while (unit->left != nullptr)
    {
      unit = unit->left;
    }
  }
  else
  {
    while ((unit == unit->ancest->right) && (unit->ancest != nullptr))
    {
      unit = unit->ancest;
    }
    unit = unit->ancest;
  }
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::ConstIterator psarev::avlTree< Key, Value, Compare >::ConstIterator::operator++(int)
{
  this_t inked(*this);
  ++(*this);
  return inked;
}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::ConstIterator& psarev::avlTree< Key, Value, Compare >::ConstIterator::operator--()
{
  if (unit == nullptr)
  {
    unit = root;
    while (unit->right != nullptr)
    {
      unit = unit->right;
    }
  }
  else if (unit->left != nullptr)
  {
    unit = unit->left;
    while (unit->right != nullptr)
    {
      unit = unit->right;
    }
  }
  else
  {
    while ((unit == unit->ancest->left) && (unit->ancest != nullptr))
    {
      unit = unit->ancest;
    }
    unit = unit->ancest;
  }
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::ConstIterator psarev::avlTree< Key, Value, Compare >::ConstIterator::operator--(int)
{
  this_t deked(*this);
  --(*this);
  return deked;
}

template < typename Key, typename Value, typename Compare >
const typename psarev::avlTree< Key, Value, Compare >::dataType& psarev::avlTree< Key, Value, Compare >::ConstIterator::operator*() const
{
  return unit->data;
}

template < typename Key, typename Value, typename Compare >
const typename psarev::avlTree< Key, Value, Compare >::dataType* psarev::avlTree< Key, Value, Compare >::ConstIterator::operator->() const
{
  return &(unit->data);
}

template < typename Key, typename Value, typename Compare >
bool psarev::avlTree< Key, Value, Compare >::ConstIterator::operator==(const this_t& that) const
{
  return unit == that.unit;
}

template < typename Key, typename Value, typename Compare >
bool psarev::avlTree< Key, Value, Compare >::ConstIterator::operator!=(const this_t& that) const
{
  return !(that == *this);
}

template< typename Key, typename Value, typename Compare >
class psarev::avlTree< Key, Value, Compare >::Iterator : public std::iterator< std::bidirectional_iterator_tag, dataType >
{
public:
  friend class avlTree< Key, Value, Compare >;
  using this_t = Iterator;
  Iterator();
  Iterator(ConstIterator constIter);
  Iterator(const this_t&) = default;
  ~Iterator() = default;

  this_t& operator=(const this_t&) = default;
  this_t& operator++();
  this_t operator++(int);
  this_t& operator--();
  this_t operator--(int);
  this_t operator+(size_t index);

  dataType& operator*();
  dataType* operator->();
  const dataType& operator*() const;
  const dataType* operator->() const;

  bool operator==(const this_t&) const;
  bool operator!=(const this_t&) const;

private:
  ConstIterator imIter;
};

template < typename Key, typename Value, typename Compare >
psarev::avlTree< Key, Value, Compare >::Iterator::Iterator() :
  imIter(ConstIterator())
{}

template < typename Key, typename Value, typename Compare >
psarev::avlTree< Key, Value, Compare >::Iterator::Iterator(ConstIterator that) :
  imIter(that)
{}

template< typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::Iterator& psarev::avlTree< Key, Value, Compare >::Iterator::operator++()
{
  assert(imIter != ConstIterator());
  imIter++;
  return imIter;
}

template< typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::Iterator psarev::avlTree< Key, Value, Compare >::Iterator::operator++(int)
{
  ++imIter;
  return imIter;
}

template< typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::Iterator& psarev::avlTree< Key, Value, Compare >::Iterator::operator--()
{
  assert(imIter != nullptr);
  --imIter;
  return imIter;
}

template< typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::Iterator psarev::avlTree< Key, Value, Compare >::Iterator::operator--(int)
{
  --imIter;
  return imIter;
}

template< typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::dataType& psarev::avlTree< Key, Value, Compare >::Iterator::operator*()
{
  return imIter.unit->data;
}

template< typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::dataType* psarev::avlTree< Key, Value, Compare >::Iterator::operator->()
{
  return &(imIter.unit->data);
}

template< typename Key, typename Value, typename Compare >
const typename psarev::avlTree< Key, Value, Compare >::dataType& psarev::avlTree< Key, Value, Compare >::Iterator::operator*() const
{
  return imIter.node_->data;
}

template< typename Key, typename Value, typename Compare >
const typename psarev::avlTree< Key, Value, Compare >::dataType* psarev::avlTree< Key, Value, Compare >::Iterator::operator->() const
{
  return &(imIter.unit->data);
}

template< typename Key, typename Value, typename Compare >
bool psarev::avlTree< Key, Value, Compare >::Iterator::operator==(const this_t& that) const
{
  return imIter == that.imIter;
}

template< typename Key, typename Value, typename Compare >
bool psarev::avlTree< Key, Value, Compare >::Iterator::operator!=(const this_t& that) const
{
  return !(that == *this);
}

//-----------------------------------------------------------------------------------------------------------------------------------

template< typename Key, typename Value, typename Compare >
psarev::avlTree< Key, Value, Compare >::avlTree() :
  treeRoot(nullptr), treeSize(0)
{}

template<typename Key, typename Value, typename Compare>
psarev::avlTree< Key, Value, Compare >::avlTree(const avlTree& that) :
  treeRoot(that.treeRoot), treeSize(that.treeSize)
{}

template<typename Key, typename Value, typename Compare>
psarev::avlTree< Key, Value, Compare >::avlTree(size_t& initSize, dataType& initData)
{
  treeRoot = nullptr;
  treeSize = 0;
  for (size_t i = 0; i < initSize; ++i)
  {
    insert(initData);
  }
}

template< typename Key, typename Value, typename Compare >
psarev::avlTree< Key, Value, Compare >::~avlTree()
{
  clear();
  treeRoot = nullptr;
}

template<typename Key, typename Value, typename Compare>
psarev::avlTree< Key, Value, Compare >& psarev::avlTree<Key, Value, Compare>::operator=(const avlTree& that)
{
  if (this != &that)
  {
    clear();
    for (Iterator iterator = that.begin(); iterator != end(); ++iterator)
    {
      insert(*iterator);
    }
  }
  return *this;
}

template<typename Key, typename Value, typename Compare>
void psarev::avlTree<Key, Value, Compare>::clear()
{
  delUnit(treeRoot);
  treeRoot = nullptr;
}

template<typename Key, typename Value, typename Compare>
typename psarev::avlTree< Key, Value, Compare >::Iterator psarev::avlTree<Key, Value, Compare>::begin() noexcept
{
  Unit* tempo = treeRoot;
  while ((tempo != nullptr) && (tempo->left != nullptr))
  {
    tempo = tempo->left;
  }
  return Iterator(tempo, treeRoot);
}

template<typename Key, typename Value, typename Compare>
typename psarev::avlTree< Key, Value, Compare >::ConstIterator psarev::avlTree<Key, Value, Compare>::begin() const noexcept
{
  Unit* tempo = treeRoot;
  while ((tempo != nullptr) && (tempo->left != nullptr))
  {
    tempo = tempo->left;
  }
  return Iterator(tempo, treeRoot);
}

template<typename Key, typename Value, typename Compare>
typename psarev::avlTree< Key, Value, Compare >::Iterator psarev::avlTree<Key, Value, Compare>::end() noexcept
{
  return Iterator(nullptr, treeRoot);
}

template<typename Key, typename Value, typename Compare>
typename psarev::avlTree< Key, Value, Compare >::ConstIterator psarev::avlTree<Key, Value, Compare>::end() const noexcept
{
  return Iterator(nullptr, treeRoot);
}

template< typename Key, typename Value, typename Compare >
bool psarev::avlTree< Key, Value, Compare >::isEmpty() const noexcept
{
  return (treeSize == 0);
}

template<typename Key, typename Value, typename Compare>
size_t psarev::avlTree< Key, Value, Compare >::getSize() const noexcept
{
  return treeSize;
}

template<typename Key, typename Value, typename Compare>
typename psarev::avlTree< Key, Value, Compare >::Iterator psarev::avlTree<Key, Value, Compare>::find(Key& key)
{
  Compare compare;
  Unit* tempo = treeRoot;

  while (tempo != nullptr)
  {
    if (compare(key, tempo->data.first))
    {
      tempo = tempo->left;
    }
    else if (compare(tempo->data.first, key))
    {
      tempo = tempo->right;
    }
    else
    {
      return ConstIterator(tempo, treeRoot);
    }
  }
  return end();
}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::Iterator psarev::avlTree< Key, Value, Compare >::insert(dataType& data)
{
  treeRoot = updData(treeRoot, data);
  return find(data.first);
}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::Iterator psarev::avlTree< Key, Value, Compare >::insert(dataType&& data)
{
  treeRoot = updData(treeRoot, std::move(data));
  return find(data.first);
}

template<typename Key, typename Value, typename Compare>
Value& psarev::avlTree<Key, Value, Compare>::at(const Key& key)
{
  Compare compare;
  Unit* tempo = treeRoot;
  while (tempo != nullptr)
  {
    if (compare(tempo->data.first, key))
    {
      tempo = tempo->right;
    }
    else if (compare(key, tempo->data.first))
    {
      tempo = tempo->left;
    }
    else
    {
      return tempo->data.second;
    }
  }
}

template<typename Key, typename Value, typename Compare>
Value& psarev::avlTree<Key, Value, Compare>::operator[](const Key& key)
{
  // TODO: insert return statement here
}

template<typename Key, typename Value, typename Compare>
void psarev::avlTree<Key, Value, Compare>::delUnit(Unit* unit)
{
  if (treeRoot != nullptr)
  {
    delUnit(treeRoot->left);
    delUnit(treeRoot->right);
    delete treeRoot;
    treeRoot = nullptr;
  }
}

template < typename Key, typename Value, typename Compare >
size_t psarev::avlTree< Key, Value, Compare >::getHeight(Unit* unit)
{
  size_t height = 0;
  if (unit != nullptr)
  {
    size_t heightL = getHeight(unit->left);
    size_t heightR = getHeight(unit->right);
    height = std::max(heightL, heightR) + 1;
  }
  return height;
}

template<typename Key, typename Value, typename Compare>
typename psarev::avlTree< Key, Value, Compare >::Unit* psarev::avlTree<Key, Value, Compare>::llTurn(Unit* moveU)
{
  Unit* tempo = moveU->right;
  Unit* ancest = moveU->ancest;
  moveU->right = tempo->left;

  if (moveU->right != nullptr)
  {
    moveU->right->ancest = moveU;
  }

  tempo->left = moveU;
  tempo->left->ancest = tempo;
  tempo->ancest = ancest;
  return tempo;
}

template<typename Key, typename Value, typename Compare>
typename psarev::avlTree< Key, Value, Compare >::Unit* psarev::avlTree<Key, Value, Compare>::lrTurn(Unit* moveU)
{
  moveU->left = llTurn(moveU->left);
  Unit* moved = rrTurn(moveU);

  return moved;
}

template<typename Key, typename Value, typename Compare>
typename psarev::avlTree< Key, Value, Compare >::Unit* psarev::avlTree<Key, Value, Compare>::rrTurn(Unit* moveU)
{
  Unit* tempo = moveU->left;
  Unit* ancest = moveU->ancest;
  moveU->left = tempo->right;

  if (moveU->left != nullptr)
  {
    moveU->left->ancest = moveU;
  }

  tempo->right = moveU;
  tempo->right->ancest = tempo;
  tempo->ancest = ancest;
  return tempo;
}

template<typename Key, typename Value, typename Compare>
typename psarev::avlTree< Key, Value, Compare >::Unit* psarev::avlTree<Key, Value, Compare>::rlTurn(Unit* moveU)
{
  moveU->right = rrTurn(moveU->right);
  Unit* moved = llTurn(moveU);

  return moved;
}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::Unit* psarev::avlTree< Key, Value, Compare >::updData(Unit* unit, const dataType& newData)
{
  Compare compare;
  if (unit == nullptr)
  {
    unit = new Unit(newData);
    return unit;
  }
  else
  {
    if (compare(newData.first, unit->data.first))
    {
      unit->left = updData(unit->left, newData);
      unit->left->ancest = unit;
    }
    else if (compare(unit->data.first, newData.first))
    {
      unit->right = updData(unit->right, newData);
      unit->right->ancest = unit;
    }
  }

  size_t differ = 0;
  if (unit->left != nullptr)
  {
    differ = getHeight(unit->left) - getHeight(unit->right);
  }

  if (differ == 2)
  {
    differ = 0;
    if (unit->left != nullptr)
    {
      differ = getHeight(unit->left) - getHeight(unit->right);
    }
    if (differ > 0)
    {
      unit = rrTurn(unit);
    }
    else
    {
      unit = lrTurn(unit);
    }
  }
  else if (differ == -2)
  {
    differ = 0;
    if (unit->left != nullptr)
    {
      differ = getHeight(unit->left) - getHeight(unit->right);
    }
    if (differ > 0)
    {
      unit = rlTurn(unit);
    }
    else
    {
      unit = llTurn(unit);
    }
  }
  return unit;
}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::Unit* psarev::avlTree< Key, Value, Compare >::updData(Unit* unit, dataType&& newData)
{
  Compare compare;
  if (unit == nullptr)
  {
    unit = new Unit(std::move(newData));
    return unit;
  }
  else
  {
    if (compare(newData.first, unit->data.first))
    {
      unit->left = updData(unit->left, std::move(newData));
      unit->left->ancest = unit;
    }
    else if (compare(unit->data.first, newData.first))
    {
      unit->right = updData(unit->right, std::move(newData));
      unit->right->ancest = unit;
    }
  }

  size_t differ = 0;
  if (unit->left != nullptr)
  {
    differ = getHeight(unit->left) - getHeight(unit->right);
  }

  if (differ == 2)
  {
    differ = 0;
    if (unit->left != nullptr)
    {
      differ = getHeight(unit->left) - getHeight(unit->right);
    }
    if (differ > 0)
    {
      unit = rrTurn(unit);
    }
    else
    {
      unit = lrTurn(unit);
    }
  }
  else if (differ == -2)
  {
    differ = 0;
    if (unit->left != nullptr)
    {
      differ = getHeight(unit->left) - getHeight(unit->right);
    }
    if (differ > 0)
    {
      unit = rlTurn(unit);
    }
    else
    {
      unit = llTurn(unit);
    }
  }
  return unit;
}

#endif