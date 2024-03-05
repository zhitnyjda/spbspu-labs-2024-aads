#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"
#include "iterator.hpp"
#include <memory>
#include <stdexcept>

namespace anikanov {

  template<typename T>
  class List {
  public:
    List();
    List(const List &other);
    List(List &&other) noexcept;
    List(const T &value, size_t count);
    ~List();

    void push_back(const T &value);
    T pop(size_t n = -1);
    bool empty();
    size_t size() const;
    void clear();
    void swap(List &other);
    void remove(const T &value);

    template<typename Predicate>
    void remove_if(Predicate pred);
    void assign(size_t count, const T &value);

    T &operator[](size_t index);
    List< T > &operator=(List< T > &&other) noexcept;
    List< T > &operator=(List< T > other);

    anikanov::Iterator< T > back();
    anikanov::Iterator< T > begin() const;
    anikanov::Iterator< T > end() const;

  private:
    std::shared_ptr< Node< T>> head, tail;
    size_t list_size;
  };

  template<typename T>
  List< T > &List< T >::operator=(List< T > other)
  {
    swap(other);
    return *this;
  }

  template<typename T>
  List< T > &List< T >::operator=(List< T > &&other) noexcept
  {
    if (this != &other) {
      clear(); // Освободим существующие ресурсы

      head = other.head;
      tail = other.tail;

      other.head = nullptr;
      other.tail = nullptr;
    }
    return *this;
  }

  template<typename T>
  List< T >::List() : head(nullptr), tail(nullptr), list_size(0)
  {
  }

  template<typename T>
  List< T >::List(const List &other): head(nullptr), tail(nullptr), list_size(0)
  {
    auto current = other.head;
    while (current != nullptr) {
      push_back(current->data);
      current = current->next;
    }
  }

  template<typename T>
  List< T >::List(List &&other) noexcept: head(other.head), tail(other.tail), list_size(other.size)
  {
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
  }

  template<typename T>
  List< T >::List(const T &value, size_t count): head(nullptr), tail(nullptr), list_size(0)
  {
    for (size_t i = 0; i < count; ++i) {
      push_back(value);
    }
  }

  template<typename T>
  List< T >::~List()
  {
    clear();
  }

  template<typename T>
  void List< T >::push_back(const T &value)
  {
    auto newNode = std::make_shared< Node< T>>(value);
    if (head == nullptr) {
      head = newNode;
      tail = newNode;
    } else {
      tail->next = newNode;
      tail = newNode;
    }
    list_size++;
  }

  template<typename T>
  T List< T >::pop(size_t n)
  {
    if (list_size == 0) {
      throw std::out_of_range("List is empty");
    }

    if (n < 0) {
      n += list_size;
    }

    if (n < 0 || n >= list_size) {
      throw std::out_of_range("Index out of range");
    }
    auto current = head;
    for (int i = 0; i < n; ++i) {
      current = current->next;
    }

    if (current->prev != nullptr) {
      current->prev->next = current->next;
    } else {
      head = current->next;
    }

    if (current->next != nullptr) {
      current->next->prev = current->prev;
    } else {
      tail = current->prev;
    }

    T value = current->data;
    delete current;
    --list_size;

    return value;
  }

  template<typename T>
  bool List< T >::empty()
  {
    if (head == tail) {
      return true;
    }
    return false;
  }

  template<typename T>
  size_t List< T >::size() const
  {
    return list_size;
  }

  template<typename T>
  void List< T >::clear()
  {
    auto current = head;
    while (current != nullptr) {
      auto next = current->next;
      current = next;
    }
    head = nullptr;
    tail = nullptr;
  }

  template<typename T>
  void List< T >::swap(List &other)
  {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
  }

  template<typename T>
  void List< T >::assign(size_t count, const T &value)
  {
    clear();
    for (size_t i = 0; i < count; ++i) {
      push_back(value);
    }
  }

  template<typename T>
  void List< T >::remove(const T &value)
  {
    remove_if([value](T &other) {
      return value == other;
    });
  }

  template<typename T>
  template<typename Predicate>
  void List< T >::remove_if(Predicate pred)
  {
    auto current = head;
    while (current != nullptr) {
      if (pred(current->data)) {
        auto toDelete = current;
        if (current->prev != nullptr) {
          current->prev->next = current->next;
        } else {
          head = current->next;
        }
        if (current->next != nullptr) {
          current->next->prev = current->prev;
        } else {
          tail = current->prev;
        }
        current = current->next;
        delete toDelete;
        --list_size;
      } else {
        current = current->next;
      }
    }
  }

  template<typename T>
  T &List< T >::operator[](size_t index)
  {
    if (index >= list_size) {
      throw std::out_of_range("Index out of range");
    }

    auto current = head;
    for (size_t i = 0; i < index; ++i) {
      current = current->next;
    }

    return current->data;
  }

  template<typename T>
  anikanov::Iterator< T > List< T >::back()
  {
    return Iterator< T >(tail);
  }

  template<typename T>
  anikanov::Iterator< T > List< T >::begin() const
  {
    return Iterator< T >(head);
  }

  template<typename T>
  anikanov::Iterator< T > List< T >::end() const
  {
    return Iterator< T >(nullptr);
  }
}

#endif
