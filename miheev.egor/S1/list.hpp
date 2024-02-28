#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <memory>

namespace miheev
{
  template< typename T >
  class List
  {
  public:
    T data_;
    List< T >* next_;
    class Iterator;

    List(T data):
      data_(data),
      next_(nullptr)
    {}
    ~List()
    {
      if (next_ != nullptr)
      {
        delete next_;
      }
    }
    List() = default;
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
    T& operator[](size_t i)
    {
      if (i == 0)
      {
        return data_;
      }
      else
      {
        return next_[i-1];
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

    class Iterator
    {
    private:
      T* cur_;

    public:
      Iterator(T* head)
      {
        cur_ = head;
      }
      T& operator++()
      {
        cur_ = cur_->next_;
        return *cur_;
      }
      T& operator++(int)
      {
        T* copy = cur_;
        cur_ = cur_->next_;
        return *copy;
      }
      T& operator+(size_t n)
      {
        for (; n > 0; n--)
        {
          this++;
        }
      }
      T& operator*()
      {
        return cur_->data;
      }
      T* operator->()
      {
        return std::addressof(cur_->data);
      }
    };
  };
}

#endif

