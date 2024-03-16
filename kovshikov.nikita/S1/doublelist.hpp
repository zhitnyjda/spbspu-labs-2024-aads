#ifndef DOUBLELIST_HPP
#define DOUBLELIST_HPP
#include "node.hpp"
#include <cstddef>
#include <iostream> //brrr
//для копирующего перемещения
//#include <utility>

namespace kovshikov
{
  template <typename T>
  class DoubleList
  {
  public:
//сделать параматры по умолчанию и убрать первый конструктор??
    DoubleList(): head_(nullptr), tail_(nullptr) {};
    DoubleList(Node<T>* head, Node<T>* tail);
    DoubleList(const DoubleList& dl);
    DoubleList<T>& operator=(const DoubleList& dl);
    DoubleList<T>& operator=(DoubleList&& dl); //???
    DoubleList(DoubleList&& dl) = default; //???
    ~DoubleList(); //используется динамическая память, нужно прописать деструктор

    T& front() const;
    T& back() const;

    bool empty() const;

    void pushFront(const T &value);
    void pushBack(const T& value);
    void popFront();
    void popBack();
    void clear();
    void swap(DoubleList& dl);

  private:
    Node<T>* head_;
    Node<T>* tail_;
  };


  template<typename T>
  DoubleList<T>::DoubleList(Node<T>* head, Node<T>* tail):
  head_(head),
  tail_(tail)
  {};

  template <typename T>
  DoubleList<T>::~DoubleList()
  {
    clear();
  }

//смогу ли я обратиться к приватным полям в методе?
  template <typename T>
  DoubleList<T>::DoubleList(const DoubleList& dl)
  {
    this->head_ = dl.head_;
    this->tail_ = dl.tail_;
  }

  template <typename T>
  DoubleList<T>& DoubleList<T>::operator=(const DoubleList& dl)
  {
    DoubleList<T> newDl(dl);
    return newDl;
  }

//реализация конструктора перемещения
/*  template <typename T>
  DoubleList<T>::DoubleList(DoubleList&& dl)
  {
    this->head_ = dl.head_;
    this->tail_ = dl.tail_;
  }*/

//реализация оператора перемещения
/*  template<typename T>
  DoubleList<T>& DoubleList<T>::operator=(DoubleList&& dl)
  {

  }*/

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
    newNode->prev = tail_;
    tail_->next = newNode;
    tail_ = newNode;
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
      std::cout << "popFront" << "\n"; //brrr
    }
  }


  /*template< typename T >
  void DoubleList<T>::popFront()
  {
    if (head_ == tail_)
    {
      delete tail_;
      head_ = tail_ = nullptr;
    }
    if (head_ != nullptr)
    {
      Node<T>* node = head_;
      head_ = node->next;
      delete node;
    }
    std::cout << "popFront" << "\n";
  }*/

  /*template <typename T>
  void DoubleList<T>::popBack()
  {
    if(head_ == tail_)
    {
      delete tail_;
      head_ = tail_ = nullptr;
    }
    if(head_ != nullptr)
    {
      Node<T>* node = tail_;
      tail_ = node->prev;
      delete node;
    }
    std::cout << "popBack" << "\n";
  }*/

  template <typename T>
  void DoubleList<T>::popBack()
  {
   // std::cout << "qwerty"; // brrr
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
      std::cout << "popBack" << "\n"; //brrr
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


//а получится ли обратится к приватному полю в методе?
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



}

#endif

