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
}
#endif
