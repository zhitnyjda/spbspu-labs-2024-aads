#ifndef MAINEARRAY_HPP
#define MAINEARRAY_HPP

#include <iostream>
#include "Node.hpp"

namespace kaseev {
  template<class T>
  class List {
  public:
    List() : head(nullptr), ArrSize(0) {}
    ~List();

    void pushBack(T& value);
    bool empty();
    long int size() const;
    T& operator[](size_t index);

  private:
    size_t ArrSize;
    Node<T>* head;
  };

  template<class T>
  List<T>::~List() {
    while (head != nullptr) {
      Node<T>* temp = head;
      head = head->next;
      delete temp;
    }
  }

  template<class T>
  void List<T>::pushBack(T& value) {
    Node<T>* newNode = new Node<T>(value);

    if (head == nullptr) {
      head = newNode;
    } else {
      Node<T>* current = head;
      while (current->next != nullptr) {
        current = current->next;
      }
      current->next = newNode;
    }

    ArrSize++;
  }

  template<class T>
  bool List<T>::empty() {
    return head == nullptr;
  }

  template<class T>
  long int List<T>::size() const {
    return ArrSize;
  }

  template<class T>
  T& List<T>::operator[](size_t index) {
    if (index >= ArrSize) {
      throw std::out_of_range("Index out of range");
    }
    Node<T>* current = head;
    for (size_t i = 0; i < index; ++i) {
      current = current->next;
    }
    return current->data;
  }

}

#endif
