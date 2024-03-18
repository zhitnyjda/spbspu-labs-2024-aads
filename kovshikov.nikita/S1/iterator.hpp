#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "node.hpp"
#include <cassert>
#include <memory>

namespace kovshikov
{
  template<typename T>
  struct Iterator
  {
    Node<T>* node;
    using this_t = Iterator<T>;

    Iterator(): node(nullptr) {};
    Iterator(const this_t &) = default;
    ~Iterator() = default;
    this_t & operator=(const this_t &) = default;

    this_t & operator++();
    this_t operator++(int);

    this_t & operator--();
    this_t operator--(int);

    bool operator!=(const this_t & other) const;
    bool operator==(const this_t & other) const;

    T & operator*();
    T * operator->();
  };

  template<typename T>
  typename Iterator<T>::this_t & Iterator<T>::operator++()
  {
    assert(node != nullptr);
    node = node->next;
    return *this;
  }

  template<typename T>
  typename Iterator<T>::this_t Iterator<T>::operator++(int)
  {
    assert(node != nullptr);
    this_t result(*this);
    ++(*this);
    return result;
  }

  template<typename T>
  typename Iterator<T>::this_t & Iterator<T>::operator--()
  {
    assert(node != nullptr);
    node = node->prev;
    return *this;
  }

  template<typename T>
  typename Iterator<T>::this_t Iterator<T>::operator--(int)
  {
    assert(node != nullptr);
    this_t result(*this);
    --(*this);
    return result;
  }

  template<typename T>
  bool Iterator<T>::operator==(const this_t & other) const
  {
    return node == other.node;
  }

  template<typename T>
  bool Iterator<T>::operator!=(const this_t & other) const
  {
    return !(other == *this);
  }

  template<typename T>
  T & Iterator<T>::operator*()
  {
    assert(node != nullptr);
    return node->data;
  }

  template<typename T>
  T * Iterator<T>::operator->()
  {
    assert(node != nullptr);
    return std::addressof(node->data);
  }
}

#endif
