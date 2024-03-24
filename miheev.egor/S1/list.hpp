#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <iostream>
#include <memory>

namespace miheev
{
  template< typename T >
  class List
  {
  public:
    T data_;
    List< T >* next_;
    bool isEmpty_;
    class Iterator;

    List():
      data_(0),
      next_(nullptr),
      isEmpty_(true)
    {}

    List(T data):
      data_(data),
      next_(nullptr),
      isEmpty_(false)
    {}

    List(const List& toCopy)
    {
      data_ = toCopy.data_;
      isEmpty_ = toCopy.isEmpty_;
      if (toCopy.next_)
      {
        next_ = new List< T >(*toCopy.next_);
      }
      else
      {
        next_ = nullptr;
      }
    }

    List& operator= (const List& list)
    {
      data_ = list.data_;
      isEmpty_ = list.isEmpty_;
      if (next_)
      {
        List< T >* old = next_;
        next_ = nullptr;
        delete old;
      }
      if (list.next_)
      {
        next_ = new List< T >(*(list.next_));
      }
      return *this;
    }

    ~List()
    {
      if (next_)
      {
        delete next_;
      }
    }

    void clear()
    {
      if (next_ != nullptr)
      {
        delete next_;
      }
      delete this;
    }

    size_t size() const
    {
      if (isEmpty_)
      {
        return 0;
      }
      if (!next_)
      {
        return 1;
      }
      return 1 + next_->size();
    }

    void pushBack(T data)
    {
      if (next_ == nullptr)
      {
        next_ = new List< T >(data);
      }
      else
      {
        next_->pushBack(data);
      }
    }

    void print(std::ostream& stream = std::cout, const char& splitter = ' ') const
    {
      stream << data_ << splitter;
      if (next_)
      {
        next_->print(stream, splitter);
      }
      else
      {
        std::cout << '\n';
      }
    }

    Iterator begin()
    {
      return this;
    }
    Iterator end()
    {
      return nullptr;
    }

    struct Iterator
    {
      List<T>* cur;
      using this_t = List< T >::Iterator;
      Iterator():
        cur(nullptr)
      {}
      Iterator(List< T >* head):
        cur(head)
      {}
      Iterator(const this_t&) = default;
      this_t& operator=(const this_t&) = default;
      List<T>& operator+(size_t n)
      {
        for (; n > 0; n--)
        {
          cur++;
        }
        return cur;
      }

      T& operator*()
      {
        return cur->data_;
      }

      T* operator->() const
      {
        return std::addressof(cur->data_);
      }

      explicit operator bool() const
      {
        return cur->next_ != nullptr;
      }

      bool isEmptyObject() const
      {
        return cur->isEmpty_;
      }

      this_t& operator++()
      {
        cur = cur->next_;
        return *this;
      }

      this_t operator++(int)
      {
        this_t copy(*this);
        cur = cur->next_;
        return *copy;
      }

      bool operator!=(const this_t & rhs) const
      {
        return cur != rhs.cur;
      }

      bool operator==(const this_t & rhs) const
      {
        return cur == rhs.cur;
      }
    };
  };
}

#endif
