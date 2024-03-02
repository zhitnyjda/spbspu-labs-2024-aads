#ifndef LIST_HPP
#define LIST_HPP
#include "node.hpp"
#include "iterator.hpp"

namespace sobolevsky
{

  template< class T >
  class List
  {
  public:
    List();
    ~List();

    void pushFront(T data);
    void pushBack(T data);
    void popFront();
    void popBack();
    void clear();
    void swap(List * list1, List * list2);

  private:
    Node * head;
    Node * tail;
    size_t size;
  };
}

template< class T >
sobolevsky::List< T >::List()
{
  Node * head = nullptr;
  Node * tail = nullptr;
}

template< class T >
sobolevsky::List< T >::~List()
{
  clear();
}

template< class T >
void sobolevsky::List< T >::pushFront(T data)
{
  Node * ptr = new Node(data);
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

template< class T >
void sobolevsky::List< T >::pushBack(T data)
{
  Node * ptr = new Node(data);
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

template< class T >
void sobolevsky::List< T >::popFront()
{
  if (head == nullptr)
  {
    return;
  }

  Node * ptr = head->next;
  ptr == nullptr ? (tail == nullptr) : (ptr->prev = nullptr);

  delete head;
  size--;
  head = ptr;
}

template< class T >
void sobolevsky::List< T >::popBack()
{
  if (tail == nullptr)
  {
    return;
  }

  Node * ptr = tail->prev;
  ptr == nullptr ? (head == nullptr) : (ptr->next = nullptr);

  delete tail;
  size--;
  tail = ptr;
}

template< class T >
void sobolevsky::List< T >::clear()
{
  while (head != nullptr)
  {
    popFront();
  }
}

template< class T >
void sobolevsky::List< T >::swap(List * list1, List * list2)
{
  if (list1 != nullptr && list2 != nullptr)
  {
    Node * tempHead;
    Node * tempTail;
    size_t tempSize;

    tempHead = list1->head;
    tempTail = list1->tail;
    tempSize = list1->size;

    list1->head = list2->head;
    list1->tail = list2->tail;
    list1->size = list2->size;

    list2->head = tempHead->head;
    list2->tail = tempTail->tail;
    list2->size = tempSize->size;

    delete tempHead;
    delete tempTail;
  }
}

#endif
