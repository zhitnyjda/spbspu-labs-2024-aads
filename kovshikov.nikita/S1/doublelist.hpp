#ifndef DOUBLELIST_HPP
#define DOUBLELIST_HPP
#include "node.hpp"
#include <cstddef>
//#include <iostream> //brrr
#include <utility>
#include "iterator.hpp"

namespace kovshikov
{
  template <typename T>
  class DoubleList
  {
  public:
    DoubleList(): head_(nullptr), tail_(nullptr) {};
    DoubleList(size_t size, const T &value);
    DoubleList(const DoubleList& dl);
    DoubleList(DoubleList&& dl); //???
    ~DoubleList();

    DoubleList<T>& operator=(const DoubleList<T>& dl);
    DoubleList<T>& operator=(DoubleList&& dl); //???

    T& front() const;
    T& back() const;

    bool empty() const;

    void pushFront(const T &value);
    void pushBack(const T& value);
    void popFront();
    void popBack();
    void clear();
    void swap(DoubleList& dl);
    void remove(const T &value);
    template<class Predicate>
    void remove_if(Predicate pred);
    void assign(size_t size, const T &value);

    Iterator<T> begin() const;
    Iterator<T> end() const;
    Iterator<const T> cbegin() const;
    Iterator<const T> cend() const;

  private:
    Node<T>* head_;
    Node<T>* tail_;
  };

  template<typename T>
  DoubleList<T>::DoubleList(size_t size, const T &value)
  {
    head_ = nullptr;
    tail_ = nullptr;
    for(size_t i = 0; i < size; i++)
    {
      this->pushBack(value);
    }
  }

  template <typename T>
  DoubleList<T>::~DoubleList()
  {
    clear();
  }

  template <typename T>
  DoubleList<T>::DoubleList(const DoubleList& dl)
  {
    this->head_ = nullptr;
    this->tail_ = nullptr;
    Node<T> *temp = dl.head_;
    while(temp != nullptr)
    {
      this->pushBack(temp->data);
      temp = temp->next;
    }
  }

  template <typename T>
  DoubleList<T>& DoubleList<T>::operator=(const DoubleList& dl)
  {
    DoubleList<T> newDl(dl);
    this->swap(newDl);
    return *this;
  }

  template <typename T>
  DoubleList<T>::DoubleList(DoubleList&& dl)
  {
    this->head_ = nullptr;
    this->tail_ = nullptr;
    Node<T> *temp = std::move(dl.head_);
    while(temp != nullptr)
    {
      this->pushBack(std::move(temp->data));
      temp = temp->next;
    }
  }


  template<typename T>
  DoubleList<T>& DoubleList<T>::operator=(DoubleList&& dl)
  {
    this->clear();
    Node<T> *temp = std::move(dl.head_);
    while(temp != nullptr)
    {
      this->pushBack(std::move(temp->data));
      temp = temp->next;
    }
    return *this;
  }

  template <typename T>
  T& DoubleList<T>::front() const
  {
    return head_->data;
  }

  template <typename T>
  T& DoubleList<T>::back() const
  {
    return tail_->data;
  }

  template <typename T>
  bool DoubleList<T>::empty() const
  {
    if (head_ == nullptr && tail_ == nullptr)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  template <typename T>
  void DoubleList<T>::pushFront(const T &value)
  {
    Node<T>* newNode = new Node<T>(value); // генерация исключения?
    if (this->empty() == true)
    {
      head_ = newNode;
      tail_ = newNode;
    }
    else
    {
      newNode->next = head_;
      head_->prev = newNode;
      head_ = newNode;
    }
  }

  template <typename T>
  void DoubleList<T>::pushBack(const T& value)
  {
    Node<T>* newNode = new Node<T>(value); //генерация исключения??
    if (this->empty() == true)
    {
      head_ = newNode;
      tail_ = newNode;
    }
    else
    {
      newNode->prev = tail_;
      tail_->next = newNode;
      tail_ = newNode;
    }
  }

  template <typename T>
  void DoubleList<T>::popFront()
  {
    if(head_ != nullptr && tail_ != nullptr)
    {
      Node<T>* temp = head_->next;
      delete head_;
      head_ = temp;
      if(head_ == nullptr)
      {
        tail_ = nullptr;
      }
      else
      {
        head_->prev = nullptr;
      }
     // std::cout << "popFront\n"; //brrrr
    }
  }

  template <typename T>
  void DoubleList<T>::popBack()
  {
    if(head_ != nullptr && tail_ != nullptr)
    {
      Node<T>* temp = tail_->prev;
      delete tail_;
      tail_ = temp;
      if(tail_ == nullptr)
      {
        head_ = nullptr;
      }
      else
      {
        tail_->next = nullptr;
      }
    //  std::cout << "popBack\n"; //brrr
    }
  }

  template <typename T>
  void DoubleList<T>::clear()
  {
    while (head_ && tail_)
    {
      popFront();
    }
  }

  template <typename T>
  void DoubleList<T>::swap(DoubleList& dl)
  {
    Node<T>* tempHead = dl.head_;
    Node<T>* tempTail = dl.tail_;
    dl.head_ = this->head_;
    this->head_ = tempHead;
    dl.tail_ = this->tail_;
    this->tail_ = tempTail;
  }

  template<typename T>
  void DoubleList<T>::remove(const T &value)
  {
    Iterator<T> iterator = this->begin();
    while(iterator != this->end())
    {
      if(iterator.node->data == value)
      {
        Node<T>* tempPrev = iterator.node->prev;
        Node<T>* tempNext = iterator.node->next;
        Iterator<T> iteratorToDelete = iterator;
        if(head_ == tail_)
        {
          head_ = tail_ = nullptr;
        }
        else if(iterator.node == head_)
        {
          head_ = tempNext;
          tempNext->prev = nullptr;
        }
        else
        {
          tempPrev->next = tempNext;
          tempNext->prev = tempPrev;
        }
        delete iteratorToDelete.node;
      }
      iterator++;
     }
  }

  template<typename T>
  template<class Predicate>
  void DoubleList<T>::remove_if(Predicate pred)
  {
    Iterator<T> iterator = this->begin();
    while(iterator != this->end())
    {
      if(pred(iterator.node->data))
      {
        Node<T>* tempPrev = iterator.node->prev;
        Node<T>* tempNext = iterator.node->next;
        Iterator<T> iteratorToDelete = iterator;
        if(head_ == tail_)
        {
          head_ = tail_ = nullptr;
        }
        else if(iterator.node == head_)
        {
          head_ = tempNext;
          tempNext->prev = nullptr;
        }
        else
        {
          tempPrev->next = tempNext;
          tempNext->prev = tempPrev;
        }
        delete iteratorToDelete.node;
      }
      iterator++;
     }
  }

  template<typename T>
  void DoubleList<T>::assign(size_t size, const T &value)
  {
    this->clear();
    for(size_t i = 0; i < size; i++)
    {
      this->pushBack(value);
    }
  }

  template<typename T>
  Iterator<T> DoubleList<T>::begin() const
  {
    return Iterator<T>(head_);
  }

  template<typename T>
  Iterator<T> DoubleList<T>::end() const
  {
    if(this->empty())
    {
      return this->begin();
    }
    else
    {
      Node<T>* pastTheEnd = tail_->next;
      return Iterator<T>(pastTheEnd);
    }
  }

  template<typename T>
  Iterator<const T> DoubleList<T>::cbegin() const
  {
    return Iterator<const T>(head_);
  }

  template<typename T>
  Iterator<const T> DoubleList<T>::cend() const
  {
    if(this->empty)
    {
      return this->cbegin();
    }
    else
    {
      Node<T>* pastTheEnd = tail_->next;
      return Iterator<const T>(pastTheEnd);
    }
  }
}

#endif
