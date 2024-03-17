#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <utility>
#include <iostream>
#include <limits>

namespace Panov {

  template<typename T>
  class List {
  private:
    struct Node {
      T data;
      Node* next;
      Node* prev;
      Node(const T& newData) : data(newData), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    std::size_t size;

  public:
    class Iterator {
    private:
      Node* current;

    public:
      Iterator(Node* node) : current(node) {}

      T& operator*() const {
        return current->data;
      }

      Iterator& operator++() {
        current = current->next;
        return *this;
      }

      Iterator operator++(int) {
        Iterator temp = *this;
        ++(*this);
        return temp;
      }

      bool operator==(const Iterator& other) const {
        return current == other.current;
      }

      bool operator!=(const Iterator& other) const {
        return !(*this == other);
      }
    };

    List() : head(nullptr), tail(nullptr), size(0) {}

    List(const List& other) : head(nullptr), tail(nullptr), size(0) {
      for (auto it = other.begin(); it != other.end(); ++it)
        push_back(*it);
    }

    List& operator=(const List& other) {
      if (this != &other) {
        clear();
        for (auto it = other.begin(); it != other.end(); ++it)
          push_back(*it);
      }
      return *this;
    }

    ~List() {
      clear();
    }

    void push_back(const T& value) {
      if (size == std::numeric_limits<std::size_t>::max()) {
        std::cerr << "Error: Maximum size of the list reached. Overflow detected.\n";
        exit(1);
      }

      try {
        Node* newNode = new Node(value);
        if (empty()) {
          head = newNode;
        }
        else {
          tail->next = newNode;
          newNode->prev = tail;
        }
        tail = newNode;
        ++size;
      }
      catch (const std::bad_alloc& e) {
        std::cerr << "Error: Memory allocation failed. Overflow detected.\n";
        exit(1);
      }
    }

    void clear() {
      while (!empty()) {
        pop_back();
      }
    }

    bool empty() const {
      return size == 0;
    }

    void pop_back() {
      if (empty()) return;
      if (size == 1) {
        delete tail;
        head = tail = nullptr;
      }
      else {
        Node* temp = tail->prev;
        delete tail;
        tail = temp;
        tail->next = nullptr;
      }
      --size;
    }

    Iterator begin() const {
      return Iterator(head);
    }

    Iterator end() const {
      return Iterator(nullptr);
    }
  };
}
#endif
