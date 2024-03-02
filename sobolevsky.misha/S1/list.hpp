#ifndef LIST_HPP
#define LIST_HPP
#include "node.hpp"
#include "iterator.hpp"

namespace sobolevsky
{

  template< typename T >
  class List
  {
  public:
    Node< T > * head;
    Node< T > * tail;
    size_t size;

    List();
    ~List();

    void pushFront(T data);
    void pushBack(T data);
    void popFront();
    void popBack();
    void clear();
    void swap(List * list1, List * list2);
  };
}

template< typename T >
sobolevsky::List< T >::List()
{
  head = nullptr;
  tail = nullptr;
}

template< typename T >
sobolevsky::List< T >::~List()
{
  clear();
}

template< typename T >
void sobolevsky::List< T >::pushFront(T data)
{
  Node< T > * ptr = new Node(data);
  ptr->next = head;
  if (head != nullptr)
  {
    head->prev = ptr;
  }
  if (tail == nullptr)
  {
    tail = ptr;
  }
  head = ptr;
  size++;
}

template< typename T >
void sobolevsky::List< T >::pushBack(T data)
{
  Node< T > * ptr = new Node(data);
  ptr->prev = tail;
  if (tail != nullptr)
  {
    tail->next = ptr;
  }
  if (head == nullptr)
  {
    head = ptr;
  }
  tail = ptr;
  size++;
}

template< typename T >
void sobolevsky::List< T >::popFront()
{
  if (head == nullptr)
  {
    return;
  }

  Node< T > * ptr = head->next;
  if (ptr == nullptr)
  {
    tail == nullptr;
  }
  else
  {
    ptr->prev = nullptr;
  }

  delete head;
  size--;
  head = ptr;
}

template< typename T >
void sobolevsky::List< T >::popBack()
{
  if (tail == nullptr)
  {
    return;
  }

  Node< T > * ptr = tail->prev;
  if (ptr == nullptr)
  {
    head == nullptr;
  }
  else
  {
    ptr->next = nullptr;
  }

  delete tail;
  size--;
  tail = ptr;
}

template< typename T >
void sobolevsky::List< T >::clear()
{
  while (head != nullptr)
  {
    popFront();
  }
}

template< typename T >
void sobolevsky::List< T >::swap(List * list1, List * list2)
{
  if (list1 != nullptr && list2 != nullptr)
  {
    Node< T > * tempHead;
    Node< T > * tempTail;
    size_t tempSize;

    tempHead = list1->head;
    tempTail = list1->tail;
    tempSize = list1->size;

    list1->head = list2->head;
    list1->tail = list2->tail;
    list1->size = list2->size;

    list2->head = tempHead->head;
    list2->tail = tempTail->tail;
    list2->size = tempSize;

    delete tempHead;
    delete tempTail;
  }
}

#endif
