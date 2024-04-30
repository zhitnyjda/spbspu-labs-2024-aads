#ifndef CONST_LIST_ITERATOR_HPP
#define CONST_LIST_ITERATOR_HPP
#include <memory>
#include "node.hpp"

namespace zheleznyakov
{
  template < typename T >
  class ConstListIterator
  {
  public:
    ConstListIterator(const Node< T >*listItem = nullptr);
    ~ConstListIterator() = default;

    ConstListIterator(const ConstListIterator< T >&) = default;
    ConstListIterator< T > &operator=(const ConstListIterator< T >&) const;

    ConstListIterator< T >&operator++();
    ConstListIterator< T >&operator++(int);

    ConstListIterator< T >&operator--();
    ConstListIterator< T >&operator--(int);

    T &operator*() const;
    T *operator->() const;

    bool operator!=(const ConstListIterator< T >&rhs) const;
    bool operator==(const ConstListIterator< T >&rhs) const;

    ConstListIterator begin() const;
    ConstListIterator end() const;

  private:
    Node< T >*listItem;
  };
}

template < typename T >
zheleznyakov::ConstListIterator< T >::ConstListIterator(const Node< T >*listItem) : listItem(listItem) {}

template < typename T >
zheleznyakov::ConstListIterator< T >&zheleznyakov::ConstListIterator< T >::operator++()
{
  listItem = listItem->next;
  return (*this);
}

template < typename T >
zheleznyakov::ConstListIterator< T >&zheleznyakov::ConstListIterator< T >::operator++(int)
{
  ConstListIterator< T >result(*this);
  ++(*this);
  return result;
}

template < typename T >
zheleznyakov::ConstListIterator< T >&zheleznyakov::ConstListIterator< T >::operator--()
{
  listItem = listItem->prev;
  return (*this);
}

template < typename T >
zheleznyakov::ConstListIterator< T >&zheleznyakov::ConstListIterator< T >::operator--(int)
{
  ConstListIterator< T >result(*this);
  --(*this);
  return result;
}

template < typename T >
bool zheleznyakov::ConstListIterator< T >::operator==(const ConstListIterator< T >&rhs) const
{
  return listItem == rhs.listItem;
}

template < typename T >
bool zheleznyakov::ConstListIterator< T >::operator!=(const ConstListIterator< T >&rhs) const
{
  return !(rhs == *this);
}

template < typename T >
T &zheleznyakov::ConstListIterator< T >::operator*() const
{
  return listItem->data;
}

template < typename T >
T *zheleznyakov::ConstListIterator< T >::operator->() const
{
  return std::addressof(listItem->data);
}

template< typename T >
zheleznyakov::ConstListIterator< T >zheleznyakov::ConstListIterator< T >::begin() const
{
  return this;
}

template< typename T >
zheleznyakov::ConstListIterator< T >zheleznyakov::ConstListIterator< T >::end() const
{
  return nullptr;
}
#endif
