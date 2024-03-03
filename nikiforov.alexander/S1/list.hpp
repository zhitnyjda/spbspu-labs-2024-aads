#ifndef LIST_HPP
#define LIST_HPP
#include "node.hpp"
#include "iterator.hpp"
#include <cstddef>

namespace nikiforov
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
    void clear();
    bool is_empty();

    Iterator<T> begin() const;
    Iterator<T> end() const;
    size_t size() const;

  private:

    Node<T>* head;
    size_t size_l;
  };


  template<typename T>
  nikiforov::List<T>::List()
  {
    head = nullptr;
    size_l = 0;
  }

  template<typename T>
  nikiforov::List<T>::~List()
  {
    clear();
  }

  template<typename T>
  void nikiforov::List<T>::push_front(T data)
  {
    Node<T>* nd = new Node<T>(data);
    if (head == nullptr)
    {
      head = nd;
    }
    else
    {
      Node<T>* actual = head;
      nd->pNext = actual;
      head = nd;
    }
    size_l++;
  }

  template<typename T>
  void nikiforov::List<T>::push_back(T data)
  {
    Node<T>* nd = new Node<T>(data);
    if (head == nullptr)
    {
      head = nd;
    }
    else
    {
      Node<T>* actual = head;
      while (actual->pNext != nullptr)
      {
        actual = actual->pNext;
      }
      actual->pNext = nd;
    }
    size_l++;
  }

  template<typename T>
  void nikiforov::List<T>::pop_front()
  {
    Node<T>* actual = head;
    head = head->pNext;
    delete actual;
    size_l--;
  }

  template<typename T>
  void nikiforov::List<T>::pop_back()
  {
    Node<T>* actual = head;
    for (size_t i = 0; i < (size_l - 1); i++)
    {
      actual = actual->pNext;
    }
    delete actual;
    size_l--;
  }

  template<typename T>
  void nikiforov::List<T>::clear()
  {
    size_t size = size_l;
    for (size_t i = 0; i < size; i++)
    {
      pop_front();
    }
  }

  template<typename T>
  bool nikiforov::List<T>::is_empty()
  {
    if (head == nullptr)
    {
      return true;
    }
    return false;
  }


  template<typename T>
  Iterator<T> nikiforov::List<T>::begin() const
  {
    return Iterator<T>(head);
  }

  template<typename T>
  Iterator<T> nikiforov::List<T>::end() const
  {
    return Iterator<T>(nullptr);
  }

  template<typename T>
  size_t nikiforov::List<T>::size() const
  {
    return size_l;
  }
}

#endif
