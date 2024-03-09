#ifndef LIST_HPP
#define LIST_HPP
#include "iterator.hpp"
#include <cstddef>

namespace nikiforov
{
  template <typename T>
  class List
  {
  public:
    List();
    List(Iterator< T > begin, Iterator< T > end, int value);
    List(const List& other);
    ~List();

    void push_front(T data);
    void push_back(T data);
    void pop_front();
    void pop_back();
    void swap(List< T >& other);
    void clear();
    bool is_empty();

    Iterator< T > begin();
    Iterator< T > end();
    size_t size();

  private:

    Node<T>* head;
    size_t size_l;
  };
}

template<typename T>
nikiforov::List<T>::List()
{
  head = nullptr;
  size_l = 0;
}

template<typename T>
nikiforov::List<T>::List(Iterator<T> begin, Iterator<T> end, int value)
{
  for (begin; begin != end; ++begin)
  {
    push_back(value);
  }
}

template<typename T>
nikiforov::List<T>::List(const List& other)
{
  if (other.head == nullptr)
  {
    head = nullptr;
  }
  else
  {
    head = new Node<T>(*other.head);
  }
  size_l = other.size_l;
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
void nikiforov::List<T>::swap(List<T>& other)
{
  Node<T>* short_termH = this->head;
  head = other.head;
  other.head = short_termH;

  size_t short_termS = this->size_l;
  size_l = other.size_l;
  other.size_l = short_termS;
}

template<typename T>
void nikiforov::List<T>::clear()
{
  const size_t size = size_l;
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
nikiforov::Iterator<T> nikiforov::List<T>::begin()
{
  return Iterator<T>(head);
}

template<typename T>
nikiforov::Iterator<T> nikiforov::List<T>::end()
{
  return Iterator<T>(nullptr);
}

template<typename T>
size_t nikiforov::List<T>::size()
{
  return size_l;
}
#endif
