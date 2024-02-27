#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>

namespace miheev
{
  template< typename T >
  class List
  {
  private:
    T data_;
    List< T >* next_;

  public:
    class Iterator;
    List(T data):
      data_(data),
      next_(nullptr)
    {}
    void push(T data)
    {
      if (next_ == nullptr)
      {
        next_ = new List< T >(data);
      }
      else
      {
        this->push(data);
      }
    }

    Iterator begin()
    {

    }
    Iterator end();

    class Iterator
    {
    private:
      T* cur_;

    public:
      Iterator(T* head)
      {
        cur_ = head;
      }
      T& operator++();
      T& operator++(int);
      T& operator+(size_t);
    };
  };
}

#endif

