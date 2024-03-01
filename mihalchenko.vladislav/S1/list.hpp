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
    void push_front(T data);
    void push_back(T data);
    void pop_front();
    void pop_back();
    void insert(T value, size_t i);
    void removeAt(size_t i);
    T &operator[](const int i);
    void clear();
    size_t getSize() { return size_; };

    /*Iterator<T> begin() const
    {
      return Iterator(begin_);
    }
    Iterator<T> end() const
    {
      return Iterator(nullptr);
    }*/

  private:
    template <typename U>
    class Iterator
    {
    public:
      U &operator=(const U &);
      U &operator++();
      U operator++(int);
      U &operator*();
      U *operator->();

      bool operator==(const U &) const;
      bool operator!=(const U &) const;

      Iterator getPointerNext() { return pNext_; };

      U getSize() { return data_; };

      // private:
      Iterator(U data = U(), Iterator *pNext = nullptr)
      {
        data_ = data;
        pNext_ = pNext;
      }

      Iterator *pNext_;
      U data_;
    };

    Iterator<T> *begin_;
    // ListIterator<T> *end_;
    size_t size_;
  };

  template <typename T>
  mihalchenko::List<T>::List()
  {
    size_ = 0;
    begin_ = nullptr;
  }

  template <typename T>
  List<T>::~List()
  {
    clear();
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
    removeAt(size_ - 1);
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
  void mihalchenko::List<T>::removeAt(size_t index)
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
  T &mihalchenko::List<T>::operator[](const int index)
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
  }

  template <typename T>
  void mihalchenko::List<T>::clear()
  {
    while (size_)
    {
      pop_front();
    }
  }

  /*template <typename T>
  mihalchenko::List<T>::Iterator<T> mihalchenko::List<T>::begin() const
  {
    return Iterator(begin_);
  }

  template <typename T>
  mihalchenko::List<T>::Iterator<T> mihalchenko::List<T>::end() const
  {
    return Iterator(nullptr);
  }*/

  template <typename T>
  template <typename U>
  U &mihalchenko::List<T>::Iterator<U>::operator++()
  {
    begin_ = begin_->pNext;
    return this;
  }

  template <typename T>
  template <typename U>
  U mihalchenko::List<T>::Iterator<U>::operator++(int)
  {
    U result(*this);
    ++(*this);
    return result;
  }

  template <typename T>
  template <typename U>
  U &mihalchenko::List<T>::Iterator<U>::operator*()
  {
    return begin_->data_;
  }

  template <typename T>
  template <typename U>
  U *mihalchenko::List<T>::Iterator<U>::operator->()
  {
    return std::addressof(begin_->data_);
  }

  template <typename T>
  template <typename U>
  bool mihalchenko::List<T>::Iterator<U>::operator==(const U &rhs) const
  {
    return begin_ == rhs.begin_;
  }

  template <typename T>
  template <typename U>
  bool mihalchenko::List<T>::Iterator<U>::operator!=(const U &rhs) const
  {
    return !(rhs == *this);
  }
}

#endif
