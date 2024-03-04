#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "unit.hpp"

namespace psarev
{
  template<typename T>
  class Iterator
  {
  public:
    Iterator(Unit <T>* unit = nullptr);
    ~Iterator() = default;
    Iterator(const Iterator< T >&) = default;
    Iterator<T>& operator=(const Iterator< T >&) = default;
    Iterator<T>& operator++();
    Iterator<T> operator++(int);

    Iterator<T>& operator--();
    Iterator<T> operator--(int);

    T& operator*();
    T* operator->();

    bool operator==(const Iterator< T >&) const;
    bool operator!=(const Iterator< T >&) const;
  private:
    Unit<T>* unit;
  };
}

template<typename T>
psarev::Iterator<T>::Iterator(Unit <T>* unit) :
  unit(unit)
{}

template <typename T>
psarev::Iterator<T>& psarev::Iterator<T>::operator++()
{
  unit = unit->next;
  return *this;
}

template <typename T>
psarev::Iterator<T> psarev::Iterator<T>::operator++(int)
{
  Iterator<T> inked(*this);
  ++(*this);
  return inked;
}

template <typename T>
psarev::Iterator<T>& psarev::Iterator<T>::operator--()
{
  unit = unit->prev;
  return *this;
}

template <typename T>
psarev::Iterator<T> psarev::Iterator<T>::operator--(int)
{
  Iterator<T> deked(*this);
  --(*this);
  return deked;
}

template<typename T>
T& psarev::Iterator<T>::operator*()
{
  return unit->data;
}

template<typename T>
T* psarev::Iterator<T>::operator->()
{
  return &(unit->data);
}

template<typename T>
inline bool psarev::Iterator<T>::operator==(const Iterator<T>& that) const
{
  return unit == that.unit;
}

template<typename T>
bool psarev::Iterator<T>::operator!=(const Iterator<T>& that) const
{
  return !(that == *this);
}

#endif
