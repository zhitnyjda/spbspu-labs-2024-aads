#ifndef LIST_ITERATOR_HPP
#define LIST_ITERATOR_HPP
#include <memory>
#include "node.hpp"

namespace zheleznyakov
{
  template < typename T >
  class ListIterator
  {
  public:
    ListIterator(Node<  T  >*listItem = nullptr);
    ~ListIterator() = default;

    ListIterator(const ListIterator<  T  >&) = default;
    ListIterator<  T> &operator=(const ListIterator<T  >&);

    ListIterator<  T  >&operator++();
    ListIterator<  T  >&operator++(int);

    ListIterator<  T  >&operator--();
    ListIterator<  T  >&operator--(int);

    T &operator*();
    T *operator->();

    bool operator!=(const ListIterator<  T  >&rhs) const;
    bool operator==(const ListIterator<  T  >&rhs) const;

    ListIterator begin();
    ListIterator end();

  private:
    Node<  T  >*listItem;
  };
}

template < typename T >
zheleznyakov::ListIterator<  T>::ListIterator(Node<T  >*listItem) : listItem(listItem) {}

template < typename T >
zheleznyakov::ListIterator< T >&zheleznyakov::ListIterator< T >::operator++()
{
  listItem = listItem->next;
  return (*this);
}

template < typename T >
zheleznyakov::ListIterator< T >&zheleznyakov::ListIterator< T >::operator++(int)
{
  ListIterator<  T  >result(*this);
  ++(*this);
  return result;
}

template < typename T >
zheleznyakov::ListIterator< T >&zheleznyakov::ListIterator< T >::operator--()
{
  listItem = listItem->prev;
  return (*this);
}

template < typename T >
zheleznyakov::ListIterator< T >&zheleznyakov::ListIterator< T >::operator--(int)
{
  ListIterator<  T  >result(*this);
  --(*this);
  return result;
}

template < typename T >
bool zheleznyakov::ListIterator<  T>::operator==(const ListIterator<T  >&rhs) const
{
  return listItem == rhs.listItem;
}

template < typename T >
bool zheleznyakov::ListIterator<  T>::operator!=(const ListIterator<T  >&rhs) const
{
  return !(rhs == *this);
}

template < typename T >
T &zheleznyakov::ListIterator< T >::operator*()
{
  return listItem->data;
}

template < typename T >
T *zheleznyakov::ListIterator< T >::operator->()
{
  return std::addressof(listItem->data);
}

template< typename T >
zheleznyakov::ListIterator< T >zheleznyakov::ListIterator< T >::begin()
{
  return this;
}

template< typename T >
zheleznyakov::ListIterator< T >zheleznyakov::ListIterator< T >::end()
{
  return nullptr;
}
#endif
