#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <assert.h>
#include <initializer_list>

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
    List(iter beginThat, iter endThat);
    List(std::initializer_list< T > ilThat);
    ~List();

    void popFront();
    void popBack();
    void pushFront(T& data);
    void pushBack(T& data);
    void pushFront(T&& data);
    void pushBack(T&& data);

    void assign(size_t amount, T& data);
    void assign(iter beginThat, iter endThat);
    void assign(std::initializer_list<T> ilThat);

    iter insert(iter& pos, T& data);
    iter insert(iter& pos, T&& data);
    iter insert(iter& pos, size_t& amount, T& data);
    iter insert(iter& pos, size_t& amount, T&& data);
    iter erase(iter& pos);
    iter erase(iter& first, iter& last);

    void remove(const T& value);

    template< class Func >
    void remove_if(Func p);

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
  ConstIterator iter_;
};

template< typename T >
psarev::List< T >::Iterator::Iterator() :
  iter_(ConstIterator())
{}

template< typename T >
psarev::List< T >::Iterator::Iterator(Unit* ptr) :
  iter_(ConstIterator(ptr))
{}

template< typename T >
psarev::List< T >::Iterator::Iterator(ConstIterator constIter) :
  iter_(constIter)
{}

template < typename T >
typename psarev::List< T >::Iterator& psarev::List< T >::Iterator::operator++()
{
  assert(iter_ != ConstIterator());
  iter_++;
  return iter_;
};

template < typename T >
typename psarev::List< T >::Iterator psarev::List< T >::Iterator::operator++(int)
{
  ++iter_;
  return iter_;
}

template < typename T >
typename psarev::List< T >::Iterator& psarev::List< T >::Iterator::operator--()
{
  assert(iter_ != nullptr);
  iter_--;
  return iter_;
}

template < typename T >
typename psarev::List< T >::Iterator psarev::List< T >::Iterator::operator--(int)
{
  --iter_;
  return iter_;
}

template< typename T >
T& psarev::List< T >::Iterator::operator*()
{
  return iter_.unit->data;
}

template< typename T >
T* psarev::List< T >::Iterator::operator->()
{
  return &(iter_.unit->data);
}

template< typename T >
const T& psarev::List< T >::Iterator::operator*() const
{
  return iter_.unit->data;
}

template< typename T >
const T* psarev::List< T >::Iterator::operator->() const
{
  return &(iter_.unit->data);
}

template< typename T >
bool psarev::List< T >::Iterator::operator==(const this_t& that) const
{
  return iter_ == that.iter_;
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
psarev::List< T >::List(iter beginThat, iter endThat)
{
  size = 0;
  while (beginThat != endThat)
  {
    pushBack(*beginThat);
    beginThat++;
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

template<typename T>
void psarev::List<T>::pushFront(T&& data)
{
  head = new Unit(data, head);
  if (size != 0)
  {
    head->next->prev = head;
  }
  size++;
}

template<typename T>
void psarev::List<T>::pushBack(T&& data)
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

template<typename T>
void psarev::List<T>::assign(size_t amount, T& data)
{
  clear();
  for (int i = 0; i < amount; i++)
  {
    pushBack(data);
  }
}

template<typename T>
void psarev::List<T>::assign(iter beginThat, iter endThat)
{
  clear();
  while (beginThat != endThat)
  {
    pushBack(*beginThat);
    beginThat++;
  }
}

template<typename T>
void psarev::List<T>::assign(std::initializer_list<T> ilThat)
{
  clear();
  for (T data : ilThat)
  {
    pushBack(data);
  }
}

template<typename T>
typename psarev::List< T >::Iterator psarev::List<T>::insert(iter& pos, T& data)
{
  if (pos == begin())
  {
    pushFront(data);
    return pos--;
  }
  Unit* insertable = new Unit(data);
  insertable->next = pos.iter_.unit;
  insertable->prev = pos.iter_.unit->prev;
  (pos--).iter_.unit->prev = insertable;
  pos.iter_.unit->next = insertable;
  size++;
  return pos++;
}

template<typename T>
typename psarev::List< T >::Iterator psarev::List<T>::insert(iter& pos, T&& data)
{
  if (pos == begin())
  {
    pushFront(data);
    return pos--;
  }
  Unit* insertable = new Unit(data);
  insertable->next = pos.iter_.unit;
  insertable->prev = pos.iter_.unit->prev;
  (pos--).iter_.unit->prev = insertable;
  pos.iter_.unit->next = insertable;
  size++;
  return pos++;
}

template<typename T>
typename psarev::List< T >::Iterator psarev::List<T>::insert(iter& pos, size_t& amount, T& data)
{
  if (amount == 0)
  {
    return pos;
  }
  iter firstPos;
  for (size_t i = 0; i < amount; i++)
  {
    pos = insert(pos, data);
    if (i == 0)
    {
      firstPos = pos;
    }
  }
  return firstPos;
}

template<typename T>
typename psarev::List< T >::Iterator psarev::List<T>::insert(iter& pos, size_t& amount, T&& data)
{
  if (amount == 0)
  {
    return pos;
  }
  iter firstPos;
  for (size_t i = 0; i < amount; i++)
  {
    pos = insert(pos, data);
    if (i == 0)
    {
      firstPos = pos;
    }
  }
  return firstPos;
}

template<typename T>
typename psarev::List< T >::Iterator psarev::List<T>::erase(iter& pos)
{
  if (pos.iter_.unit == head)
  {
    popFront();
    return(begin());
  }
  if (pos.iter_.unit == tail)
  {
    iter cpEnd = end();
    popBack();
    return(cpEnd);
  }
  Unit* del = pos.iter_.unit;
  Unit* foll = del->next;
  del->prev->next = del->next;
  del->next->prev = del->prev;
  delete del;
  size--;
  iter toFollow(foll);
  return(toFollow);
}

template<typename T>
typename psarev::List< T >::Iterator psarev::List<T>::erase(iter& first, iter& last)
{
  if (first == last)
  {
    return(last);
  }
  for (first; first != last; )
  {
    first = erase(first);
  }
  return(first);
}

template< typename T >
void psarev::List< T >::remove(const T& value)
{
  Unit* tempo = this->head;
  for (size_t i = 0; i < (size + 1); i++)
  {
    if (tempo->data == value)
    {
      if (tempo == head)
      {
        tempo = tempo->next;
        popFront();
      }
      else if (tempo == tail)
      {
        popBack();
      }
      else
      {
        Unit* removable = tempo;
        tempo = tempo->prev;
        tempo->next = removable->next;
        removable->next->prev = tempo;
        delete removable;
        i--;
        --size;
        tempo = tempo->next;
      }
    }
    else
    {
      tempo = tempo->next;
    }
  }
}

template< typename T >
template< class Func >
void psarev::List< T >::remove_if(Func p)
{
  Unit* tempo = this->head;
  for (size_t i = 0; i < (size + 1); i++)
  {
    if (p(tempo->data))
    {
      if (tempo == head)
      {
        tempo = tempo->next;
        popFront();
      }
      else if (tempo == tail)
      {
        popBack();
      }
      else
      {
        Unit* removable = tempo;
        tempo = tempo->prev;
        tempo->next = removable->next;
        removable->next->prev = tempo;
        delete removable;
        i--;
        --size;
        tempo = tempo->next;
      }
    }
    else
    {
      tempo = tempo->next;
    }
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
