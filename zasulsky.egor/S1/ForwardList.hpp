#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP

#include <iterator>
#include <stdexcept>
#include "Node.hpp"

namespace zasulsky
{
  template < typename T >
  class ForwardList;

  template < typename T >
  class constIterator;

  template < typename T >
  class Iterator : public std::iterator < std::forward_iterator_tag, T >
  {
  public:
    friend ForwardList<T>;
    friend constIterator<T>;

    Iterator() :
      current_(nullptr)
    {}

    Iterator(detail::Node<T>* start) :
      current_(start)
    {}

    bool operator==(const Iterator& other) const
    {
      return current_ == other.current_;
    }

    bool operator!=(const Iterator& other) const
    {
      return !(*this == other);
    }

    T& operator*()
    {
      return current_->data;
    }

    T* operator->()
    {
      if (current_ == nullptr)
      {
        throw std::logic_error("uncorrect argument");
      }
      return std::addressof(current_->data);
    }

    Iterator& operator++()
    {
      if (current_)
      {
        current_ = current_->next;
      }
      return *this;
    }
    Iterator operator++(int)
    {
      Iterator<T> temp = *this;
      ++(*this);
      return temp;
    }
  private:
    detail::Node< T >* current_;

    Iterator(const constIterator<T>& other) :
      current_(const_cast<detail::Node <T>*> (other.current_))
    {}
  public:
    detail::Node < T >*& getCur()
    {
      return current_;
    }
  };

  template < class T >
  class constIterator : public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    friend ForwardList < T >;
    friend Iterator < T >;

    constIterator() :
      current_(nullptr)
    {}

    constIterator(detail::Node< T >* start) :
      current_(start)
    {}
    constIterator(const Iterator< T > other) noexcept :
      current_(other.current_)
    {}
    bool operator==(const constIterator& other) const
    {
      return current_ == other.current_;
    }

    bool operator!=(const constIterator& other) const
    {
      return !(*this == other);
    }

    const T& operator*() const
    {
      return current_->data;
    }
    const T* operator->() const
    {
      if (current_ == nullptr)
      {
        throw std::logic_error("->");
      }
      return std::addressof(current_->data);
    }

    constIterator& operator++()
    {
      if (current_)
      {
        current_ = current_->next;
      }
      return *this;
    }

    constIterator operator++(int)
    {
      constIterator< T > temp = *this;
      ++(*this);
      return temp;
    }

  private:
    detail::Node< T >* current_;
  public:
    detail::Node < T >*& etCur()
    {
      return current_;
    }

  };


  template < class T >
  class ForwardList
  {

  public:
    using iter = Iterator< T >;
    using constIter = constIterator< T >;

    ForwardList() :
      fakeNode_(static_cast<detail::Node< T >*>(operator new(sizeof(detail::Node < T >))))
    {
      fakeNode_->next = nullptr;
    }
    explicit ForwardList(detail::Node<  T>* head) :
      fakeNode_(reinterpret_cast<detail::Node< T >*>(operator new(sizeof(detail::Node< T >))))
    {
      fakeNode_->next = head;
    }
    ForwardList(const ForwardList& other) :
      fakeNode_(static_cast<detail::Node<T>*>(operator new(sizeof(detail::Node< T >))))
    {
      fakeNode_->next = nullptr;
      insert_after(other.cbegin(), other.cend(), cbeforeBegin());
    }
    ForwardList(ForwardList&& other) :
      ForwardList(other.head())
    {
      other.head() = nullptr;
    }
    ~ForwardList()
    {
      clear();
      operator delete(reinterpret_cast<void*>(fakeNode_), sizeof(detail::Node<T>));
    }

    ForwardList& operator=(const ForwardList& rhs)
    {
      if (this == std::addressof(rhs))
      {
        return *this;
      }
      try
      {
        clear();
        insert_after(rhs.cbegin(), rhs.cend(), cbeforeBegin());
      }
      catch (std::bad_alloc&)
      {
        clear();
        throw;
      }
      return *this;
    }

    ForwardList& operator=(ForwardList&& rhs)
    {
      if (this == std::addressof(rhs))
      {
        return *this;
      }
      clear();
      head() = rhs.head();
      rhs.head() = nullptr;
      return *this;
    }

    iter begin()
    {
      return iter(fakeNode_->next);
    }
    iter beforeBegin()
    {
      return iter(fakeNode_);
    }

    iter end()
    {
      return iter(nullptr);
    }
    constIter cbegin() const
    {
      return constIter(fakeNode_->next);
    }

    constIter cbeforeBegin() const
    {
      return constIter(fakeNode_);
    }

    constIter cend() const
    {
      return constIter();
    }
    iter insert_after(constIter it, T  data)
    {
      checkIt(it);
      iter noConstIt(it);
      auto temp = noConstIt.current_->next;
      noConstIt.current_->next = new detail::Node< T >(data, temp);
      return ++noConstIt;
    }

    template < class inpIt >
    iter insert_after(inpIt begin, inpIt end, constIter beforeBegin)
    {
      iter noConstIt(beforeBegin);
      while (begin != end)
      {
        insert_after(noConstIt, *begin);
        begin++;
      }
      return ++noConstIt;
    }

    iter erase_after(constIter it)
    {
      checkIt(it);
      iter noConstIt(it);
      auto temp = noConstIt.current_->next;
      if (temp)
      {
        noConstIt.current_->next = temp->next;
        delete temp;
        return noConstIt++;
      }
      else
      {
        throw std::runtime_error("error");
      }
    }

    void pushFront(T value)
    {
      insert_after(cbeforeBegin(), value);
    }

    void popFront()
    {
      if (empty())
      {
        throw std::logic_error("ForwardList is empty");
      }
      erase_after(cbeforeBegin());
    }

    bool empty() const
    {
      return fakeNode_->next == nullptr;
    }
    void clear()
    {
      while (!empty())
      {
        popFront();
      }
    }

    T& front()
    {
      if (empty())
      {
        throw std::logic_error("ForwardList is empty");
      }
      return *begin();
    }

    detail::Node< T >** getPtrHead()
    {
      return  fakeNode_ ? std::addressof(fakeNode_->next) : nullptr;
    }

    detail::Node< T >*& head()
    {
      return fakeNode_->next;
    }

    int size()
    {
      int count = 0;
      constIter it = cbegin();
      while (it != cend())
      {
        ++it;
        ++count;
      }
      return count;
    }

    void SpliceAfter(constIter it, ForwardList& fl)
    {
      detail::Node<T>* next = const_cast<detail::Node<T>*>(it.current_)->next;
      const_cast<detail::Node<T>*>(it.current_)->next = fl.head();
      while (it.current_->next)
      {
        ++it;
      }
      const_cast<detail::Node< T >*>(it.current_)->next = next;
      fl.head() = nullptr;
    }

  private:

    detail::Node< T >* fakeNode_;

    void checkIt(constIter it)
    {
      if (it.current_ == nullptr)
      {
        throw std::runtime_error("iterator is empty");
      }
    }
  };
}

#endif
