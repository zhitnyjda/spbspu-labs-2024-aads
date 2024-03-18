#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <iterator>
#include <stdexcept>

template<typename T>
class ListNode
{
public:
  T value;
  ListNode* next;
  ListNode(T val) : value(val), next(nullptr) {}
};
template<typename T>
class List
{
public:
  ListNode<T>* head;
  ListNode<T>* tail;
  size_t size;

  List() : head(nullptr), tail(nullptr), size(0) {}
  List(const List& other) : head(nullptr), tail(nullptr), size(0)
  {
    ListNode<T>* current = other.head;
    while (current != nullptr)
    {
      push_back(current->value);
      current = current->next;
    }
  }
  List(List&& other) noexcept : head(other.head), tail(other.tail), size(other.size)
  {
    other.head = other.tail = nullptr;
    other.size = 0;
  }
  List& operator=(List other)
  {
    swap(*this, other);
    return *this;
  }
  ~List() { clear(); }
  void push_back(T val)
  {
        ListNode<T>* newNode = new ListNode<T>(val);
        if (tail) tail->next = newNode;
        else head = newNode;
        tail = newNode;
        ++size;
  }
  bool empty() const { return size == 0; }
  void clear()
  {
    while (head)
    {
        ListNode<T>* temp = head;
        head = head->next;
        delete temp;
    }
    head = tail = nullptr;
    size = 0;
  }
  class iterator
  {
    ListNode<T>* ptr;
  public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::forward_iterator_tag;
    iterator(ListNode<T>* p = nullptr) : ptr(p) {}
    iterator& operator++()
    {
      if (ptr == nullptr) throw std::out_of_range("Iterator cannot be incremented past the end");
      ptr = ptr->next;
      return *this;
    }
    bool operator!=(const iterator& other) const
    {
      return ptr != other.ptr;
    }
    reference operator*()
    {
      if (ptr == nullptr) throw std::out_of_range("Iterator cannot be dereferenced");
      return ptr->value;
    }
  };
  iterator begin()
  {
    return iterator(head);
  }
  iterator end()
  {
    if (nullptr)
    {
      return nullptr;
    }
    else
    {
      return iterator(nullptr);
    }
  }
};
#endif
