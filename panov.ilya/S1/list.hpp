#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <limits>
#include <stdexcept>
#include "node.hpp"
#include "listiterator.hpp"

namespace Panov
{
  template< class T >
  class List
  {
  public:
    List() :
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {}
    List(const T& value, size_t count) :
      List()
    {
      try
      {
        for (size_t i = 0; i < count; ++i)
        {
          push_back(value);
        }
      }
      catch (const std::exception& e)
      {
        clear();
        throw;
      }
    }
    List(ListIterator< T > start, ListIterator< T > finish) :
      List()
    {
      try
      {
        while (start != finish)
        {
          push_back(*start);
          ++start;
        }
      }
      catch (const std::exception& e)
      {
        clear();
        throw;
      }
    }
    List(std::initializer_list< T > il) :
      List()
    {
      try
      {
        auto it = il.begin();
        while (it != il.end())
        {
          push_back(*it);
          ++it;
        }
      }
      catch (const std::exception& e)
      {
        clear();
        throw;
      }
    }
    List(const List< T >& rhs) :
      List()
    {
      try
      {
        Node< T >* node = rhs.head_;
        while (size_ != rhs.size_)
        {
          push_back(node->value_);
          node = node->next_;
        }
      }
      catch (const std::exception& e)
      {
        for (size_t j = 0; j < size_; ++j)
        {
          pop_front();
        }
        throw;
      }
    }
    List(const List< T >&& rhs)
    {
      swap(rhs);
    }
    bool operator<(const List< T >& rhs) const
    {
      size_t min_size = std::min(rhs.size_, size_);
      Node< T >* node = head_;
      Node< T >* rhs_node = rhs.head_;
      for (size_t i = 0; i < min_size; ++i)
      {
        if (node->value_ != rhs_node->value_)
        {
          return node->value_ < rhs_node->value_;
        }
        node = node->next_;
        rhs_node = rhs_node->next_;
      }
      return false;
    }
    bool operator>=(const List< T >& rhs) const
    {
      return !(*this < rhs);
    }
    bool operator<=(const List< T >& rhs) const
    {
      return !(rhs < *this);
    }
    bool operator>(const List< T >& rhs) const
    {
      return (rhs < *this);
    }
    bool operator==(const List< T >& rhs) const
    {
      return !(*this < rhs) && !(rhs < *this);
    }
    bool operator!=(const List< T >& rhs) const
    {
      return !(rhs == *this);
    }
    List< T >& operator=(const List< T >&& rhs)
    {
      if (this != std::addressof(rhs))
      {
        clear();
        swap(rhs);
      }
      return *this;
    }
    List< T >& operator=(const List< T >& rhs)
    {
      if (this != std::addressof(rhs))
      {
        List< T > temp(rhs);
        temp.swap(*this);
      }
      return *this;
    }
    ~List()
    {
      clear();
    }
    void swap(List< T >& list)
    {
      std::swap(list.head_, head_);
      std::swap(list.tail_, tail_);
      std::swap(list.size_, size_);
    }
    const T& at(size_t i) const
    {
      if (i >= size_)
      {
        throw std::logic_error("Element outside the list");
      }
      return operator[](i);
    }
    T& at(size_t i)
    {
      return const_cast<T&>(static_cast<const List< T >&>(*this).at(i));
    }
    T& operator[](size_t i)
    {
      return const_cast<T&>(static_cast<const List< T >&>(*this).operator[](i));
    }
    const T& operator[](size_t i) const
    {
      ConstListIterator< T > iterator(head_);
      for (size_t j = 0; j < i; ++j)
      {
        ++iterator;
      }
      return *iterator;
    }
    size_t size() const
    {
      return size_;
    }
    T& back()
    {
      return tail_->value_;
    }
    T& front()
    {
      return head_->value_;
    }
    const T& back() const
    {
      return tail_->value_;
    }
    const T& front() const
    {
      return head_->value_;
    }
    ListIterator< T > begin()
    {
      return ListIterator< T >(head_);
    }
    ListIterator< T > end()
    {
      return ListIterator< T >(tail_->next_);
    }
    ConstListIterator< T > cbegin() const
    {
      return ConstListIterator< T >(head_);
    }
    ConstListIterator< T > cend() const
    {
      return ConstListIterator< T >(tail_->next_);
    }
    ConstListIterator< T > erase(ConstListIterator< T > it)
    {
      ConstListIterator< T > end(tail_);
      if (it == cbegin())
      {
        pop_front();
      }
      else if (it == end)
      {
        pop_back();
      }
      else
      {
        ConstListIterator< T > iterator(head_);
        Node< T >* node = head_;
        while (iterator != it)
        {
          node = node->next_;
          ++iterator;
        }
        node->next_->prev_ = node->prev_;
        node->prev_->next_ = node->next_;
        delete node;
        --size_;
      }
      return it;
    }
    ConstListIterator< T > erase(ConstListIterator< T > it_start, ConstListIterator< T > it_finish)
    {
      while (it_start != it_finish)
      {
        erase(it_start++);
      }
      return it_finish;
    }
    ListIterator< T > insert(ListIterator< T > it, const T& value)
    {
      try
      {
        if (it == begin())
        {
          push_front(value);
        }
        else if (it == end())
        {
          push_back(value);
        }
        else
        {
          ListIterator< T > iterator(head_);
          Node< T >* node = head_;
          while (iterator != it)
          {
            node = node->next_;
            ++iterator;
          }
          Node< T >* new_node = new Node< T >(value, node, node->prev_);
          node->prev_ = new_node;
          new_node->prev_->next_ = new_node;
          ++size_;
        }
        return ++it;
      }
      catch (const std::exception& e)
      {
        clear();
        throw;
      }
    }
    ListIterator< T > insert(ListIterator< T > it, ListIterator< T > start, ListIterator< T > finish)
    {
      try
      {
        while (start != finish)
        {
          insert(it, *start);
          ++it;
          ++start;
        }
        return it;
      }
      catch (const std::exception& e)
      {
        clear();
        throw;
      }
    }
    ListIterator< T > insert(ListIterator< T > it, size_t n, const T& value)
    {
      for (size_t i = 0; i < n; ++i)
      {
        insert(it++, value);
      }
      return it;
    }
    ListIterator< T > insert(ListIterator< T > it, std::initializer_list< T > il)
    {
      auto iterator = il.begin();
      while (iterator != il.end())
      {
        insert(it, *iterator);
        ++iterator;
      }
      return it;
    }
    bool empty() const
    {
      return size_ == 0;
    }
    void push_front(const T& value)
    {
      Node< T >* new_node = new Node< T >(value, head_, nullptr);
      if (head_)
      {
        head_->prev_ = new_node;
      }
      if (!tail_)
      {
        try
        {
          Node< T >* end_node = new Node< T >(value);
          tail_ = new_node;
          end_node->prev_ = tail_;
          tail_->next_ = end_node;
        }
        catch (const std::exception& e)
        {
          delete new_node;
          throw;
        }
      }
      head_ = new_node;
      ++size_;
    }
    void push_back(const T& value)
    {
      Node< T >* new_node = new Node< T >(value, nullptr, tail_);
      if (tail_)
      {
        tail_->next_->prev_ = new_node;
        new_node->next_ = tail_->next_;
        tail_->next_ = new_node;
      }
      if (!head_)
      {
        try
        {
          Node< T >* end_node = new Node< T >(value);
          head_ = new_node;
          tail_ = head_;
          end_node->prev_ = tail_;
          tail_->next_ = end_node;
          ++size_;
          return;
        }
        catch (const std::exception& e)
        {
          delete new_node;
          throw;
        }
      }
      tail_ = new_node;
      ++size_;
    }
    void pop_back()
    {
      if (size_ == 1)
      {
        delete tail_->next_;
        delete tail_;
        --size_;
      }
      else
      {
        Node< T >* temp = tail_;
        tail_->next_->prev_ = tail_->prev_;
        tail_->prev_->next_ = tail_->next_;
        tail_ = tail_->prev_;
        delete temp;
        --size_;
      }
    }
    void pop_front()
    {
      if (size_ == 1)
      {
        delete tail_->next_;
        delete head_;
        --size_;
      }
      else
      {
        head_ = head_->next_;
        delete head_->prev_;
        --size_;
      }
    }
    void clear()
    {
      while (!empty())
      {
        pop_back();
      }
    }
  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  };
}
#endif
