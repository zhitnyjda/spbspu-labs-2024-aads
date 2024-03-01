#ifndef UNIT_HPP
#define UNIT_HPP

namespace psarev
{
  template< typename T >
  class Unit
  {
  public:
    T data;
    Unit* next;
    Unit* prev;
    Unit(T data = T(), Unit* next = nullptr, Unit* prev = nullptr);
  };

  template< typename T >
  psarev::Unit< T >::Unit(T data, Unit* next, Unit* prev)
  {
    this->data = T();
    this->next = next;
    this->prev = prev;
  }
}
#endif
