#ifndef LISTITERATOR_HPP
#define LISTITERATOR_HPP

#include <cassert>
#include <memory>
#include "Node.hpp"
#include <iostream>

namespace sukacheva {
  template <class T>
  struct Iterator {
  public:
    Node< T >* node;
    Iterator(Node< T >* node_) : node(node_) {}
    ~Iterator() = default;
    Iterator(const Iterator< T >&) = default;
    Iterator< T >& operator=(const Iterator< T >&) = default;

    Iterator< T >& operator++();
    Iterator< T > operator++(int);

    T& operator*();
    T* operator->();

    bool operator!=(const Iterator< T >&) const;
    bool operator==(const Iterator< T >&) const;
  };

  template <class T>
  struct ConstIterator {
  public:
    Node< T >* node;
    ConstIterator(Node< T >* node_) : node(node_) {}
    ~ConstIterator() = default;
    ConstIterator(const ConstIterator< T >&) = default;
    ConstIterator< T >& operator=(const ConstIterator< T >&) = default;

    ConstIterator< T >& operator++();
    ConstIterator< T > operator++(int);

    T& operator*() const;
    T* operator->() const;

    bool operator!=(const ConstIterator< T >& rhs) const;
    bool operator==(const ConstIterator< T >& rhs) const;
  };

  template<class T>
  ConstIterator<T>& ConstIterator<T>::operator++()
  {
    node = node->next;
    return *this;
  }

  template<class T>
  ConstIterator<T> sukacheva::ConstIterator<T>::operator++(int)
  {
    ConstIterator<T> result(*this);
    ++(*this);
    return result;
  }

  template< class T >
  bool ConstIterator<T>::operator==(const ConstIterator<T>& rhs) const {
    return node == rhs.node;
  }

  template< class T >
  bool ConstIterator<T>::operator!=(const ConstIterator<T>& rhs) const {
    return !(rhs == *this);
  }

  template<class T>
  T& ConstIterator<T>::operator*() const
  {
    if (node == nullptr) {
      std::cout << "some errors..";
    }
    else {
      return (node->data);
    }
  }

  template< class T >
  T* ConstIterator<T>::operator->() const
  {
    assert(node != nullptr);
    return std::addressof(node->data);
  }

  template<class T>
  Iterator<T>& Iterator<T>::operator++()
  {
    node = node->next;
    return *this;
  }

  template< class T>
  Iterator< T > Iterator< T >::operator++(int) {
    Iterator< T > result(*this);
    ++(*this);
    return result;
  }

  template< class T >
  bool Iterator< T >::operator==(const Iterator< T >& rhs) const {
    return node == rhs.node;
  }

  template< class T >
  bool Iterator< T >::operator!=(const Iterator< T >& rhs) const {
    return !(rhs == *this);
  }

  template<class T>
  T& Iterator< T >::operator*()
  {
    if (node == nullptr) {
      std::cout << "some errors..";
    }
    else {
      return (node->data);
    }
  }

  template< class T >
  T* Iterator< T >::operator->() {
    assert(node != nullptr);
    return std::addressof(node->data);
  }
}

#endif
