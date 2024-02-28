#ifndef CLASSLIST_HPP
#define CLASSLIST_HPP
#include <stddef.h>
#include <iostream>
#include <string>

namespace mihalchenko
{
  template <typename T>
  class List
  {
  public:
    List();
    ~List();

    void push_front(T data, size_t i);
    void pushBack(T data);
    void pop_front();
    void pop_back();
    void insert(T value, size_t i);
    void removeAt(size_t i);
    T &operator[](const int i);
    void clear();

    size_t getSize() { return size_; };

  private:
    template <typename U>
    class ListIterator
    {
    public:
      U &operator=(const U &) = default;
      U &operator++();
      U operator++(int);
      U &operator*();
      U *operator->();

      bool operator==(const U &) const;
      bool operator!=(const U &) const;

      ListIterator getPointerNext() { return pNext_; };
      U getSize() { return data_; };

    private:
      ListIterator(U data = U(), ListIterator *pNext = nullptr)
      {
        data_(data);
        pNext_(pNext);
      }

      ListIterator *pNext_;
      U data_;
    };
    ListIterator<T> *begin_;
    ListIterator<T> *node_;
    ListIterator<T> head;
    size_t size_;
  };
}

template <typename T>
mihalchenko::List<T>::List()
{
  size_ = 0;
  head = nullptr;
}

template <typename T>
void mihalchenko::List<T>::push_front(T data, size_t i)
{
  begin_ = new ListIterator<T>(data, begin_);
  size_++;
}

template <typename T>
void mihalchenko::List<T>::pushBack(T data)
{
  if (begin_ == nullptr)
  {
    begin_ = new ListIterator<T>(data);
  }
  else
  {
    ListIterator<T> *actual = this->begin_;
    while (actual->pNext_ != nullptr)
    {
      actual = actual->pNext_;
    }
    actual->pNext_ = new ListIterator<T>(data);
  }
  size_++;
}

template <typename T>
void mihalchenko::List<T>::pop_front()
{
  ListIterator<T> *temp = begin_;
  begin_ = begin_->pNext;
  delete temp;
  size_--;
}

template <typename T>
void mihalchenko::List<T>::pop_back()
{
  removeAt(size_--);
}

template <typename T>
void mihalchenko::List<T>::insert(T data, size_t index)
{
  if (index == 0)
  {
    push_front(data);
  }
  else
  {
    ListIterator<T> *previous = this->begin_;
    for (size_t i = 0; i < index - 1; i++)
    {
      previous = previous->pNext_;
    }
    ListIterator<T> *newListIterator = new ListIterator<T>(data, previous->pNext_);
    previous->pNext_ = newListIterator;
    size_++;
  }
}

template <typename T>
void mihalchenko::List<T>::removeAt(size_t index)
{
  if (index == 0)
  {
    pop_front();
  }
  else
  {
    ListIterator<T> *previous = this->begin_;
    for (size_t i = 0; i < index - 1; i++)
    {
      previous = previous->pNext_;
    }
    ListIterator<T> *toDelete = previous->pNext;
    previous->pNext_ = previous->pNext;
    delete toDelete;
    size_--;
  }
}

template <typename T>
T &mihalchenko::List<T>::operator[](const int index)
{
  size_t c = 0;
  ListIterator<T> *actual = this->begin;
  while (actual != nullptr)
  {
    if (c == index)
    {
      return actual->data_;
    }
    actual = actual->pNext_;
    c++;
  }
}

template <typename T>
void mihalchenko::List<T>::clear()
{
  while (size_)
  {
    pop_front();
  }
}

template <typename T>
template <typename U>
U &mihalchenko::List<T>::ListIterator<U>::operator++()
{
  node_ = node_->pNext;
  return this;
}

template <typename T>
template <typename U>
U mihalchenko::List<T>::ListIterator<U>::operator++(int)
{
  U result(*U);
  ++(*U);
  return result;
}

template <typename T>
template <typename U>
U &mihalchenko::List<T>::ListIterator<U>::operator*()
{
  return node_->data;
}

template <typename T>
template <typename U>
U *mihalchenko::List<T>::ListIterator<U>::operator->()
{
  return std::addressof(node_->data);
}

template <typename T>
template <typename U>
bool mihalchenko::List<T>::ListIterator<U>::operator==(const U &rhs) const
{
  return node_ == rhs.node;
}

template <typename T>
template <typename U>
bool mihalchenko::List<T>::ListIterator<U>::operator!=(const U &rhs) const
{
  return !(rhs == *U);
}

#endif
