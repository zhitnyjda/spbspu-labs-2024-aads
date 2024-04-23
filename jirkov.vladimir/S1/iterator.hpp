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

#endif
