#ifndef LIST_ITERATOR
#define LIST_ITERATOR
#include "node.hpp"
#include <cassert>
#include <memory>

namespace doroshenko
{
  template<typename T>
  struct ListIterator
  {
    Node<T>* node;

    ListIterator();
    ~ListIterator() = default;
    ListIterator(const ListIterator<T>&) = default;
    ListIterator<T>& operator= (const ListIterator<T>&) = default;
    ListIterator(Node<T>* pointer);

    ListIterator<T>& operator++();
    ListIterator<T> operator++(int);
    T& operator*();
    T* operator->();

    bool operator!=(const ListIterator<T>& rhs) const;
    bool operator==(const ListIterator<T>& rhs) const;
  };
}

template<typename T>
doroshenko::ListIterator<T>::ListIterator() :
  node(nullptr)
{}

template<typename T>
doroshenko::ListIterator<T>::ListIterator(Node<T>* pointer) :
  node(pointer)
{}

template<typename T>
doroshenko::ListIterator<T>& doroshenko::ListIterator<T>::operator++()
{
  assert(node != nullptr);
  node = node->next;
  return *this;
}

template<typename T>
doroshenko::ListIterator<T> doroshenko::ListIterator<T>::operator++(int)
{
  assert(node != nullptr);
  ListIterator<T> result(*this);
  ++(*this);
  return result;
}

template<typename T>
T& doroshenko::ListIterator<T>::operator*()
{
  assert(node != nullptr);
  return node->data;
}

template<typename T>
T* doroshenko::ListIterator<T>::operator->()
{
  assert(node != nullptr);
  return std::addressof(node->data);
}

template<typename T>
bool doroshenko::ListIterator<T>::operator!=(const ListIterator<T>& rhs) const
{
  return node == rhs.node;
}

template<typename T>
bool doroshenko::ListIterator<T>::operator==(const ListIterator<T>& rhs) const
{
  return !(rhs == *this);
}

#endif
