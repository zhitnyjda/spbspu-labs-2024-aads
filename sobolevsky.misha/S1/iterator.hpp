#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "list.hpp"
#include <memory>

namespace sobolevsky
{
  template< typename T >
  class Iterator
  {
  public:
    Iterator(Node< T > * node);
    Iterator(const Iterator< T > &) = default;
    ~Iterator() = default;

    Iterator< T > & operator=(const Iterator< T > &) = default;

    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);

    bool operator!=(const Iterator& other) const;
    bool operator==(const Iterator& other) const;

    T & operator * ();
    T * operator->();

    std::string name();

    Node< T > * currNode = nullptr;
  };
}

template< typename T >
sobolevsky::Iterator< T >::Iterator(Node< T > * node)
{
  currNode = node;
}

template< typename T >
sobolevsky::Iterator< T >& sobolevsky::Iterator< T >::operator++()
{
  if (currNode)
  {
    currNode = currNode->next;
  }
  return *this;
}

template<typename T>
sobolevsky::Iterator<T> sobolevsky::Iterator< T >::operator++(int)
{
  sobolevsky::Iterator< T > temp(*this);
  operator++();
  return temp;
}

template< typename T >
sobolevsky::Iterator< T >& sobolevsky::Iterator< T >::operator--()
{
  if (currNode)
  {
    currNode = currNode->prev;
  }
  return *this;
}

template<typename T>
sobolevsky::Iterator<T> sobolevsky::Iterator< T >::operator--(int)
{
  sobolevsky::Iterator< T > temp(*this);
  operator--();
  return temp;
}

template< typename T >
bool sobolevsky::Iterator< T >::operator!=(const Iterator& other) const
{
  return currNode != other.currNode;
}

template< typename T >
bool sobolevsky::Iterator< T >::operator==(const Iterator& other) const
{
  return currNode == other.currNode;
}

template< typename T >
T & sobolevsky::Iterator< T >::operator * ()
{
  return currNode->data;
}

template< typename T >
T * sobolevsky::Iterator< T >::operator->()
{
  return std::addressof(currNode->data);
}

template< typename T >
std::string sobolevsky::Iterator< T >::name()
{
  return currNode->name;
}

namespace sobolevsky
{
  template< typename T >
  class ConstIterator
  {
  public:
    ConstIterator(Node< T > * node);
    ConstIterator(const ConstIterator< T > &) = default;
    ~ConstIterator() = default;

    ConstIterator< T > & operator=(const ConstIterator< T > &) = default;

    ConstIterator& operator++();
    ConstIterator operator++(int);
    ConstIterator& operator--();
    ConstIterator operator--(int);

    bool operator!=(const ConstIterator& other) const;
    bool operator==(const ConstIterator& other) const;

    T & operator * ();
    T * operator->();

    std::string name();
  private:
    Node< T > * currNode = nullptr;
  };
}

template< typename T >
sobolevsky::ConstIterator< T >::ConstIterator(Node< T > * node)
{
  currNode = node;
}

template< typename T >
sobolevsky::ConstIterator< T >& sobolevsky::ConstIterator< T >::operator++()
{
  if (currNode)
  {
    currNode = currNode->next;
  }
  return *this;
}

template<typename T>
sobolevsky::ConstIterator<T> sobolevsky::ConstIterator< T >::operator++(int)
{
  sobolevsky::ConstIterator< T > temp(*this);
  operator++();
  return temp;
}

template< typename T >
sobolevsky::ConstIterator< T >& sobolevsky::ConstIterator< T >::operator--()
{
  if (currNode)
  {
    currNode = currNode->prev;
  }
  return *this;
}

template<typename T>
sobolevsky::ConstIterator<T> sobolevsky::ConstIterator< T >::operator--(int)
{
  sobolevsky::ConstIterator< T > temp(*this);
  operator--();
  return temp;
}

template< typename T >
bool sobolevsky::ConstIterator< T >::operator!=(const ConstIterator& other) const
{
  return currNode != other.currNode;
}

template< typename T >
bool sobolevsky::ConstIterator< T >::operator==(const ConstIterator& other) const
{
  return currNode == other.currNode;
}

template< typename T >
T & sobolevsky::ConstIterator< T >::operator * ()
{
  return currNode->data;
}

template< typename T >
T * sobolevsky::ConstIterator< T >::operator->()
{
  return std::addressof(currNode->data);
}

template< typename T >
std::string sobolevsky::ConstIterator< T >::name()
{
  return currNode->name;
}

#endif
