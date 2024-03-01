#ifndef LISTITERATOR_HPP
#define LISTITERATOR_HPP

#include "node.hpp"

namespace khoroshkin
{
  template < typename T >
  class ListIterator
  {
  public:
    Node< T > * node;

    ListIterator(Node < T > * newNode = nullptr);
    ~ListIterator() = default;
    ListIterator(const ListIterator< T > &) = default;
    ListIterator< T > & operator=(const ListIterator< T > &) = default;

    ListIterator< T > & operator++();
    ListIterator< T > operator++(int);

    T & operator*();
    T * operator->();

    bool operator!=(const ListIterator< T > &) const;
    bool operator==(const ListIterator< T > &) const;
  };
}

template < typename T >
khoroshkin::ListIterator< T >::ListIterator(Node < T > * newNode) :
  node(newNode)
{}

template < typename T >
khoroshkin::ListIterator< T > & khoroshkin::ListIterator< T >::operator++()
{
  node = node->pNext;
  return *this;
}

template < typename T >
khoroshkin::ListIterator< T > khoroshkin::ListIterator< T >::operator++(int)
{
  ListIterator< T > result(*this);
  ++(*this);
  return result;
}

template< typename T >
T & khoroshkin::ListIterator< T >::operator*() {
  return node->data;
}

template< typename T >
T * khoroshkin::ListIterator< T >::operator->() {
  return std::addressof(node->data);
}

template< typename T >
bool khoroshkin::ListIterator< T >::operator!=(const khoroshkin::ListIterator< T > & rhs) const {
  return !(rhs == *this);
}

template< typename T >
bool khoroshkin::ListIterator< T >::operator==(const khoroshkin::ListIterator< T > & rhs) const {
  return node == rhs.node;
}

#endif
