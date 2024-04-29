#ifndef LIST_HPP
#define LIST_HPP

#include <iterator>

namespace ponomarev
{
  template< typename T >
  class List
  {
  public:
    class ConstIterator;
    class Iterator;

    using iterator = Iterator;
    using const_iterator = ConstIterator;

    List();
    List(size_t count, const T & value);
    explicit List(size_t amount);
    List(iterator first, iterator last);
    List(std::initializer_list< T > init);
    ~List();

    List< T > & operator=(const List & other);
    List< T > & operator=(List && other);

    T & front();

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    bool isEmpty() const noexcept;

    void clear();
    void pushBack(const T & value);
    void pop_front();
    void swap(List & other) noexcept;

    private:
      struct ListNode
      {
        friend class List< T >;
        ListNode(T data, ListNode * next = nullptr, ListNode * prev = nullptr)
        {
           this->data = data;
           this->next = next;
           this->prev = prev;
        }

        T data;
        ListNode * next;
        ListNode * prev;
      };

      ListNode * head;
      ListNode * tail;
  };
}

template< typename T >
class ponomarev::List< T >::ConstIterator: public std::iterator< std::bidirectional_iterator_tag, T >
{
  public:
    friend class List< T >;
    using this_t = ConstIterator;

    ConstIterator();
    explicit ConstIterator(ListNode * ptr);
    ConstIterator(const this_t &) = default;
    ~ConstIterator() = default;

    this_t & operator=(const this_t &) = default;
    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);

    const T & operator*() const;
    const T * operator->() const;

    bool operator!=(const this_t &) const;
    bool operator==(const this_t &) const;

  private:
    ListNode * node_;
};

template< typename T >
ponomarev::List< T >::ConstIterator::ConstIterator():
  node_(nullptr)
{}

template< typename T >
ponomarev::List< T >::ConstIterator::ConstIterator(ListNode * ptr):
  node_(ptr)
{}

template< typename T >
typename ponomarev::List< T >::ConstIterator & ponomarev::List< T >::ConstIterator::operator++()
{
  node_ = node_->next;
  return *this;
}

template < typename T >
typename ponomarev::List< T >::ConstIterator ponomarev::List< T >::ConstIterator::operator++(int)
{
  ConstIterator t(*this);
  ++(*this);
  return t;
}

template< typename T >
typename ponomarev::List< T >::ConstIterator & ponomarev::List< T >::ConstIterator::operator--()
{
  node_ = node_->prev;
  return *this;
}

template < typename T >
typename ponomarev::List< T >::ConstIterator ponomarev::List< T >::ConstIterator::operator--(int)
{
  ConstIterator t(*this);
  --(*this);
  return t;
}

template< typename T >
const T & ponomarev::List< T >::ConstIterator::operator*() const
{
  return node_->data;
}

template< typename T >
const T * ponomarev::List< T >::ConstIterator::operator->() const
{
  return & (node_->data);
}

template< typename T >
bool ponomarev::List< T >::ConstIterator::operator==(const this_t & some) const
{
  return node_ == some.node_;
}

template< typename T >
bool ponomarev::List< T >::ConstIterator::operator!=(const this_t & some) const
{
  return !(some == *this);
}

template< typename T >
class ponomarev::List< T >::Iterator : public std::iterator< std::bidirectional_iterator_tag, T >
{
public:
  friend class List< T >;
  using this_t = Iterator;
  Iterator();
  explicit Iterator(ListNode * ptr);
  explicit Iterator(ConstIterator constIterator);
  Iterator(const this_t &) = default;
  ~Iterator() = default;

  this_t & operator=(const this_t &) = default;
  this_t & operator++();
  this_t operator++(int);
  this_t & operator--();
  this_t operator--(int);

  T & operator*();
  T * operator->();
  const T & operator*() const;
  const T * operator->() const;

  bool operator==(const this_t &) const;
  bool operator!=(const this_t &) const;

private:
  ConstIterator iterator_;
};

template< typename T >
ponomarev::List< T >::Iterator::Iterator():
  iterator_(ConstIterator())
{}

template< typename T >
ponomarev::List< T >::Iterator::Iterator(ListNode * ptr) :
  iterator_(ConstIterator(ptr))
{}

template< typename T >
ponomarev::List< T >::Iterator::Iterator(ConstIterator constIterator) :
  iterator_(constIterator)
{}

template< typename T >
typename ponomarev::List< T >::Iterator & ponomarev::List< T >::Iterator::operator++()
{
  iterator_++;
  return iterator_;
};

template< typename T >
typename ponomarev::List< T >::Iterator ponomarev::List< T >::Iterator::operator++(int)
{
  ++iterator_;
  return iterator_;
}

template < typename T >
typename ponomarev::List< T >::Iterator & ponomarev::List< T >::Iterator::operator--()
{
  iterator_--;
  return iterator_;
}

template < typename T >
typename ponomarev::List< T >::Iterator ponomarev::List< T >::Iterator::operator--(int)
{
  --iterator_;
  return iterator_;
}

template< typename T >
T & ponomarev::List< T >::Iterator::operator*()
{
  return iterator_.node_->data;
}

template< typename T >
T * ponomarev::List< T >::Iterator::operator->()
{
  return & (iterator_.node_->data);
}

template< typename T >
const T & ponomarev::List< T >::Iterator::operator*() const
{
  return iterator_.node_->data;
}

template< typename T >
const T * ponomarev::List< T >::Iterator::operator->() const
{
  return & (iterator_.node_->data);
}

template< typename T >
bool ponomarev::List< T >::Iterator::operator==(const this_t & some) const
{
  return iterator_ == some.iterator_;
}

template< typename T >
bool ponomarev::List< T >::Iterator::operator!=(const this_t & some) const
{
  return !(some == *this);
}

template< typename T >
ponomarev::List< T >::List():
  head(nullptr),
  tail(nullptr)
{}

template< typename T >
ponomarev::List< T >::List(size_t count, const T & value)
{
  for (int i = 0; i < count; i++)
  {
    pushBack(value);
  }
}

template< typename T >
ponomarev::List< T >::List(size_t amount)
{
  for (int i = 1; i <= amount; i++)
  {
    pushBack(T());
  }
}

template< typename T >
ponomarev::List< T >::List(iterator first, iterator last)
{
  while (first != last)
  {
    pushBack(*first);
    first++;
  }
}

template< typename T >
ponomarev::List< T >::List(std::initializer_list< T > init)
{
  for (T data : init)
  {
    pushBack(data);
  }
}

template< typename T >
ponomarev::List< T >::~List()
{
  clear();
}

template< typename T >
ponomarev::List< T > & ponomarev::List< T >::operator=(const List & other)
{
  if (&other != this)
  {
    clear();
    ListNode * temp = other.head.next;
    while (temp != nullptr)
    {
      push(temp->data);
      temp = temp->next;
    }
  }
  return *this;
}

template< typename T >
ponomarev::List< T > & ponomarev::List< T >::operator=(List && other)
{
  if (&other != this)
  {
    clear();
    head.next = std::move(other.head.next);
    other.head.next = nullptr;
  }
  return *this;
}


template< typename T >
T & ponomarev::List< T >::front()
{
  return head.next->data;
}

template< typename T >
typename ponomarev::List< T >::iterator ponomarev::List< T >::begin() noexcept
{
  return Iterator(head->next);
}

template< typename T >
typename ponomarev::List< T >::iterator ponomarev::List< T >::end() noexcept
{
  return Iterator(tail.prev);
}

template< typename T >
typename ponomarev::List< T >::const_iterator ponomarev::List< T >::begin() const noexcept
{
  return ConstIterator(head.next);
}

template< typename T >
typename ponomarev::List< T >::const_iterator ponomarev::List< T >::end() const noexcept
{
  return ConstIterator(tail.prev);
}

template< typename T >
typename ponomarev::List< T >::const_iterator ponomarev::List< T >::cbegin() const noexcept
{
  return ConstIterator(head.next);
}

template< typename T >
typename ponomarev::List< T >::const_iterator ponomarev::List< T >::cend() const noexcept
{
   return ConstIterator(tail.prev);
}

template< typename T >
bool ponomarev::List< T >::isEmpty() const noexcept
{
  return (head.next == nullptr);
}

template< typename T >
void ponomarev::List< T >::clear()
{
  while (head)
  {
    head = head->next;
    delete head->prev;
  }
}

template< typename T >
void ponomarev::List< T >::pushBack(const T & value)
{
  if (head == nullptr)
  {
    head = new ListNode(value);
    tail = head;
  }
  else
  {
    ListNode * temp = new ListNode(value, nullptr, tail);
    tail->next = temp;
    tail = temp;
  }
}

template< typename T >
void ponomarev::List< T >::pop_front()
{
  ListNode * temp = head->next;
  head->next = temp->next;
  delete temp;
}

template< typename T >
void ponomarev::List< T >::swap(List & other) noexcept
{
  ListNode temp = other.head;
  other.head = head;
  head = temp;
}

#endif
