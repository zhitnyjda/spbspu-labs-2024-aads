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

    List();
    ~List();

    //перегрузки операторов

    void clear();
    void push(const T & value);

    //итераторы

    private:
      struct ListNode
      {
        explicit ListNode(const T & d):
          data(d),
          next(nullptr),
          prev(nullptr)
        {}
        T data;
        ListNode * next;
        ListNode * prev;
      };

      ListNode *head;
      ListNode *tail;
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
    this_t operator--();
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
  assert(node_ != nullptr);
  node_ = node_->next;
  return *this;
}

template< typename T >
typename ponomarev::List< T >::ConstIterator & ponomarev::List< T >::ConstIterator::operator--()
{
  assert(node_ != nullptr);
  node_ = node_->prev;
  return *this;
}

template< typename T >
const T & ponomarev::List< T >::ConstIterator::*() const
{
  return node_->data;
}

template< typename T >
const T * ponomarev::List< T >::ConstIterator::operator->() const
{
  return &(node_->data);
}

template< typename T >
bool ponomarev::List< T >::ConstIterator::operator==(const this_t & some) const
{
  return node_ == some.node_;
}

template< typename T >
bool ponomarev::List< T >::ConstIterator::operator==(const this_t & some) const
{
  return !(some == *this);
}

template< typename T >
ponomarev::List< T >::List():
  head(nullptr),
  tail(nullptr)
{}

template< typename T >
ponomarev::List< T >::~List()
{
  clear();
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
void ponomarev::List< T >::push(const T & value)
{
  ListNode * data = new ListNode(value);
  if (head == tail == nullptr)
  {
    head->next = data;
    tail->prev = data;
  }
  else
  {
    ListNode * temp = tail->prev;
    temp->next = data;
    tail->prev = data;
  }
}

#endif
