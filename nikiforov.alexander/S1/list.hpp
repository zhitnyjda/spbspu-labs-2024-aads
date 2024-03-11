#ifndef LIST_HPP
#define LIST_HPP
#include "iterator.hpp"
#include <stdexcept>
#include <initializer_list>
#include <cstddef>

namespace nikiforov
{
  template <typename T>
  class List
  {
  public:
    List();
    List(size_t count, const T& value);
    List(Iterator< T > begin, Iterator< T > end, int value);
    List(const List& other);
    ~List();

    T& front();
    T& back();

    void assign(size_t count, const T& value);
    void assign(Iterator< T > first, Iterator< T > last);
    void assign(std::initializer_list<T> ilist);

    bool is_empty();
    size_t size();

    void push_front(T data);
    void push_back(T data);
    void pop_front();
    void pop_back();
    void swap(List< T >& other);
    void clear();

    void remove(T value);

    Iterator< T > begin();
    Iterator< T > end();

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
nikiforov::List<T>::List(size_t count, const T& value)
{
  for (size_t i = 0; i < count; i++)
  {
    push_back(value);
  }
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
nikiforov::List<T>::List(const nikiforov::List<T>& other)
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
T& nikiforov::List<T>::front()
{
  if (is_empty())
  {
    throw std::logic_error("Empty list!");
  }
  return head->data;
}

template<typename T>
T& nikiforov::List<T>::back()
{
  if (is_empty())
  {
    throw std::logic_error("Empty list!");
  }
  Node<T>* actual = head;
  for (size_t i = 0; i < (size_l - 1); i++)
  {
    actual = actual->pNext;
  }
  return actual->data;
}

template<typename T>
void nikiforov::List<T>::assign(size_t count, const T& value)
{
  clear();
  for (size_t i = 0; i < count; i++)
  {
    push_back(value);
  }
}

template<typename T>
void nikiforov::List<T>::assign(Iterator<T> first, Iterator<T> last)
{
  clear();
  while (first != last)
  {
    push_back(*first);
    first++;
  }
}

template<typename T>
void nikiforov::List<T>::assign(std::initializer_list<T> ilist)
{
  clear();
  for (const T* iter = ilist.begin(); iter != ilist.end(); ++iter)
  {
    push_back(*iter);
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
size_t nikiforov::List<T>::size()
{
  return size_l;
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
void nikiforov::List<T>::remove(T value)
{
  size_t size = size_l;
  size_t count = 0;
  Node<T>* actual = head;
  Node<T>* todel = head;
  Iterator<T> iter = begin();
  for (size_t i = 0; i < size; i++)
  {
    actual = head;
    todel = head;
    if (*iter == value)
    {
      if (iter == begin())
      {
        head = head->pNext;
        iter = begin();
        delete actual;
        size_l--;
        continue;
      }
      else
      {
        for (size_t i = 0; i < (count - 1); i++)
        {
          actual = actual->pNext;
        }
        todel = actual->pNext;
        actual->pNext = todel->pNext;
        iter++;
        delete todel;
        size_l--;
        continue;
      }
    }
    iter++;
    count++;
  }
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
#endif
