#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "list.hpp"
#include <memory>

// мой итератор должен
// копироваться +
// иметь деструктор +
// оператор инкремент +
// оператор декремент +
// операция разыменовывания и проверки на равентсво/неравенство +
// конструктор по умолчанию +

namespace sobolevsky
{
  template< class T >
  class Iterator
  {
  public:
    Iterator(Node< T > * node);
    ~Iterator() = default;
    Iterator(const Iterator< T > &) = default;
    Iterator< T > & operator=(const Iterator< T > &) = default;

    Iterator& operator++();
    Iterator& operator--();

    bool operator!=(const Iterator& other) const;
    bool operator==(const Iterator& other) const;

    T & operator*();
    T * operator->();
  private:
    Node * currNode;
  };
}

template< class T >
sobolevsky::Iterator< T >::Iterator(Node< T > * node)
{
  currNode = node;
}

template< class T >
sobolevsky::Iterator< T >& sobolevsky::Iterator< T >::operator++()
{
  if (currNode)
  {
    currNode = currNode->next;
  }
  return *this
}

template< class T >
sobolevsky::Iterator< T >& sobolevsky::Iterator< T >::operator--()
{
  if (currNode)
  {
    currNode = currNode->prev;
  }
  return *this
}

template< class T >
bool sobolevsky::Iterator< T >::operator!=(const Iterator& other) const
{
  return currNode != other.currNode;
}

template< class T >
bool sobolevsky::Iterator< T >::operator==(const Iterator& other) const
{
  return currNode == other.currNode;
}

template< class T >
T & sobolevsky::Iterator< T >::operator*()
{
  if (node != nullptr)
  {
    return node->data;
  }
}

template< class T >
T * sobolevsky::Iterator< T >::operator->()
{
  if (node != nullptr)
  {
    return std::addressof(node->data);
  }
}

#endif
