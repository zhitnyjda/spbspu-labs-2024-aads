#ifndef LIST_HPP
#define LIST_HPP

#include <utility>

template< typename T >
class List
{

private:
  std::pair<char*, int*> data_;
  List* next_;
}

#endif
