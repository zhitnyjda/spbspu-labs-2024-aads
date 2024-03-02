#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "node.hpp"

// мой итератор должен
// копироваться -
// иметь деструктор +
// оператор инкремент -
// оператор декремент -
// операция разыменовывания и проверки на равентсво/неравенство -
// конструктор по умолчанию -

template< class T >
class Iterator
{
public:
  ~Iterator() = default;
  
private:
  Node * node;
  using this_t = Iterator< T >;
};

#endif
