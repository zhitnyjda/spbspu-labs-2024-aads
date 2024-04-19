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
    explicit List(size_t count);
    List(size_t count, const T &value);
    List(std::initializer_list< T > ilist);
    List(const List &copy);
    List<T> &operator=(const List &copy);
    List(List &&move);
    List<T> &operator=(List &&move);
    ~List();

    void swap(List<T> &other);

    void push_front(T data);
    void push_back(T data);
    void pop_front();
    void pop_back();
    void insert(T value, size_t ind);
    void erase(size_t i);
    T &operator[](const size_t ind);
    void clear();
    bool empty();

    T &front();

    size_t getSize() { return size_; };

    template <typename U>
    class ConstIterator : public std::iterator<std::forward_iterator_tag, T>
    {
    public:
      friend class List<T>;
      ConstIterator();
      ConstIterator(Node *ind);
      ConstIterator(const ConstIterator<T> &) = default;

      ~ConstIterator() = default;

      ConstIterator<T> &operator++();
      ConstIterator<T> operator++(int);
      const T &operator*() const;
      const T *operator->() const;
      bool operator!=(const ConstIterator<T> &rhs) const;
      bool operator==(const ConstIterator<T> &rhs) const;

    private:
      Node *node_;
    };

    template <typename U>
    class Iterator : public std::iterator<std::forward_iterator_tag, T>
    {
    public:
      friend class List<T>;
      Iterator();
      Iterator(ConstIterator<T>);
      Iterator(const Iterator<T> &) = default;
      ~Iterator() = default;

      Iterator<T> &operator++();
      Iterator<T> operator++(int);
      T &operator*();
      T *operator->();
      bool operator==(const Iterator<T> &rhs) const;
      bool operator!=(const Iterator<T> &rhs) const;
      List<T> &operator+(size_t num);

    private:
      ConstIterator<T> constIter_;
    };

    void assign(size_t count, const T &value);
    void assign(Iterator<T> first, Iterator<T> last);
    void assign(std::initializer_list<T> ilist);

    ConstIterator<T> cbegin() const noexcept;
    ConstIterator<T> cend() const noexcept;
    Iterator<T> begin() noexcept;
    Iterator<T> end() noexcept;

    void erase_after(Iterator<T> iterator);

    void remove(const T &iterValue);
    template <typename F>
    void remove_if(F functor);

  private:
    Node *begin_;
    size_t size_;
    struct Node
    {
      T data_;
      Node *pNext_;
      Node(T value) : data_(value), pNext_(nullptr) {}
    };
  };
}

template <typename T>
template <typename U>
mihalchenko::List<T>::ConstIterator<U>::ConstIterator() : node_(nullptr)
{
}

template <typename T>
template <typename U>
mihalchenko::List<T>::ConstIterator<U>::ConstIterator(Node *node) : node_(node)
{
}

template <typename T>
template <typename U>
mihalchenko::List<T>::ConstIterator<T> &mihalchenko::List<T>::ConstIterator<U>::operator++()
{
  node_ = node_->pNext_;
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
  return node_->data_;
}

template <typename T>
template <typename U>
const T *mihalchenko::List<T>::ConstIterator<U>::operator->() const
{
  return std::addressof(node_->data_);
}

template <typename T>
template <typename U>
bool mihalchenko::List<T>::ConstIterator<U>::operator==(const ConstIterator<T> &rhs) const
{
  return node_ == rhs.node_;
}

template <typename T>
template <typename U>
bool mihalchenko::List<T>::ConstIterator<U>::operator!=(const ConstIterator<T> &rhs) const
{
  return !(rhs == *this);
}

template <typename T>
template <typename U>
mihalchenko::List<T>::Iterator<U>::Iterator() : constIter_(nullptr)
{
}

template <typename T>
template <typename U>
mihalchenko::List<T>::Iterator<U>::Iterator(ConstIterator<T> value) : constIter_(value)
{
}

template <typename T>
template <typename U>
mihalchenko::List<T>::Iterator<T> &mihalchenko::List<T>::Iterator<U>::operator++()
{
  ++constIter_;
  return *this;
}

template <typename T>
template <typename U>
mihalchenko::List<T>::Iterator<T> mihalchenko::List<T>::Iterator<U>::operator++(int)
{
  constIter_++;
  return *this;
}

template <typename T>
template <typename U>
T &mihalchenko::List<T>::Iterator<U>::operator*()
{
  return constIter_.node_->data_;
}

template <typename T>
template <typename U>
T *mihalchenko::List<T>::Iterator<U>::operator->()
{
  return std::addressof(constIter_.node_->data_);
}

template <typename T>
template <typename U>
bool mihalchenko::List<T>::Iterator<U>::operator==(const Iterator<T> &rhs) const
{
  return constIter_ == rhs.constIter_;
}

template <typename T>
template <typename U>
bool mihalchenko::List<T>::Iterator<U>::operator!=(const Iterator<T> &rhs) const
{
  return !(rhs.constIter_ == constIter_);
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
  return ConstIterator(begin_);
}

template <typename T>
mihalchenko::List<T>::ConstIterator<T> mihalchenko::List<T>::cend() const noexcept
{
  /*while (begin_->pNext_ != nullptr)
  {
    end_ = begin_->pNext_;
  }
  return end_;*/
  return ConstIterator(nullptr);
}

template <typename T>
mihalchenko::List<T>::Iterator<T> mihalchenko::List<T>::begin() noexcept
{
  return Iterator(begin_);
}

template <typename T>
mihalchenko::List<T>::Iterator<T> mihalchenko::List<T>::end() noexcept
{
  /*while (begin_->pNext_ != nullptr)
  {
    end_ = begin_->pNext_;
  }
  return end_;*/
  return Iterator(nullptr);
}

template <typename T>
mihalchenko::List<T>::List()
{
  size_(0);
  begin_(nullptr);
}

template< typename T >
mihalchenko::List< T >::List(size_t num)
{
  for (size_t i = 0; i < num; i++)
  {
    push_back(num);
  }
}

template< typename T >
mihalchenko::List< T >::List(size_t num, const T& value) :
  head_(nullptr)
{
  for (size_t i = 0; i < num; i++)
  {
    push_back(value);
  }
}

template< typename T >
mihalchenko::List< T >::List(std::initializer_list< T > init_list)
{
  assign(init_list);
}

template <typename T>
mihalchenko::List<T>::List(const List<T> &copy)
{
  if (copy.begin_ == nullptr)
  {
    begin_ = nullptr;
  }
  else
  {
    begin_ = new Node(*copy.begin_);
  }
  size_ = copy.size_;
}

template <typename T>
mihalchenko::List<T> &mihalchenko::List<T>::operator=(const List &copy)
{
  if (this == &copy)
  {
    return *this;
  }
  size_ = copy.size_;
  clear();
  Node *pointer = copy.begin_;
  while (pointer)
  {
    push_back(pointer->data_);
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
mihalchenko::List<T> &mihalchenko::List<T>::operator=(List &&move)
{
  if (this == &move)
  {
    move.clear();
    return *this;
  }
  clear();
  List<T> temp = std::move(move);
  swap(temp);
  move.clear();
  return *this;
}

template <typename T>
mihalchenko::List<T>::~List()
{
  clear();
}

template <typename T>
void mihalchenko::List<T>::swap(List<T> &other)
{
  /*while (other.begin_)
  {
    push_back(other.begin_->data_);
    other.begin_ = other.begin_->pNext_;
  }*/
  Node * temp = begin_;
  begin_ = other.begin_;
  other.begin_ = temp;
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
  begin_ = new Node(data, begin_);
  size_++;
}

template <typename T>
void mihalchenko::List<T>::push_back(T data)
{
  if (begin_ == nullptr)
  {
    begin_ = new Node(data);
  }
  else
  {
    Node *actual = begin_;
    while (actual->pNext_ != nullptr)
    {
      actual = actual->pNext_;
    }
    actual->pNext_ = new Node(data);
  }
  size_++;
}

template <typename T>
void mihalchenko::List<T>::pop_front()
{
  Node *temp = begin_;
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
    Node *pointer = begin_;
    for (size_t i = 0; i < index - 1; i++)
    {
      pointer = pointer->pNext_;
    }
    Node *delPointer = pointer->pNext_;
    pointer->pNext_ = delPointer->pNext_;
    delete delPointer;
    size_--;
  }
}

template <typename T>
T &mihalchenko::List<T>::operator[](const size_t index)
{
  size_t c = 0;
  Node *actual = begin_;
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
  return (begin_ == nullptr);
}

template <typename T>
T &mihalchenko::List<T>::front()
{
  if (empty())
  {
    throw std::logic_error("List is empty!");
  }
  return begin_->data_;
}

template <typename T>
void mihalchenko::List<T>::assign(size_t count, const T &value)
{
  clear();
  for (size_t i = 0; i < count; i++)
  {
    push_back(value);
  }
}

template <typename T>
void mihalchenko::List<T>::assign(Iterator<T> first, Iterator<T> last)
{
  clear();
  while (first != last)
  {
    push_back(*first);
    first++;
  }
}

template <typename T>
void mihalchenko::List<T>::assign(std::initializer_list<T> i_list)
{
  clear();
  for (auto iter = i_list.begin(); iter != i_list.end(); ++iter)
  {
    push_back(*iter);
  }
}

template <typename T>
void mihalchenko::List<T>::erase_after(Iterator<T> iterator)
{
  Node *valueBegin = iterator.data_;
  Node *valueDel = valueBegin->pNext_;
  valueBegin->pNext_ = valueDel->pNext_;
  delete valueDel;
  size--;
  iterator = begin_;
}

template <typename T>
void mihalchenko::List<T>::remove(const T &iterValue)
{
  for (Node iterator = begin(); iterator != end(); ++iterator)
  {
    if (iterator->pNext_ == iterValue && iterator->pNext_ != this->end_)
    {
      erase_after(iterator);
    }
    else if (*iterator == iterValue && *iterator == *begin_)
    {
      pop_front();
      iterator = begin_;
    }
  }
}

template <typename T>
template <typename F>
void mihalchenko::List<T>::remove_if(F functor)
{
  for (Node iterator = begin(); iterator != end(); ++iterator)
  {
    if (functor(*(iterator)))
    {
      remove(*iterator);
      iterator = begin_;
    }
  }
}

#endif
