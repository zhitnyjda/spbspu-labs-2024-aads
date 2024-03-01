#ifndef LIST_HPP
#define LIST_HPP
#include "node.hpp"

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
      tail = ptr;
    }

    void clear();
    void swap();
  private:
    Node * head;
    Node * tail;
    size_t size;
};

template< class T >
using ds_t = List< T >;

template< class T >
using in_lst = typename ds_t< T >::Node< T >;

#endif
