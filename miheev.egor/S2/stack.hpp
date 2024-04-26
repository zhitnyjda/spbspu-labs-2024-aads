#ifndef STACK_HPP
#define STACK_HPP

#include "list.hpp"

namespace miheev
{
  template< typename T >
  class Stack
  {
  public:
    Stack();
    Stack(const T&);
    Stack(const Stack&);
    ~Stack();

    bool empty() const;
    size_t size() const;
    T& top();
    const T& top() const;
    void push(const T&);
    void pop();
    void swap(Stack&) noexcept;
  private:
    List< T > container_;
  }
}

#endif
