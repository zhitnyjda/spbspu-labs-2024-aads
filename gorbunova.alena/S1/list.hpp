#ifndef LIST_HPP
#define LIST_HPP
#include "node.hpp"

namespace gorbunova
{
  template<typename T>
  class List
  {
  public:
    List();
    ~List();

    void pushFront(T data);
    void pushBack(T data);
    void popFront();
    void removeAt(int index);
    void popBack();
    void clear();

  private:
    int count;
    Node<T>* head;
  };
}

template<typename T>
gorbunova::List<T>::List()
{
  count = 0;
  head = nullptr;
}

template<typename T>
gorbunova::List<T>::~List()
{
  clear();
}

template<typename T>
void gorbunova::List<T>::pushFront(T data)
{
  head = new Node<T>(data, head);
  count++;
}

template<typename T>
void gorbunova::List<T>::pushBack(T data)
{
  if (head == nullptr)
  {
    head = new Node<T>(data);
  }
  else
  {
    Node<T>* curr = this->head;
    while (curr->next != nullptr)
    {
      curr = curr->next;
    }
    curr->next = new Node<T>(data);
  }
  count++;
}

template<typename T>
void gorbunova::List<T>::popFront()
{
  Node<T>* temp = head;
  head = head->next;
  delete temp;
  count--;
}

void gorbunova::List<T>::removeAt(int index)
{
  if (index == 0)
  {
    popFront();
  }
  else
  {
    Node<T>* prev = this->head;
    for (int i = 0; i < index - 1; i++)
    {
      prev = prev->next;
    }
    Node<T>* toDelete = prev->next;
    prev->next = toDelete->next;
    delete toDelete;
    count--;
  }
}

template<typename T>
void gorbunova::List<T>::popBack()
{
  removeAt(count - 1);
}

template<typename T>
void gorbunova::List<T>::clear()
{
  while (count)
  {
    popFront();
  }
}

#endif
