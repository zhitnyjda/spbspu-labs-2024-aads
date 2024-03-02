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

template< class T >
class Iterator
{
public:
  friend class List;

  Iterator(): currNode(nullptr) {};
  Iterator(Node * node): currNode(node) {};
  ~Iterator() = default;
  Iterator(const Iterator< T > &) = default;
  Iterator< T > & operator=(const Iterator< T > &) = default;

  Iterator& operator++()
  {
    if (currNode)
    {
      currNode = currNode->next;
    }
    return *this
  }

  Iterator& operator--()
  {
    if (currNode)
    {
      currNode = currNode->prev;
    }
    return *this
  }

  bool operator!=(const Iterator& other) const
  {
    return currNode != other.currNode;
  }

  bool operator==(const Iterator& other) const
  {
    return currNode == other.currNode;
  }

  T & operator*()
  {
    if (node != nullptr)
    {
      return node->data;
    }
  }

  T * operator->()
  {
    if (node != nullptr)
    {
      return std::addressof(node->data);
    }
  }

private:
  Node * currNode;
};

#endif
