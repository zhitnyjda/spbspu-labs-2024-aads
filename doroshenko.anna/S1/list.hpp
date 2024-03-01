#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include "listIterator.hpp"
#include "node.hpp"

namespace doroshenko
{
  template <typename T>
  class List
  {
  public:

    List();
    ~List();

    void pushFront(const T& data);
    void popFront();
    bool isEmpty();
    void clear();
    void swap(List<T>& otherList);

    Node<T>* operator[](const int index);

    ListIterator<T> begin() const;
    ListIterator<T> end() const;

    const ListIterator<T> cbegin() const;
    const ListIterator<T> cend() const;

  private:
    Node<T>* head_;
  };
}

template< typename T >
doroshenko::List<T>::List() :
  head_(nullptr)
{}

template< typename T >
doroshenko::List<T>::~List()
{
  clear();
}

template< typename T >
void doroshenko::List<T>::pushFront(const T& data)
{
  Node<T>* node = new Node<T>(data);
  node->next = head_;
  head_ = node;
}

template< typename T >
void doroshenko::List<T>::popFront()
{
  if (head_ != nullptr)
  {
    Node<T>* node = head_;
    head_ = node->next;
    delete node;
  }
}

template<typename T>
bool doroshenko::List<T>::isEmpty()
{
  if (head_ == nullptr)
  {
    return true;
  }
  return false;
}

template< typename T >
void doroshenko::List<T>::clear()
{
  while (head_ != nullptr)
  {
    popFront();
  }
}

template< typename T >
void doroshenko::List<T>::swap(List<T>& otherList)
{
  doroshenko::Node<T>* head = head_;
  head_ = otherList.head_;
  otherList.head_ = head;
  delete head;
}

template< typename T >
doroshenko::Node<T>* doroshenko::List<T>::operator[](const int index)
{
  if (isEmpty() == true)
  {
    return nullptr;
  }
  Node<T>* head = head_;
  for (int i = 0; i < index; i++)
  {
    head = head->next;
    if (!head)
    {
      return nullptr;
    }
  }
  return head;
}

template< typename T>
doroshenko::ListIterator<T> doroshenko::List<T>::begin() const
{
  return ListIterator<T>(head_);
}

template< typename T>
doroshenko::ListIterator<T> doroshenko::List<T>::end() const
{
  return ListIterator<T>(nullptr);
}

template< typename T>
const doroshenko::ListIterator<T> doroshenko::List<T>::cbegin() const
{
  return ListIterator<T>(head_);
}

template< typename T>
const doroshenko::ListIterator<T> doroshenko::List<T>::cend() const
{
  return ListIterator<T>(nullptr);
}

#endif
