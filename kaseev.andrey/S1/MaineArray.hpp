#ifndef MAINEARRAY_HPP
#define MAINEARRAY_HPP

#include <iostream>
#include "Node.hpp"

namespace kaseev {
  template< class T >
  class List {
  public:
    List() : ArrSize(0), head(nullptr) {}
    ~List();
    List(size_t count);
    List(size_t count, const T& value);
    List(std::initializer_list<T> ilist);
    List(const List& other);

    void pushBack(const T &value);
    bool empty() const;
    int size() const;
    void pop_front();
    void clear();
    void pop(int index);
    void remove(const T &value);
    template< class UnaryPredicate >
    void remove_if(UnaryPredicate p);
    T& front();
    void swap(List &other);

    const T &operator[](int index) const;
    List<T>& operator=(const List<T>& other);


  private:
    int ArrSize;
    Node<T> *head;
  };

  template< class T >
  List<T>::~List()
  {
    clear();
  }

  template< class T >
  void List<T>::pushBack(const T &value)
  {
    Node<T> *newNode = new Node<T>(value);

    if (head == nullptr)
    {
      head = newNode;
    } else
    {
      Node<T> *current = head;
      while (current->next != nullptr)
      {
        current = current->next;
      }
      current->next = newNode;
    }

    ArrSize++;
  }

  template< class T >
  bool List<T>::empty() const
  {
    return head == nullptr;
  }

  template< class T >
  int List<T>::size() const
  {
    return ArrSize;
  }

  template< class T >
  void List<T>::pop_front()
  {
    if (head == nullptr)
    {
      ArrSize = 0;
      throw std::logic_error("empty list");
    }
    Node<T> *temp = head;
    head = head->next;
    temp->next = nullptr;
    delete temp;
    ArrSize--;
  }

  template< class T >
  void List<T>::clear()
  {
    while (head != nullptr)
    {
      pop_front();
    }
  }

  template<class T>
  void List<T>::pop(int index) {
    if (index < 0 || index >= ArrSize) {
      throw std::out_of_range("Index out of range");
    }
    Node<T> *current = head;
    Node<T> *prev = nullptr;
    for (int i = 0; i < index; ++i) {
      prev = current;
      current = current->next;
    }
    if (prev != nullptr) {
      prev->next = current->next;
    } else {
      head = current->next;
    }
    delete current;
    ArrSize--;
  }

  template<class T>
  void List<T>::remove(const T &value) {
    int index = 0;
    while (index < ArrSize) {
      if ((*this)[index] == value) {
        pop(index);
      } else {
        index++;
      }
    }
  }

  template<class T>
  T& List<T>::front() {
    if (empty()) {
      throw std::logic_error("List is empty");
    }
    return head->data;
  }

  template<class T>
  template<class UnaryPredicate>
  void List<T>::remove_if(UnaryPredicate p) {
    while (!empty() && p(front())) {
      pop_front();
    }

    Node<T>* prev = nullptr;
    Node<T>* current = head;

    while (current != nullptr) {
      if (p(current->data)) {
        if (prev == nullptr) {
          pop_front();
          current = head;
        } else {
          prev->next = current->next;
          delete current;
          current = prev->next;
          ArrSize--;
        }
      } else {
        prev = current;
        current = current->next;
      }
    }
  }

  template<class T>
  void List<T>::swap(List &other) {
    Node<T>* temp = head;
    head = other.head;
    other.head = temp;
    int tempSize = ArrSize;
    ArrSize = other.ArrSize;
    other.ArrSize = tempSize;
  }


  template< class T >
  const T &List<T>::operator[](int index) const
  {
    if (index >= ArrSize)
    {
      throw std::out_of_range("Index out of range");
    }
    Node<T> *current = head;
    for (int i = 0; i < index; ++i)
    {
      current = current->next;
    }
    return current->data;
  }

  template<class T>
  List<T>::List(const List& other) : ArrSize(0), head(nullptr) {
    Node<T>* current = other.head;
    while (current != nullptr) {
      pushBack(current->data);
      current = current->next;
    }
  }

  template<class T>
  List<T>& List<T>::operator=(const List<T>& other) {
    if (this != &other) {
      clear();
      Node<T>* current = other.head;
      while (current != nullptr) {
        pushBack(current->data);
        current = current->next;
      }
    }
    return *this;
  }

  template<class T>
  List<T>::List(size_t count) : ArrSize(0), head(nullptr) {
    for (size_t i = 0; i < count; ++i) {
      pushBack(T());
    }
  }

  template<class T>
  List<T>::List(size_t count, const T& value) : ArrSize(0), head(nullptr) {
    for (size_t i = 0; i < count; ++i) {
      pushBack(value);
    }
  }

  template<class T>
  List<T>::List(std::initializer_list<T> ilist) : ArrSize(0), head(nullptr) {
    for (const auto& elem : ilist) {
      pushBack(elem);
    }
  }
}

#endif
