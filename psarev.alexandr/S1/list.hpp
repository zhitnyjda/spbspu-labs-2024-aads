#ifndef LIST_HPP
#define LIST_HPP
#include "unit.hpp"
#include <cstddef>

namespace psarev
{
  template< typename T >
  class List
  {
  public:
    List();
    ~List();

    T& operator[](const size_t index);
    void popFront();
    void popBack();
    void pushFront(T data);
    void pushBack(T data);
    void insert(T data, size_t index);
    void remove(size_t index);
    void clear();
    size_t getSize();

  private:
    size_t size;
    Unit< T >* head;
  };
}

template< typename T >
psarev::List< T >::List()
{
  size = 0;
  head = nullptr;
}

template< typename T >
psarev::List< T >::~List()
{
  clear();
}

template< typename T >
T& psarev::List< T >::operator[](const size_t index)
{
  size_t cntr = 0;
  Unit< T >* curr = this->head;
  while (curr != nullptr)
  {
    if (cntr == index)
    {
      return curr->data;
    }
    curr = curr->next;
    cntr++;
  }
}

template< typename T >
void psarev::List< T >::popFront()
{
  Unit< T >* interim = head;
  head = head->next;
  delete[] interim;

  size--;
}

template<typename T>
void psarev::List<T>::popBack()
{
  remove(size - 1);
}

template<typename T>
void psarev::List<T>::pushFront(T data)
{
  head = new Unit< T >(data, head);
  if (size != 0)
  {
    head->next->prev = head;
  }
  size++;
}

template< typename T >
void psarev::List< T >::pushBack(T data)
{
  if (head == nullptr)
  {
    head = new Unit< T >(data);
  }
  else
  {
    Unit< T >* curr = this->head;
    while (curr->next != nullptr)
    {
      curr = curr->next;
    }
    curr->next = new Unit< T >(data, nullptr, curr);
  }
  size++;
}

template<typename T>
void psarev::List<T>::insert(T data, size_t index)
{
  if (index == 0)
  {
    pushFront(data);
  }
  else
  {
    Unit< T >* pre = this->head;
    for (size_t i = 0; i < (index - 1); i++)
    {
      pre = pre->next;
    }

    pre->next = new Unit< T >(data, pre->next);
    size++;
  }
}

template<typename T>
void psarev::List<T>::remove(size_t index)
{
  if (index == 0)
  {
    popFront();
  }
  else
  {
    Unit< T >* pre = this->head;
    for (size_t i = 0; i < (index - 1); i++)
    {
      pre = pre->next;
    }

    Unit< T >* removable = pre->next;
    pre->next = removable->next;
    delete removable;
    size--;
  }
}

template<typename T>
void psarev::List<T>::clear()
{
  while (size > 0)
  {
    popFront();
  }
}

template< typename T >
size_t psarev::List< T >::getSize()
{
  return size;
}

#endif
