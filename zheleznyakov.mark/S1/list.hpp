#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <stdexcept>
#include "list-item.hpp"

namespace zheleznyakov
{
  template < typename T >
  class List
  {
  public:
    List();
    void pushFront(T value);
    void pushBack(T value);
    size_t getSize();
    void popFront();
    void popBack();
    void clear();
    bool isEmpty();
    T operator[](const size_t index);

  private:
    size_t size;
    ListItem<T> *head;
    ListItem<T> *tail;
  };
};

template<typename T>
zheleznyakov::List<T>::List() :
  size(0), head(nullptr), tail(nullptr)
{
}

template< typename T >
size_t zheleznyakov::List< T >::getSize()
{
  return size;
}

template <typename T>
void zheleznyakov::List< T >::pushFront(T value)
{
  ListItem<T> *newListItem = new zheleznyakov::ListItem<T>(value);
  size++;
  if (head == nullptr)
  {
    head = newListItem;
    tail = newListItem;
    return;
  }
  newListItem->next = this->head;
  head->prev = newListItem;
  head = newListItem;
}

template<typename T>
void zheleznyakov::List<T>::pushBack(T value)
{
  ListItem<T> *newListItem = new zheleznyakov::ListItem<T>(value);
  size++;
  if (head == nullptr)
  {
    head = newListItem;
    tail = newListItem;
    return;
  }
  newListItem->prev = this->tail;
  this->tail->next = newListItem;
  this->tail = newListItem;
}

template< typename T >
void zheleznyakov::List< T >::popFront()
{
  ListItem< T >* current = head;
  head = head->next;
  delete[] current;
  size--;
}

template< typename T >
void zheleznyakov::List< T >::popBack()
{
  ListItem< T >* current = tail;
  tail = tail->prev;
  delete[] current;
  size--;
}

template< typename T >
T zheleznyakov::List< T >::operator[](const size_t index)
{
  ListItem< T >* currentElement = head;
  size_t currentIndex = 0;
  while (currentElement != nullptr)
  {
    if (currentIndex == index)
    {
      return currentElement->value;
    }
    currentElement = currentElement->next;
    currentIndex++;
  }
  throw new std::runtime_error("Element not found");
}

template< typename T >
void zheleznyakov::List< T >::clear()
{
  while (size != 0)
  {
    popFront();
  }
}

template< typename T>
bool zheleznyakov::List< T >::isEmpty()
{
  return size == 0;
}
#endif
