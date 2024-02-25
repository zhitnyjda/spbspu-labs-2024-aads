#ifndef LIST_HPP
#define LIST_HPP

#include <utility>

namespace miheev
{
  template< typename T >
  class List
  {
  public:
    List(T data);
    void push(T data);
    void pop();

  private:
    T data_;
    List< T >* next_;

    class Iterator
    {
    private:
      T* cur;

    public:
      T& operator++();
      T& operator++(int);
      T& operator+(size_t);
    };
  };
}

#endif

