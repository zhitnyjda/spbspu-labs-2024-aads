#ifndef LIST_HPP
#define LIST_HPP

#include "ListIterator.hpp"
#include "Node.hpp"

namespace taskaev
{
  template< typename T>
  class List
  {
  public:
    List();
    ~List() = default;
    List(const List&) = default;
    List(List&&) = default;
    void pushFront(const T& data);
    void popFront();
    void clean();
    bool empty();
    void swap(List<T>& other);
    void reverse();
    ListIterator<T> begin();
    ListIterator<T> end();
    Node<T>* head;
  };

  template <typename T>
  List<T>::List():head(nullptr) {}

  template <typename T>
  void List<T>::pushFront(const T& data)
  {
    Node<T>* node = new Node<T>(data);
    node->next = head;
    head = node;
  }

  template <typename T>
  void List<T>::popFront()
  {
    Node<T>* node = head;
    head = node->next;
    delete node;
  }

  template <typename T>
  void List<T>::clean()
  {
    while (head) { popFront(); }
  }

  template <typename T>
  bool List<T>::empty()
  {
    return(head == nullptr);
  }

  template <typename T>
  void List<T>::swap(List<T>& other)
  {
    Node<T>* temp = head;
    head = other->head;
    other->temp = head;
    delete temp;
  }

  template <typename T>
  void List<T>::reverse()
  {
    if(!head){ return; }
    Node<T>* node = head;
    Node<T>* temp = head->next;
    node->next = nullptr;
    do
    {
      Node<T>* am = temp->next;
      temp->next = node;
      node = temp;
      temp = am;
    } while (temp);
    head = node;
  }

  template <typename T>
  ListIterator<T> List<T>::begin()
  {
    return ListIterator<T>(head);
  }

  template <typename T>
  ListIterator<T> List<T>::end()
  {
    return ListIterator<T>();
  }
}
#endif
