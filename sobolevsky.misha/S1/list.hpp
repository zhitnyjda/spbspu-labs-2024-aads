#ifndef LIST_HPP
#define LIST_HPP
#include "node.hpp"
#include "iterator.hpp"

template< class T >
class Iterator;

template< class T >
class List
{
  public:
    List()
    {
      Node * head = NULL;
      Node * tail = NULL;
    }

    Node * pushFront(T data)
    {
      Node * ptr = new Node(data);
      ptr->next = head;
      if (head != NULL)
      {
        head->prev = ptr;
      }
      if (tail == NULL)
      {
        tail = ptr;
      }
      head = ptr;
      size++;
      return ptr;
    }

    Node * pushBack(T data)
    {
      Node * ptr = new Node(data);
      ptr->prev = tail;
      if (tail != NULL)
      {
        tail->next = ptr;
      }
      if (head == NULL)
      {
        head = ptr;
      }
      tail = ptr;
      size++;
      return ptr;
    }

    void popFront()
    {
      if (head == NULL)
      {
        return;
      }

      Node * ptr = head->next;
      ptr == NULL ? (tail == NULL) : (ptr->prev = NULL);

      delete head;
      size--;
      head = ptr;
    }

    void popBack()
    {
      if (tail == NULL)
      {
        return;
      }

      Node * ptr = tail->prev;
      ptr == NULL ? (head == NULL) : (ptr->next = NULL);

      delete tail;
      size--;
      tail = ptr;
    }

    void clear()
    {
      while (head != NULL)
      {
        popFront();
      }
    }

    void swap();
  private:
    Node * head;
    Node * tail;
    size_t size;
};

#endif
