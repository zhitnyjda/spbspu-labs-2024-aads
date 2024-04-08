#ifndef LIST_HPP
#define LIST_HPP
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
    List(const List &copy);
    List<T> &operator=(const List &copy);
    List(List &&move);
    List<T> &operator=(List &&move);

    void swap(List<T> &other);

    void push_front(T data);
    void push_back(T data);
    void pop_front();
    void pop_back();
    void insert(T value, size_t i);
    void erase(size_t i);
    T &operator[](const size_t i);
    void clear();
    bool empty();

    size_t getSize() { return size_; };

    // class Iterator;

    // List(const List<T> &) = default;
    // List<T> &operator=(const List<T> &);

    // private:

    template <typename U>
    class ConstIterator
    {
    public:
      ConstIterator(T data = T(), ConstIterator<T> *pNext = nullptr)
      {
        data_ = data;
        pNext_ = pNext;
      }
      ~ConstIterator() = default;

      ConstIterator<T> &operator++();
      ConstIterator<T> operator++(int);

      const T &operator*() const;
      const T *operator->() const;

      bool operator!=(const ConstIterator<T> &rhs) const;
      bool operator==(const ConstIterator<T> &rhs) const;

      // ConstIterator<T> &operator=(const ConstIterator<T> &other) = default;

      ConstIterator<T> *pNext_;
      T data_;
    };

    template <typename U>
    class Iterator
    {
    public:
      Iterator(T data = T(), Iterator<T> *pNext = nullptr)
      {
        data_ = data;
        pNext_ = pNext;
      }

      ~Iterator() = default;

      Iterator<T> &operator++();
      Iterator<T> operator++(int);

      T &operator*();
      T *operator->();

      bool operator==(const Iterator<T> &rhs) const;
      bool operator!=(const Iterator<T> &rhs) const;

      List<T> &operator+(size_t num);
      // Iterator<T> &operator=(const Iterator<T> &) = default;

      Iterator<T> getPointerNext() { return pNext_; };

      // private:

      Iterator<T> *pNext_;
      T data_;
    };

  public:
    ConstIterator<T> cbegin() const noexcept;
    ConstIterator<T> cend() const noexcept;
    Iterator<T> begin() noexcept;
    Iterator<T> end() noexcept;

    // private:
    Iterator<T> *begin_;
    Iterator<T> *end_;

    size_t size_;
  };
}

template <typename T>
template <typename U>
mihalchenko::List<T>::ConstIterator<T> &mihalchenko::List<T>::ConstIterator<U>::operator++()
{
  begin_ = begin_->pNext_;
  return *this;
}

template <typename T>
template <typename U>
mihalchenko::List<T>::ConstIterator<T> mihalchenko::List<T>::ConstIterator<U>::operator++(int)
{
  ConstIterator<T> result(*this);
  ++(*this);
  return result;
}

template <typename T>
template <typename U>
const T &mihalchenko::List<T>::ConstIterator<U>::operator*() const
{
  return begin_->data_;
}

template <typename T>
template <typename U>
const T *mihalchenko::List<T>::ConstIterator<U>::operator->() const
{
  return std::addressof(begin_->data_);
}

template <typename T>
template <typename U>
bool mihalchenko::List<T>::ConstIterator<U>::operator==(const ConstIterator<T> &rhs) const
{
  return begin_ == rhs.begin_;
}

template <typename T>
template <typename U>
bool mihalchenko::List<T>::ConstIterator<U>::operator!=(const ConstIterator<T> &rhs) const
{
  return !(rhs == *this);
}

template <typename T>
template <typename U>
mihalchenko::List<T>::Iterator<T> &mihalchenko::List<T>::Iterator<U>::operator++()
{
  begin_ = begin_->pNext_;
  return *this;
}

template <typename T>
template <typename U>
mihalchenko::List<T>::Iterator<T> mihalchenko::List<T>::Iterator<U>::operator++(int)
{
  Iterator<T> result(*this);
  ++(*this);
  return result;
}

template <typename T>
template <typename U>
T &mihalchenko::List<T>::Iterator<U>::operator*()
{
  return begin_->data_;
}

template <typename T>
template <typename U>
T *mihalchenko::List<T>::Iterator<U>::operator->()
{
  return std::addressof(begin_->data_);
}

template <typename T>
template <typename U>
bool mihalchenko::List<T>::Iterator<U>::operator==(const Iterator<T> &rhs) const
{
  return begin_ == rhs.begin_;
}

template <typename T>
template <typename U>
bool mihalchenko::List<T>::Iterator<U>::operator!=(const Iterator<T> &rhs) const
{
  return !(rhs == *this);
}

template <typename T>
template <typename U>
mihalchenko::List<T> &mihalchenko::List<T>::Iterator<U>::operator+(size_t num)
{
  for (size_t i = 0; i < num; i++)
  {
    (*this)++;
  }
  return *this;
}

template <typename T>
mihalchenko::List<T>::ConstIterator<T> mihalchenko::List<T>::cbegin() const noexcept
{
  return begin_;
}

template <typename T>
mihalchenko::List<T>::ConstIterator<T> mihalchenko::List<T>::cend() const noexcept
{
  while (begin_->pNext_ != nullptr)
  {
    end_ = begin_->pNext_;
  }
  return end_;
}

template <typename T>
mihalchenko::List<T>::Iterator<T> mihalchenko::List<T>::begin() noexcept
{
  return begin_;
}

template <typename T>
mihalchenko::List<T>::Iterator<T> mihalchenko::List<T>::end() noexcept
{
  while (begin_->pNext_ != nullptr)
  {
    end_ = begin_->pNext_;
  }
  return end_;
}

template <typename T>
mihalchenko::List<T>::List()
{
  size_ = 0;
  begin_ = nullptr;
}

template <typename T>
mihalchenko::List<T>::~List()
{
  clear();
}

template <typename T>
mihalchenko::List<T>::List(const List<T> &copy)
{
  if (copy.begin_ == nullptr)
  {
    this->begin_ = nullptr;
  }
  else
  {
    this->begin_ = new Iterator<T>(*copy.begin_);
  }
  /*if (copy.end_ == nullptr)
  {
    this->end_ = nullptr;
  }
  else
  {
    this->end_ = new Iterator<T>(*copy.end_);
  }*/
  this->size_ = copy.size_;
}

template <typename T>
mihalchenko::List<T> &mihalchenko::List<T>::operator=(const List<T> &copy)
{
  if (this == &copy)
  {
    return *this;
  }
  this->size_ = copy.size_;
  clear();
  Iterator<T> *pointer = copy.begin_;
  while (pointer)
  {
    this->push_back(pointer->data_);
    pointer = pointer->pNext_;
  }
  return *this;
}

template <typename T>
mihalchenko::List<T>::List(List<T> &&move)
{
  this->begin_ = move.begin_;
  move.begin_ = nullptr;
  this->end_ = move.begin_;
  move.end_ = nullptr;
  this->size_ = move.size_;
  move.size_ = 0;
}

template <typename T>
mihalchenko::List<T> &mihalchenko::List<T>::operator=(List<T> &&move)
{
  if (this == &move)
  {
    move.clear();
    return *this;
  }
  clear();
  mihalchenko::List<T> temp = std::move(move);
  swap(temp);
  move.clear();
  return *this;
}

template <typename T>
void mihalchenko::List<T>::swap(List<T> &other)
{
  while (other.begin_)
  {
    push_back(other.begin_->data_);
    other.begin_ = other.begin_->pNext_;
  }
  /*mihalchenko::List<T> *tempPointerBegin = this->begin_;
  this->begin_ = other.begin_;
  other.begin_ = tempPointerBegin;
  mihalchenko::List<T> *tempPointerEnd = this->end_;
  this->end_ = other.end_;
  other.end_ = tempPointerEnd;*/

  size_t tempSize = this->size_;
  this->size_ = other.size_;
  other.size_ = tempSize;
}

template <typename T>
void mihalchenko::List<T>::push_front(T data)
{
  begin_ = new Iterator<T>(data, begin_);
  size_++;
}

template <typename T>
void mihalchenko::List<T>::push_back(T data)
{
  if (begin_ == nullptr)
  {
    begin_ = new Iterator<T>(data);
  }
  else
  {
    Iterator<T> *actual = this->begin_;
    while (actual->pNext_ != nullptr)
    {
      actual = actual->pNext_;
    }
    actual->pNext_ = new Iterator<T>(data);
  }
  size_++;
}

template <typename T>
void mihalchenko::List<T>::pop_front()
{
  Iterator<T> *temp = begin_;
  begin_ = begin_->pNext_;
  delete temp;
  size_--;
}

template <typename T>
void mihalchenko::List<T>::pop_back()
{
  erase(size_ - 1);
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
    Iterator<T> *previous = this->begin_;
    for (size_t i = 0; i < index - 1; i++)
    {
      previous = previous->pNext_;
    }
    Iterator<T> *newIterator = new Iterator<T>(data, previous->pNext_);
    previous->pNext_ = newIterator;
    size_++;
  }
}

template <typename T>
void mihalchenko::List<T>::erase(size_t index)
{
  if (index == 0)
  {
    pop_front();
  }
  else
  {
    Iterator<T> *previous = this->begin_;
    for (size_t i = 0; i < index - 1; i++)
    {
      previous = previous->pNext_;
    }
    Iterator<T> *toDelete = previous->pNext_;
    previous->pNext_ = previous->pNext_;
    delete toDelete;
    size_--;
  }
}

template <typename T>
T &mihalchenko::List<T>::operator[](const size_t index)
{
  size_t c = 0;
  Iterator<T> *actual = this->begin_;
  while (actual != nullptr)
  {
    if (c == index)
    {
      return actual->data_;
    }
    actual = actual->pNext_;
    c++;
  }
  throw std::out_of_range("Index out of range");
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
bool mihalchenko::List<T>::empty()
{
  return (this->begin_ == nullptr);
}

#endif
