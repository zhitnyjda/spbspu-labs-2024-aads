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
      Node * head = nullptr;
      Node * tail = nullptr;
    }

    Node * pushFront(T data)
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
      return ptr;
    }

    Node * pushBack(T data)
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
      return ptr;
    }

    void popFront()
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

    void popBack()
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

    void clear()
    {
      while (head != nullptr)
      {
        popFront();
      }
    }

    void swap(List * list1, List * list2)
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
  private:
    Node * head;
    Node * tail;
    size_t size;
};

#endif
