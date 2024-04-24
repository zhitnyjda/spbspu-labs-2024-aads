#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "node.hpp"
#include <cassert>
#include <memory>

namespace jirkov
{
  template<typename T>
  struct Iterator
  {
    Node<T>* node;
    Iterator();
    ~Iterator() = default;
    Iterator(const Iterator<T>&) = default;
    Iterator<T>& operator= (const Iterator<T>&) = default;
    Iterator(Node<T>* pointer);
    Iterator<T>& operator++();
    Iterator<T> operator++(int);
    T& operator*();
    T* operator->();
    bool operator!=(const Iterator<T>& rhs) const;
    bool operator==(const Iterator<T>& rhs) const;
  };
}

template<typename T>
jirkov::Iterator<T>::Iterator() :
  node(nullptr)
{}

template<typename T>
jirkov::Iterator<T>::Iterator(Node<T>* pointer) :
  node(pointer)
{}

template<typename T>
jirkov::Iterator<T>& jirkov::Iterator<T>::operator++()
{
  assert(node != nullptr);
  node = node->next;
  return *this;
}

template<typename T>
jirkov::Iterator<T> jirkov::Iterator<T>::operator++(int)
{
  assert(node != nullptr);
  Iterator<T> result(*this);
  ++(*this);
  return result;
}

template<typename T>
T& jirkov::Iterator<T>::operator*()
{
  assert(node != nullptr);
  return node->data;
}

template<typename T>
T* jirkov::Iterator<T>::operator->()
{
  assert(node != nullptr);
  return std::addressof(node->data);
}

template<typename T>
bool jirkov::Iterator<T>::operator!=(const Iterator<T>& rhs) const
{
  return node == rhs.node;
}

template<typename T>
bool jirkov::Iterator<T>::operator==(const Iterator<T>& rhs) const
{
  return !(rhs == *this);
}

#endif
