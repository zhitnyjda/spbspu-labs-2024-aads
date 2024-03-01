#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "list.hpp"
#include "node.hpp"

namespace nikiforov
{
  template <typename T>
  class Iterator
  {
  public:
    Iterator(Node<T>* pNode) : pNode(pNode) { }
    ~Iterator() = default;
    Iterator(const Iterator<T>&) = default;

    T& operator*();
    const T& operator*() const;
    T* operator->();
    const T* operator->() const;

    bool operator!=(const Iterator& lhs) const;
    bool operator==(const Iterator& lhs) const;

    Iterator<T> operator++(int);

  private:
    Node<T>* pNode;
  };

  template<typename T>
  T& Iterator<T>::operator*()
  {
    return pNode->data;
  }

  template<typename T>
  const T& Iterator<T>::operator*() const
  {
    return pNode->data;
  }

  template<typename T>
  T* Iterator<T>::operator->()
  {
    return &(pNode->data);
  }

  template<typename T>
  const T* Iterator<T>::operator->() const
  {
    return &(pNode->data);
  }

  template<typename T>
  bool Iterator<T>::operator!=(const Iterator& lhs) const
  {
    return !(*this == lhs);
  }

  template<typename T>
  bool Iterator<T>::operator==(const Iterator& lhs) const
  {
    return pNode == lhs.pNode;
  }


  template<typename T>
  Iterator<T> Iterator<T>::operator++(int)
  {
    if (pNode != nullptr)
      pNode = pNode->pNext;
    return *this;
  }
}

#endif
