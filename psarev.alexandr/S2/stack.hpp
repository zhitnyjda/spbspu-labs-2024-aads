#ifndef STACK_HPP
#define STACK_HPP

namespace psarev
{
  template < typename T >
  class Stack
  {
  public:
    void push(T rhs);
    T drop();
  private:
    List< T > depot;
  };
}

#endif