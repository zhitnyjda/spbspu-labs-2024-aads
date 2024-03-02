#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "list.hpp"

// мой итератор должен
// копироваться -
// иметь деструктор +
// оператор инкремент +
// оператор декремент +
// операция разыменовывания и проверки на равентсво/неравенство -
// конструктор по умолчанию +

template< class T >
class Iterator
{
public:
  friend class List;

  Iterator(): currNode(nullptr) {};
  Iterator(Node * node): currNode(node) {};
  ~Iterator() = default;

  Iterator& operator++()
  {
    if (current)
    {
      current = current->next;
    }
    return *this
  }

  Iterator& operator--()
  {
    if (current)
    {
      current = current->prev;
    }
    return *this
  }

private:
  Node * currNode;
};

#endif
