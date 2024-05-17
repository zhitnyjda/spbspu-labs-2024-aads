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

    void push(Key k, Value v);
    Value get(Key k);
    Value drop(Key k);

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
  };

  template < typename Key, typename Value, typename Compare >
  class psarev::avlTree< Key, Value, Compare >::ConstIterator : public std::iterator< std::bidirectional_iterator_tag, dataType >
  {
  public:
    friend class avlTree< Key, Value, Compare >;
    using this_t = ConstIterator;

    ConstIterator()
    {
      unit(nullptr), root(nullptr)
    }
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
    friend class Tree< Key, Value, Compare >;
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

  template< typename Key, typename Value, typename Compare >
  psarev::avlTree< Key, Value, Compare >::Iterator::Iterator() :
    imIter(ConstIterator())
  {}

  template< typename Key, typename Value, typename Compare >
  psarev::avlTree< Key, Value, Compare >::Iterator::Iterator(ConstIterator constIter) :
    imIter(constIter)
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

}

#endif