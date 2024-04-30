#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <memory>
#include "node.hpp"
#include "list-iterator.hpp"

namespace zheleznyakov
{
  template < typename T >
  class List
  {
  public:
    List();
    ~List();
    List(const List< T > &other);
    List(const size_t count, const T &value);
    List(List &&other) noexcept;
    void pushFront(const T &value);
    void pushBack(const T &value);
    size_t getSize();
    void popFront();
    void popBack();
    void clear();
    void swap(size_t index1, size_t index2);
    bool isEmpty();
    void assign(const size_t count, const T &value);
    void remove(size_t i);
    template < typename UnaryPredicate >
    void removeIf(UnaryPredicate predicate);
    T &operator[](const size_t index);

  private:
    size_t size;
    Node< T >*head;
    Node< T >*tail;
  };
};

template < typename T >
zheleznyakov::List< T >::List() : size(0), head(nullptr), tail(nullptr)
{
}

template < typename T >
zheleznyakov::List< T >::List(const List< T >&other) : size(other.size), head(nullptr), tail(nullptr)
{
  if (other.size > 0)
  {
    head = new Node< T >(other.head->value);
    tail = head;
    Node< T >*current = other.head;
    while (current->next != nullptr)
    {
      tail->next = new Node< T >(current->next->value);
      tail = tail->next;
      current = current->next;
    }
  }
}

template < typename T >
zheleznyakov::List< T >::List(const size_t count, const T &value) : size(0), head(nullptr), tail(nullptr)
{
  for (size_t i = 0; i < count; i++)
  {
    pushBack(value);
  }
}

template < typename T >
zheleznyakov::List< T >::List(List &&other) noexcept : size{other.size}, head{other.head}, tail{other.tail}
{
  other.size = 0;
  other.head = nullptr;
  other.tail = nullptr;
}

template < typename T >
zheleznyakov::List< T >::~List()
{
  clear();
}

template < typename T >
size_t zheleznyakov::List< T >::getSize()
{
  return size;
}

template < typename T >
void zheleznyakov::List< T >::pushFront(const T &value)
{
  Node< T >*newNode = new zheleznyakov::Node< T >(value);
  size++;
  if (head == nullptr)
  {
    head = newNode;
    tail = newNode;
    return;
  }
  newNode->next = this->head;
  head->prev = newNode;
  head = newNode;
}

template < typename T >
void zheleznyakov::List< T >::pushBack(const T &value)
{
  Node< T >*newNode = new zheleznyakov::Node< T >(value);
  size++;
  if (head == nullptr)
  {
    head = newNode;
    tail = newNode;
    return;
  }
  newNode->prev = this->tail;
  this->tail->next = newNode;
  this->tail = newNode;
}

template < typename T >
void zheleznyakov::List< T >::popFront()
{
  Node< T >*current = head;
  head = head->next;
  delete current;
  size--;
}

template < typename T >
void zheleznyakov::List< T >::popBack()
{
  Node< T >*current = tail;
  tail = tail->prev;
  delete current;
  size--;
}

template < typename T >
T &zheleznyakov::List< T >::operator[](const size_t index)
{
  Node< T >*currentElement = head;
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
  throw std::out_of_range("Out of range");
}

template < typename T >
void zheleznyakov::List< T >::clear()
{
  while (size != 0)
  {
    popFront();
  }
}

template < typename T >
bool zheleznyakov::List< T >::isEmpty()
{
  return size == 0;
}

template < typename T >
void zheleznyakov::List< T >::swap(size_t index1, size_t index2)
{
  zheleznyakov::Node< T >*currentItem1 = this->head;
  size_t currentIndex1 = 0;
  while (currentIndex1 < index1)
  {
    currentItem1 = currentItem1->next;
    ++currentIndex1;
  }
  zheleznyakov::Node< T >*currentItem2 = this->head;
  size_t currentIndex2 = 0;
  while (currentIndex2 < index2)
  {
    currentItem2 = currentItem2->next;
    ++currentIndex2;
  }
  T tempValue = currentItem1->value;
  currentItem1->value = currentItem2->value;
  currentItem2->value = tempValue;
}

template < typename T >
void zheleznyakov::List< T >::assign(const size_t count, const T &value)
{
  clear();
  for (size_t i = 0; i < count; i++)
  {
    pushBack(value);
  }
}

template < typename T >
void zheleznyakov::List< T >::remove(size_t i)
{
  Node< T >*current = head;
  for (size_t j = 0; j < i; j++)
  {
    current = current->next;
  }

  if (current->prev)
  {
    current->prev->next = current->next;
  }
  else
  {
    head = current->next;
  }

  if (current->next)
  {
    current->next->prev = current->prev;
  }
  else
  {
    tail = current->prev;
  }
}

template < typename T >
template < typename UnaryPredicate >
void zheleznyakov::List< T >::removeIf(UnaryPredicate predicate)
{
  Node< T >*current = head;
  while (current != nullptr)
  {
    Node< T >*next = current->next;
    if (predicate(current->value))
    {
      if (current->prev)
      {
        current->prev->next = current->next;
      }
      else
      {
        head = current->next;
      }

      if (current->next)
      {
        current->next->prev = current->prev;
      }
      else
      {
        tail = current->prev;
      }

      delete current;
      size--;
    }
    current = next;
  }
}
#endif
