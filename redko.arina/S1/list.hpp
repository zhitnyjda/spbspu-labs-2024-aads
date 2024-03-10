#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <stdexcept>
#include <memory>
#include <cassert>

namespace redko
{
  template< typename T >
  struct ListElem
  {
    ListElem();
    ListElem(T d);

    T data;
    ListElem< T > * next;
  };

  template< typename T >
  struct Iterator
  {
    ListElem< T > * node;

    using this_t = Iterator< T >;

    Iterator();
    ~Iterator() = default;
    Iterator(const this_t &) = default;
    Iterator(ListElem< T > * ptr);
    this_t& operator=(const this_t &) = default;

    this_t& operator++();
    this_t operator++(int);

    T& operator*();
    const T& operator*() const;
    T* operator->();
    const T* operator->() const;

    bool operator!=(const this_t &) const;
    bool operator==(const this_t &) const;
  };

  template< typename T >
  class List
  {
  public:
    using iterator = Iterator< T >;
    using const_iterator = Iterator< const T >;

    List(): head_() {};
    List(size_t count, const T & value);
    List(size_t count);
    List(iterator first, iterator last);
    List(const List & other);
    List(List< T > && other) noexcept;
    List(std::initializer_list< T > ilist);
    ~List();

    List< T > & operator=(const List< T > & other);
    List< T > & operator=(List< T > && other);

    void assign(size_t count, const T & value);
    void assign(iterator first, iterator last);
    void assign(std::initializer_list< T > ilist);

    T & front();

    iterator beforeBegin() noexcept;
    const_iterator beforeBegin() const noexcept;
    const_iterator cbeforeBegin() const noexcept;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    bool isEmpty();

    void clear();
    iterator insertAfter(iterator pos, const T & value);
    iterator insertAfter(iterator pos, T && value);
    Iterator< T > eraseAfter(Iterator< T > pos);
    void pushBack(const T & value);
    void pushBack(T && value);
    void popFront();
    void swap(List< T > & other);

    void spliceAfter(iterator pos, List< T > & other);
    void spliceAfter(iterator pos, List< T > && other);
    size_t remove(const T & value);
    template< typename UnaryPredicate >
    size_t removeIf(UnaryPredicate pred);
    void reverse() noexcept;
    size_t unique();
    void sort();

    bool operator==(const List< T > & rhs);
    bool operator!=(const List< T > & rhs);
    bool operator<(const List< T > & rhs);
    bool operator<=(const List< T > & rhs);
    bool operator>(const List< T > & rhs);
    bool operator>=(const List< T > & rhs);

  private:
    ListElem< T > head_;
  };
}

template < typename T >
redko::ListElem< T >::ListElem():
  data(),
  next(nullptr)
{}
template < typename T >
redko::ListElem< T >::ListElem(T d):
  data(d),
  next(nullptr)
{}

template < typename T >
redko::Iterator< T >::Iterator():
  node(nullptr)
{}
template < typename T >
redko::Iterator< T >::Iterator(ListElem< T > * ptr):
  node(ptr)
{}
template< typename T >
redko::Iterator< T > & redko::Iterator< T >::operator++()
{
  assert(node != nullptr);
  node = node->next;
  return *this;
}
template< typename T >
redko::Iterator< T > redko::Iterator< T >::operator++(int)
{
  assert(node != nullptr);
  this_t result(*this);
  ++(*this);
  return result;
}
template< typename T >
T & redko::Iterator< T >::operator*()
{
  assert(node != nullptr);
  return node->data;
}
template< typename T >
const T & redko::Iterator< T >::operator*() const
{
  assert(node != nullptr);
  return node->data;
}
template< typename T >
T * redko::Iterator< T >::operator->()
{
  assert(node != nullptr);
  return std::addressof(node->data);
}
template< typename T >
const T * redko::Iterator< T >::operator->() const
{
  assert(node != nullptr);
  return std::addressof(node->data);
}

template< typename T >
bool redko::Iterator< T >::operator==(const this_t & rhs) const
{
  return node == rhs.node;
}
template< typename T >
bool redko::Iterator< T >::operator!=(const this_t & rhs) const
{
  return !(rhs == *this);
}

template< typename T >
redko::List< T >::List(size_t count, const T & value)
{
  for (int i = 0; i < count; i++)
  {
    pushBack(value);
  }
}
template< typename T >
redko::List< T >::List(size_t count)
{
  if (count < 1)
  {
    throw std::logic_error("non-positive number");
  }
  head_.next = new ListElem< T >();
  ListElem< T > * curr = head_.next->next;
  for (int i = 1; i < count; i++)
  {
    curr = new ListElem< T >();
    curr = curr->next;
  }
}
template< typename T >
redko::List< T >::List(Iterator< T > first, Iterator< T > last)
{
  while (first != last)
  {
    pushBack(*first);
    first++;
  }
}
template< typename T >
redko::List< T >::List(const List & other)
{
  ListElem< T > * othrElem = other.head_.next;
  while (othrElem != nullptr)
  {
    pushBack(othrElem->data);
    othrElem = othrElem->next;
  }
}
template< typename T >
redko::List< T >::List(List< T > && other) noexcept
{
  head_.next = other.head_.next;
  other.head_.next = nullptr;
}
template< typename T >
redko::List< T >::~List()
{
  clear();
}
template< typename T >
redko::List< T >::List(std::initializer_list< T > ilist)
{
  for (auto value : ilist)
  {
    pushBack(value);
  }
}

template< typename T >
redko::List< T > & redko::List< T >::operator=(const redko::List< T > & other)
{
  if (&other != this)
  {
    clear();
    ListElem< T > * othrElem = other.head_.next;
    while (othrElem != nullptr)
    {
      pushBack(othrElem->data);
      othrElem = othrElem->next;
    }
  }
  return *this;
}
template< typename T >
redko::List< T > & redko::List< T >::operator=(redko::List< T > && other)
{
  if (&other != this)
  {
    clear();
    head_.next = other.head_.next;
    other.head_.next = nullptr;
  }
  return *this;
}

template< typename T >
void redko::List< T >::assign(size_t count, const T & value)
{
  clear();
  for (int i = 0; i < count; i++)
  {
    pushBack(value);
  }
}
template< typename T >
void redko::List< T >::assign(Iterator< T > first, Iterator< T > last)
{
  clear();
  while (first != last)
  {
    pushBack(*first);
    first++;
  }
}
template< typename T >
void redko::List< T >::assign(std::initializer_list< T > ilist)
{
  clear();
  for (auto value : ilist)
  {
    pushBack(value);
  }
}

template< typename T >
T & redko::List< T >::front()
{
  if (isEmpty())
  {
    throw std::logic_error("calling from empty list");
  }
  return head_.next->data;
}

template< typename T >
redko::Iterator< T > redko::List< T >::beforeBegin() noexcept
{
  return { &head_ };
}
template< typename T >
redko::Iterator< const T > redko::List< T >::beforeBegin() const noexcept
{
  return { &head_ };
}
template< typename T >
redko::Iterator< const T > redko::List< T >::cbeforeBegin() const noexcept
{
  return { &head_ };
}

template< typename T >
redko::Iterator< T > redko::List< T >::begin() noexcept
{
  return { head_.next };
}
template< typename T >
redko::Iterator< const T > redko::List< T >::begin() const noexcept
{
  return { head_.next };
}
template< typename T >
redko::Iterator< const T > redko::List< T >::cbegin() const noexcept
{
  return { head_.next };
}

template< typename T >
redko::Iterator< T > redko::List< T >::end() noexcept
{
  Iterator< T > curr = begin();
  while (curr.node != nullptr)
  {
    curr++;
  }
  return curr;
}
template< typename T >
redko::Iterator< const T > redko::List< T >::end() const noexcept
{
  Iterator< const T > curr = begin();
  while (curr.node != nullptr)
  {
    curr++;
  }
  return curr;
}
template< typename T >
redko::Iterator< const T > redko::List< T >::cend() const noexcept
{
  Iterator< const T > curr = begin();
  while (curr.node != nullptr)
  {
    curr++;
  }
  return curr;
}

template< typename T >
bool redko::List< T >::isEmpty()
{
  return head_.next == nullptr;
}

template< typename T >
void redko::List< T >::clear()
{
  while (begin() != end())
  {
    popFront();
  }
}
template< typename T >
redko::Iterator< T > redko::List< T >::insertAfter(Iterator< T > pos, const T & value)
{
  ListElem< T > * newElem = new ListElem< T >(value);
  newElem->next = pos.node->next;
  pos.node->next = newElem;
  return pos++;
}
template< typename T >
redko::Iterator< T > redko::List< T >::insertAfter(Iterator< T > pos, T && value)
{
  ListElem< T > * newElem = new ListElem< T >(value);
  newElem->next = pos.node->next;
  pos.node->next = newElem;
  return pos++;
}
template< typename T >
redko::Iterator< T > redko::List< T >::eraseAfter(Iterator< T > pos)
{
  ListElem< T > * p = pos.node->next;
  if (p != nullptr)
  {
    pos.node->next = p->next;
    delete p;
  }
  return pos++;
}
template< typename T >
void redko::List< T >::pushBack(const T & value)
{
  ListElem< T > * tmp = new ListElem< T >(value);
  if (head_.next == nullptr)
  {
    head_.next = tmp;
  }
  else
  {
    Iterator< T > curr = begin();
    while (curr.node->next != nullptr)
    {
      curr++;
    }
    curr.node->next = tmp;
  }
}
template< typename T >
void redko::List< T >::pushBack(T && value)
{
  ListElem< T > * tmp = new ListElem< T >(value);
  if (head_.next == nullptr)
  {
    head_.next = tmp;
  }
  else
  {
    Iterator< T > curr = begin();
    while (curr.node->next != nullptr)
    {
      curr++;
    }
    curr.node->next = tmp;
  }
}
template< typename T >
void redko::List< T >::popFront()
{
  eraseAfter(beforeBegin());
}
template< typename T >
void redko::List< T >::swap(List< T > & other)
{
  ListElem< T > tmp = other.head_;
  other.head_ = head_;
  head_ = tmp;
}

template< typename T >
void redko::List< T >::spliceAfter(Iterator< T > pos, List< T > & other)
{
  if (!other.isEmpty())
  {
    Iterator< T > otherElem = other.begin();
    while (otherElem != other.end())
    {
      insertAfter(pos, *otherElem);
      pos++;
      otherElem++;
    }
    other.clear();
  }
}
template< typename T >
void redko::List< T >::spliceAfter(Iterator< T > pos, List< T > && other)
{
  if (!other.isEmpty())
  {
    Iterator< T > otherElem = other.begin();
    while (otherElem != other.end())
    {
      insertAfter(pos, *otherElem);
      pos++;
      otherElem++;
    }
    other.clear();
  }
}
template< typename T >
size_t redko::List< T >::remove(const T & value)
{
  size_t count = 0;
  Iterator< T > prevIt = beforeBegin();
  Iterator< T > currIt = begin();
  while (currIt != end())
  {
    if (*currIt == value)
    {
      currIt = eraseAfter(prevIt);
      count++;
    }
    currIt++;
    prevIt++;
  }
  return count;
}
template< typename T >
template< typename UnaryPredicate >
size_t redko::List< T >::removeIf(UnaryPredicate pred)
{
  size_t count = 0;
  Iterator< T > prevIt = beforeBegin();
  Iterator< T > currIt = begin();
  while (currIt != end())
  {
    if (pred(*currIt))
    {
      currIt = eraseAfter(prevIt);
      count++;
    }
    currIt++;
    prevIt++;
  }
  return count;
}
template< typename T >
void redko::List< T >::reverse() noexcept
{
  if (!isEmpty() && head_.next->next != nullptr)
  {
    ListElem< T > * prevNode = head_.next;
    ListElem< T > * tmpNode = head_.next->next;
    while (tmpNode->next != nullptr)
    {
      tmpNode = tmpNode->next;
      prevNode = prevNode->next;
    }
    tmpNode->next = prevNode;
    ListElem< T > * currNode = prevNode;
    while (currNode != head_.next)
    {
      prevNode = head_.next;
      while (prevNode->next != currNode)
      {
        prevNode = prevNode->next;
      }
      currNode->next = prevNode;
      currNode = prevNode;
    }
    currNode->next = nullptr;
    head_.next = tmpNode;
  }
}
template< typename T >
size_t redko::List< T >::unique()
{
  size_t res = 0;
  if (!isEmpty() && head_.next->next != nullptr)
  {
    Iterator< T > nextElem(head_.next->next);
    Iterator< T > currElem(head_.next);
    while (nextElem != end())
    {
      if (*currElem == *nextElem)
      {
        res++;
        nextElem = eraseAfter((currElem));
        nextElem++;
      }
      else
      {
        currElem++;
        nextElem++;
      }
    }
  }
  return res;
}
template< typename T >
void redko::List< T >::sort()
{
  if (!isEmpty())
  {
    ListElem< T > * currElem = nullptr;
    ListElem< T > * nextElem = nullptr;
    bool wasEdited = true;
    while (wasEdited)
    {
      wasEdited = false;
      currElem = head_.next;
      nextElem = head_.next->next;
      while (nextElem != nullptr)
      {
        if (currElem->data > nextElem->data)
        {
          wasEdited = true;
          T tmp = currElem->data;
          currElem->data = nextElem->data;
          nextElem->data = tmp;
        }
        currElem = nextElem;
        nextElem = nextElem->next;
      }
    }
  }
}

template< typename T >
bool redko::List< T >::operator==(const List< T > & rhs)
{
  if (this != &rhs)
  {
    ListElem< T > * lCurr = head_.next;
    ListElem< T > * rCurr = rhs.head_.next;
    while (lCurr != nullptr && rCurr != nullptr)
    {
      if (lCurr->data != rCurr->data)
      {
        return false;
      }
      lCurr = lCurr->next;
      rCurr = rCurr->next;
    }
    if (lCurr != nullptr || rCurr != nullptr)
    {
      return false;
    }
  }
  return true;
}
template< typename T >
bool redko::List< T >::operator!=(const List< T > & rhs)
{
  return !(*this == rhs);
}
template< typename T >
bool redko::List< T >::operator<(const List< T > & rhs)
{
  if (this != &rhs)
  {
    ListElem< T > * lCurr = head_.next;
    ListElem< T > * rCurr = rhs.head_.next;
    while (rCurr != nullptr)
    {
      if (lCurr == nullptr || lCurr->data < rCurr->data)
      {
        return true;
      }
      else if (lCurr->data > rCurr->data)
      {
        return false;
      }
      lCurr = lCurr->next;
      rCurr = rCurr->next;
    }
  }
  return false;
}
template< typename T >
bool redko::List< T >::operator<=(const List< T > & rhs)
{
  return !(*this > rhs);
}
template< typename T >
bool redko::List< T >::operator>(const List< T > & rhs)
{
  if (this != &rhs)
  {
    ListElem< T > * lCurr = head_.next;
    ListElem< T > * rCurr = rhs.head_.next;
    while (lCurr != nullptr)
    {
      if (rCurr == nullptr || lCurr->data > rCurr->data)
      {
        return true;
      }
      else if (lCurr->data < rCurr->data)
      {
        return false;
      }
      lCurr = lCurr->next;
      rCurr = rCurr->next;
    }
  }
  return false;
}
template< typename T >
bool redko::List< T >::operator>=(const List< T > & rhs)
{
  return !(*this < rhs);
}

#endif
