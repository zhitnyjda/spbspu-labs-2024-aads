#ifndef MAINEARRAY_HPP
#define MAINEARRAY_HPP
#include <iostream>

namespace kaseev {
  template< class T >
  class List
  {
  public:
    List();
    ~List();
    void puchBack(const T *value);
    bool empty();
    size_t size();
  };
}
#endif
