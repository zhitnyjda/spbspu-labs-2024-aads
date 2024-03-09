#ifndef LIST_HPP
#define LIST_HPP
#include "iterator.hpp"
#include <cstddef>

namespace psarev
{
  template<typename T>
  class List
  {
  public:
    Iterator< T > begin();
    Iterator< T > end();

    List();
    ~List();

    void popFront();
    void popBack();
    void pushFront(T data);
    void pushBack(T data);
    void insert(T data, size_t index);
    void remove(size_t index);

    void swap(List< T >& other);
    void clear();

    bool empty();
    size_t getSize();

  private:
    size_t size;
    Unit<T>* head;
  };
}

template <typename T>
psarev::Iterator<T> psarev::List<T>::begin()
{
  return Iterator<T>(head);
}

template<typename T>
psarev::Iterator<T> psarev::List< T >::end()
{
  Iterator<T> point = begin();
  while (point.unit != nullptr)
  {
    point++;
  }
  return point;
}

template<typename T>
psarev::List<T>::List()
{
  size = 0;
  head = nullptr;
}

template<typename T>
psarev::List<T>::~List()
{
  clear();
}

template<typename T>
void psarev::List<T>::popFront()
{
  Unit<T>* tempo = head;
  head = head->next;
  delete tempo;

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
  head = new Unit<T>(data, head);
  if (size != 0)
  {
    head->next->prev = head;
  }
  size++;
}

template<typename T>
void psarev::List<T>::pushBack(T data)
{
  if (head == nullptr)
  {
    head = new Unit<T>(data);
  }
  else
  {
    Unit<T>* curr = this->head;
    while (curr->next != nullptr)
    {
      curr = curr->next;
    }
    curr->next = new Unit<T>(data, nullptr, curr);
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
    Unit<T>* previous = this->head;
    for (size_t i = 0; i < (index - 1); i++)
    {
      previous = previous->next;
    }

    previous->next = new Unit<T>(data, previous->next, previous);
    previous = previous->next;
    previous->next->previous = previous;
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
    Unit<T>* previous = this->head;
    for (size_t i = 0; i < (index - 1); i++)
    {
      previous = previous->next;
    }

    Unit<T>* removable = previous->next;
    previous->next = removable->next;
    removable->next->prev = previous;
    delete removable;
    size--;
  }
}

template<typename T>
void psarev::List<T>::swap(List<T>& targetList)
{
  Unit< T > tempoH = targetList.head;
  targetList.head = head;
  head = tempoH;
  size_t tempoS = targetList.size;
  targetList.size = size;
  size = tempoS;
}

template<typename T>
void psarev::List<T>::clear()
{
  while (size > 0)
  {
    popFront();
  }
}

template<typename T>
bool psarev::List<T>::empty()
{
  return this->getSize() == 0;
}

template<typename T>
size_t psarev::List<T>::getSize()
{
  return size;
}

#endif
