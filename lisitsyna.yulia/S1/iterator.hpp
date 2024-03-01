#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <memory>

namespace lisitsyna
{
  template< typename T >
  struct ListIterator {
    List< T >* node;
    using this_t = ListIterator< T >;

    ListIterator() : node(nullptr) {}
    ~ListIterator() = default;
    ListIterator(const this_t&) = default;
    this_t& operator=(const this_t&) = default;
    this_t& operator++();
    this_t operator++(int);
    T& operator*(); //+ const-версия
    T* operator->(); //+ const-версия
    bool operator!=(const this_t&) const;
    bool operator==(const this_t&) const;
  };
}
#endif
