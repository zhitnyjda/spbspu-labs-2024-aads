#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>
#include "node.hpp"

namespace jirkov {

template <typename T>
class ListIterator : public std::iterator<std::forward_iterator_tag, T> {
public:
  using value_type = typename Node<T>::value_type;
  using reference = typename Node<T>::value_type&;
  using pointer = typename Node<T>::value_type*;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;

  ListIterator() : current_(nullptr) {}
  explicit ListIterator(Node<T>* node) : current_(node) {}

  reference operator*() const {
    return current_->data;
  }

  pointer operator->() const {
    return &(current_->data);
  }

  ListIterator& operator++() {
    if (current_) {
      current_ = current_->next;
    }
    return *this;
  }

  ListIterator operator++(int) {
    ListIterator temp(*this);
    ++(*this);
    return temp;
  }

  bool operator==(const ListIterator& other) const {
    return current_ == other.current_;
  }

  bool operator!=(const ListIterator& other) const {
    return !(*this == other);
  }

private:
  Node<T>* current_;
};

template <typename T>
class ConstListIterator : public std::iterator<std::forward_iterator_tag, const T> {
public:
  using value_type = typename Node<T>::value_type;
  using reference = typename Node<T>::value_type&;
  using pointer = typename Node<T>::value_type*;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;

  ConstListIterator() : current_(nullptr) {}
  explicit ConstListIterator(const Node<T>* node) : current_(node) {}

  reference operator*() const {
    return current_->data;
  }

  pointer operator->() const {
    return &(current_->data);
  }

  ConstListIterator& operator++() {
    if (current_) {
      current_ = current_->next;
    }
    return *this;
  }

  ConstListIterator operator++(int) {
    ConstListIterator temp(*this);
    ++(*this);
    return temp;
  }

  bool operator==(const ConstListIterator& other) const {
    return current_ == other.current_;
  }

  bool operator!=(const ConstListIterator& other) const {
    return !(*this == other);
  }

private:
  const Node<T>* current_;
};

}

#endif
