#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <assert.h>

namespace psarev
{
  template< typename T >
  class List
  {
  public:
    class ConstIterator;
    class Iterator;
    using cIter = ConstIterator;
    using iter = Iterator;
    List();
    List(size_t amount);
    List(size_t amount, const T& data);
    List(iter othHead, iter othTail);
    List(std::initializer_list< T > ilThat);
    ~List();

    void popFront();
    void popBack();
    void pushFront(T& data);
    void pushBack(T& data);

    void remove(const T& value);

    T& getFront() const;
    T& getBack() const;

    void swap(List< T >& other) noexcept;
    void clear();

    bool empty() const noexcept;
    size_t getSize() const noexcept;

    cIter cbegin() const noexcept;
    cIter cend() const noexcept;
    cIter begin() const noexcept;
    cIter end() const noexcept;
    iter begin() noexcept;
    iter end() noexcept;

  private:
    class Unit
    {
    public:
      T data;
      Unit* next;
      Unit* prev;
      Unit(T data, Unit* next = nullptr, Unit* prev = nullptr)
      {
        this->data = data;
        this->next = next;
        this->prev = prev;
      }
    };

    Unit* head;
    Unit* tail;
    size_t size;
  };
}

template< typename T >
class psarev::List< T >::ConstIterator
{
public:
  friend class List< T >;
  using this_t = ConstIterator;

  ConstIterator();
  ConstIterator(Unit* ptr);
  ConstIterator(const this_t&) = default;
  ~ConstIterator() = default;

  this_t& operator=(const this_t&) = default;

  this_t& operator++();
  this_t operator++(int);
  this_t& operator--();
  this_t operator--(int);

  const T& operator*() const;
  const T* operator->() const;

  bool operator==(const this_t&) const;
  bool operator!=(const this_t&) const;

private:
  Unit* unit;
};

template< typename T >
psarev::List< T >::ConstIterator::ConstIterator() :
  unit(nullptr)
{}

template< typename T >
psarev::List< T >::ConstIterator::ConstIterator(Unit* ptr) :
  unit(ptr)
{}

template < typename T >
typename psarev::List< T >::ConstIterator& psarev::List< T >::ConstIterator::operator++()
{
  assert(unit != nullptr);
  unit = unit->next;
  return *this;
};

template < typename T >
typename psarev::List< T >::ConstIterator psarev::List< T >::ConstIterator::operator++(int)
{
  ConstIterator tempo(*this);
  ++(*this);
  return tempo;
}

template < typename T >
typename psarev::List< T >::ConstIterator& psarev::List< T >::ConstIterator::operator--()
{
  assert(unit != nullptr);
  unit = unit->prev;
  return *this;
}

template < typename T >
typename psarev::List< T >::ConstIterator psarev::List< T >::ConstIterator::operator--(int)
{
  ConstIterator tempo(*this);
  --(*this);
  return tempo;
}

template< typename T >
const T& psarev::List< T >::ConstIterator::operator*() const
{
  return unit->data;
}

template< typename T >
const T* psarev::List< T >::ConstIterator::operator->() const
{
  return &(unit->data);
}

template< typename T >
bool psarev::List< T >::ConstIterator::operator==(const this_t& that) const
{
  return unit == that.unit;
}

template< typename T >
bool psarev::List< T >::ConstIterator::operator!=(const this_t& that) const
{
  return !(that == *this);
}
//-----------------------------------
template< typename T >
class psarev::List< T >::Iterator
{
public:
  friend class List< T >;
  using this_t = Iterator;
  Iterator();
  Iterator(Unit* ptr);
  Iterator(ConstIterator constIter);
  Iterator(const this_t&) = default;
  ~Iterator() = default;

  this_t& operator=(const this_t&) = default;
  this_t& operator++();
  this_t operator++(int);
  this_t& operator--();
  this_t operator--(int);

  T& operator*();
  T* operator->();
  const T& operator*() const;
  const T* operator->() const;

  bool operator==(const this_t&) const;
  bool operator!=(const this_t&) const;

private:
  ConstIterator iter;
};

template< typename T >
psarev::List< T >::Iterator::Iterator() :
  iter(ConstIterator())
{}

template< typename T >
psarev::List< T >::Iterator::Iterator(Unit* ptr) :
  iter(ConstIterator(ptr))
{}

template< typename T >
psarev::List< T >::Iterator::Iterator(ConstIterator constIter) :
  iter(constIter)
{}

template < typename T >
typename psarev::List< T >::Iterator& psarev::List< T >::Iterator::operator++()
{
  assert(iter != nullptr);
  iter++;
  return iter;
};

template < typename T >
typename psarev::List< T >::Iterator psarev::List< T >::Iterator::operator++(int)
{
  ++iter;
  return iter;
}

template < typename T >
typename psarev::List< T >::Iterator& psarev::List< T >::Iterator::operator--()
{
  assert(iter != nullptr);
  iter--;
  return iter;
}

template < typename T >
typename psarev::List< T >::Iterator psarev::List< T >::Iterator::operator--(int)
{
  --iter;
  return iter;
}

template< typename T >
T& psarev::List< T >::Iterator::operator*()
{
  return iter.unit->data;
}

template< typename T >
T* psarev::List< T >::Iterator::operator->()
{
  return &(iter.unit->data);
}

template< typename T >
const T& psarev::List< T >::Iterator::operator*() const
{
  return iter.unit->data;
}

template< typename T >
const T* psarev::List< T >::Iterator::operator->() const
{
  return &(iter.unit->data);
}

template< typename T >
bool psarev::List< T >::Iterator::operator==(const this_t& that) const
{
  return iter == that.iter;
}

template< typename T >
bool psarev::List< T >::Iterator::operator!=(const this_t& that) const
{
  return !(that == *this);
}
//----------------------------------------------

template< typename T >
psarev::List< T >::List()
{
  head = nullptr;
  tail = nullptr;
  size = 0;
}

template< typename T >
psarev::List< T >::List(size_t amount)
{
  head = new Unit();
  tail = head;
  Unit* curr = head->next;
  size = 1;
  for (int i = 1; i < amount; i++)
  {
    curr = new Unit();
    tail = curr;
    size++;
    curr = curr->next;
  }
}

template< typename T >
psarev::List< T >::List(size_t amount, const T& data)
{
  size = 0;
  for (int i = 0; i < amount; i++)
  {
    pushBack(data);
  }
}

template< typename T >
psarev::List< T >::List(iter othHead, iter othTail)
{
  size = 0;
  while (othHead != othTail)
  {
    pushBack(*othHead);
    othHead++;
  }
}

template<typename T>
psarev::List<T>::List(std::initializer_list<T> ilThat)
{
  size = 0;
  for (T data : ilThat)
  {
    pushBack(data);
  }
}

template< typename T >
psarev::List< T >::~List()
{
  clear();
}

template< typename T >
void psarev::List< T >::popFront()
{
  Unit* tempo = head;
  head = head->next;
  delete tempo;

  size--;
}

template< typename T >
void psarev::List< T >::popBack()
{
  Unit* delUnit = tail;
  tail = tail->prev;
  delete delUnit;
  size--;
}

template< typename T >
void psarev::List< T >::pushFront(T& data)
{
  head = new Unit(data, head);
  if (size != 0)
  {
    head->next->prev = head;
  }
  size++;
}

template< typename T >
void psarev::List< T >::pushBack(T& data)
{
  if (head == nullptr)
  {
    head = new Unit(data);
    tail = head;
  }
  else
  {
    Unit* adUnit = new Unit(data, nullptr, tail);
    tail->next = adUnit;
    tail = adUnit;
  }
  size++;
}

template< typename T >
void psarev::List< T >::remove(const T& value)
{
  Unit* tempo = this->head;
  for (size_t i = 0; i < size; i++)
  {
    if (tempo->data == value)
    {
      Unit* removable = tempo;
      tempo = tempo->prev;
      tempo->next = removable->next;
      removable->next->prev = tempo;
      delete removable;
      i--;
      --size;
    }
    tempo = tempo->next;
  }
}

template< typename T >
T& psarev::List< T >::getFront() const
{
  return head->data;
}

template< typename T >
T& psarev::List< T >::getBack() const
{
  return tail->data;
}

template< typename T >
void psarev::List< T >::swap(List< T >& targetList) noexcept
{
  Unit tempoH = targetList.head;
  targetList.head = head;
  head = tempoH;
  size_t tempoS = targetList.size;
  targetList.size = size;
  size = tempoS;
}

template< typename T >
void psarev::List< T >::clear()
{
  while (size > 0)
  {
    popFront();
  }
}

template< typename T >
bool psarev::List< T >::empty() const noexcept
{
  return this->getSize() == 0;
}

template< typename T >
size_t psarev::List< T >::getSize() const noexcept
{
  return size;
}

template < typename T >
typename psarev::List< T >::ConstIterator psarev::List< T >::cbegin() const noexcept
{
  return ConstIterator(head);
}

template< typename T >
typename psarev::List< T >::ConstIterator psarev::List< T >::cend() const noexcept
{
  return ConstIterator(tail->next);
}

template < typename T >
typename psarev::List< T >::ConstIterator psarev::List< T >::begin() const noexcept
{
  return ConstIterator(head);
}

template< typename T >
typename psarev::List< T >::ConstIterator psarev::List< T >::end() const noexcept
{
  return ConstIterator(tail->next);
}

template < typename T >
typename psarev::List< T >::Iterator psarev::List< T >::begin() noexcept
{
  return Iterator(head);
}

template< typename T >
typename psarev::List< T >::Iterator psarev::List< T >::end() noexcept
{
  return Iterator(tail->next);
}

#endif
