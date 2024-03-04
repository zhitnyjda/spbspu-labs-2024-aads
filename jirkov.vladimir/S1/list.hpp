#ifndef LIST_HPP
#define LIST_HPP

#include <cassert>
#include "node.hpp"
#include "iterator.hpp"

namespace jirkov {

template <typename T>
class List {
public:
  using value_type = T;
  using size_type = std::size_t;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = ListIterator<T>;
  using const_iterator = ConstListIterator<T>;

  List() : head_(nullptr) {}
  ~List() {
    clear();
  }

  void push_back(const value_type& value) {
    if (head_ == nullptr) {
      head_ = new Node<T>(value, nullptr);
    }
    else {
      Node<T>* current = head_;
      while (current->next != nullptr) {
        current = current->next;
      }
      current->next = new Node<T>(value, nullptr);
    }
  }

  void clear() {
    while (head_ != nullptr) {
      Node<T>* next = head_->next;
      delete head_;
      head_ = next;
    }
  }

  iterator begin() {
    return iterator(head_);
  }

  const_iterator begin() const {
    return const_iterator(head_);
  }

  iterator end() {
    return iterator(nullptr);
  }

  const_iterator end() const {
    return const_iterator(nullptr);
  }

private:
  Node<T>* head_;
};
}

#endif
