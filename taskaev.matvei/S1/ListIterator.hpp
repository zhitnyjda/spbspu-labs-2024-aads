#ifndef LISTITERATOR_HPP
#define LISTITERATOR_HPP
#include <cassert>
#include <memory>
#include "Node.hpp"

namespace taskaev
{
  template< typename T >
  class ListIterator
  {
  public:
    using this_t = ListIterator<T>;
    ListIterator();
    ListIterator(Node<T>* value);
    ~ListIterator() = default;
    ListIterator(const this_t&) = default;

    this_t& operator++();
    this_t operator++(int);
    this_t& operator = (const this_t&) = default;

    T& operator*();
    T* operator->();

    bool operator!=(const this_t& rhs) const;
    bool operator==(const this_t& rhs) const;
    Node<T>* node;
  };

  template<typename T>
  ListIterator< T >::ListIterator() : node(nullptr) {}

  template<typename T>
  ListIterator< T >::ListIterator(Node<T>* value) : node(value) {}

  template<typename T>
  typename ListIterator< T >::this_t& ListIterator< T >::operator++()
  {
    assert(node != nullptr);
    node = node->next;
    return *this;
  }

  template<typename T>
  typename ListIterator< T >::this_t ListIterator< T >::operator++(int)
  {
    assert(node != nullptr);
    ListIterator< T > result(*this);
    ++(*this);
    return result;
  }

  template<typename T>
  T& ListIterator< T >::operator*()
  {
    assert(node != nullptr);
    return node->data;
  }

  template<typename T>
  T* ListIterator< T >::operator->()
  {
    assert(node != nullptr);
    return std::addressof(node->data);
  }

  template<typename T>
  bool ListIterator< T >::operator==(const this_t& rhs) const
  {
    return (node == rhs.node);
  }

  template<typename T>
  bool ListIterator< T >::operator!=(const this_t& rhs) const
  {
    return !(rhs == *this);
  }
}
#endif
