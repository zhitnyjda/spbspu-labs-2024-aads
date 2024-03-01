#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>
#include "node.hpp"

namespace Panov
{
  template< typename T >
  class Iterator : public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    Iterator(Node< T >* node);
    Iterator(const Iterator&) = default;
    ~Iterator() = default;

    T& operator*();
    T* operator->();
    const T& operator*() const;
    const T* operator->() const;
    Iterator< T >& operator=(const Iterator&) = default;
    Iterator< T >& operator++();
    Iterator< T > operator++(int);
    Iterator< T >& operator--();
    Iterator< T > operator--(int);
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;

    Iterator< T >& advance(int n);

  private:
    Node< T >* node_;
  };

  template< typename T >
  Iterator< T >::Iterator(Node< T >* node) :
    node_(node)
  {}

  template< typename T >
  Iterator< T >& Iterator< T >::operator++()
  {
    node_ = node_->next_;
    return *this;
  }

  template< typename T >
  Iterator< T > Iterator< T >::operator++(int)
  {
    Iterator temp(*this);
    node_ = node_->next_;
    return temp;
  }

  template< typename T >
  Iterator< T >& Iterator< T >::operator--()
  {
    node_ = node_->prev_;
    return *this;
  }

  template< typename T >
  Iterator< T > Iterator< T >::operator--(int)
  {
    Iterator temp(*this);
    node_ = node_->prev_;
    return temp;
  }

  template< typename T >
  bool Iterator< T >::operator==(const Iterator& other) const
  {
    return node_ == other.node_;
  }

  template< typename T >
  bool Iterator< T >::operator!=(const Iterator& other) const
  {
    return node_ != other.node_;
  }

  template< typename T >
  Iterator< T >& Iterator< T >::advance(int n)
  {
    if (n > 0)
    {
      for (int i = 0; i != n; ++i)
      {
        node_ = node_->next_;
      }
    }
    else if (n < 0)
    {
      for (int i = 0; i != -n; ++i)
      {
        node_ = node_->prev_;
      }
    }
    return *this;
  }
}
#endif
