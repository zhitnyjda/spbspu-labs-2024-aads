#ifndef LIST_H
#define LIST_H

#include <memory>
#include <iostream>
#include <stdexcept>

template< typename T >
class List {
private:
  struct Node {
    T data;
    std::shared_ptr< Node > next;

    Node(const T &data, std::shared_ptr< Node > next = nullptr) : data(data), next(next) {}
  };

  std::shared_ptr< Node > head;

public:
  class Iterator;

  class ConstIterator;

public:
  List();

  List(size_t count, const T &value);

  List(std::initializer_list< T > init);

  List(const List &other);

  List(List &&other) noexcept;

  List &operator=(const List &other);

  T &operator[](size_t index);

  template< typename Predicate >
  void remove_if(Predicate pred);

  void push_front(const T &data);

  void push_back(const T &data);

  void pop() noexcept;

  void clear() noexcept;

  void swap(List &other) noexcept;

  void splice(List< T > &other) noexcept;

  void reverse() noexcept;

  void insert(size_t index, const T &value) noexcept;

  void erase(const T &value) noexcept;

  size_t size() const;

  bool empty() const noexcept;

  Iterator begin();

  Iterator end();

  ConstIterator begin() const;

  ConstIterator end() const;

  ~List();
};

template< typename T >
class List< T >::Iterator {
  friend class List< T >;

private:
  std::shared_ptr< Node > node;
public:
  Iterator(std::shared_ptr< Node > node) : node(node) {}

  T &operator*() const {
    return node->data;
  }

  T *operator->() {
    return &node->data;
  }

  Iterator &operator++() {
    node = node->next;
    return *this;
  }

  Iterator operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
  }

  Iterator operator+(int n) const {
    Iterator temp = *this;
    while (n-- > 0 && temp.node != nullptr) {
      temp.node = temp.node->next;
    }
    return temp;
  }

  Iterator &operator+=(int n) {
    for (int i = 0; i < n && node != nullptr; i++) {
      node = node->next;
    }
    return *this;
  }

  bool operator==(const Iterator &other) const { return node == other.node; }

  bool operator!=(const Iterator &other) const { return node != other.node; }
};

template< typename T >
typename List< T >::Iterator List< T >::begin() {
  return Iterator(head);
}

template< typename T >
typename List< T >::Iterator List< T >::end() {
  return Iterator(nullptr);
}

template< typename T >
class List< T >::ConstIterator {
  friend class List< T >;

private:
  std::shared_ptr< const Node > node;
public:
  ConstIterator(std::shared_ptr< const Node > node) : node(node) {}

  const T &operator*() const {
    return node->data;
  }

  const T *operator->() {
    return &node->data;
  }

  ConstIterator &operator++() {
    node = node->next;
    return *this;
  }

  ConstIterator operator++(int) {
    ConstIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  ConstIterator operator+(int n) const {
    ConstIterator temp = *this;
    while (n-- > 0 && temp.node != nullptr) {
      temp.node = temp.node->next;
    }
    return temp;
  }

  ConstIterator &operator+=(int n) {
    ConstIterator temp = *this;
    for (int i = 0; i < n && node != nullptr; i++) {
      temp.node = temp.node->next;
    }
    return temp;
  }

  bool operator==(const ConstIterator &other) const { return node == other.node; }

  bool operator!=(const ConstIterator &other) const { return node != other.node; }
};

template< typename T >
typename List< T >::ConstIterator List< T >::end() const {
  return ConstIterator(nullptr);
}

template< typename T >
typename List< T >::ConstIterator List< T >::begin() const {
  return ConstIterator(head);
}

template< typename T >
List< T >::List() : head(nullptr) {}

template< typename T >
List< T >::~List() {
  clear();
}

template< typename T >
List< T >::List(size_t count, const T &value) : head(nullptr) {
  for (size_t i = 0; i < count; ++i) {
    push_back(value);
  }
}

template< typename T >
List< T >::List(std::initializer_list< T > init) : head(nullptr) {
  for (const T &value: init) {
    push_back(value);
  }
}

template< typename T >
List< T >::List(const List &other) : head(nullptr) {
  for (auto node = other.head; node != nullptr; node = node->next) {
    push_back(node->data);
  }
}

template< typename T >
List< T > &List< T >::operator=(const List &other) {
  swap(other);
  return *this;
}

template< typename T >
void List< T >::swap(List &other) noexcept {
  std::swap(head, other.head);
}

template< typename T >
void List< T >::push_front(const T &data) {
  head = std::make_shared< Node >(data, head);
}

template< typename T >
void List< T >::push_back(const T &data) {
  auto newNode = std::make_shared< Node >(data);
  if (!head) {
    head = newNode;
  } else {
    auto current = head;
    while (current->next) {
      current = current->next;
    }
    current->next = newNode;
  }
}

template< typename T >
void List< T >::pop() noexcept {
  if (head != nullptr) {
    head = head->next;
  }
}

template< typename T >
void List< T >::clear() noexcept {
  head = nullptr;
}

template< typename T >
void List< T >::splice(List< T > &other) noexcept {
  if (other.head == nullptr) {
    return;
  }

  if (head == nullptr) {
    head = other.head;
  } else {
    auto current = head;
    while (current->next != nullptr) {
      current = current->next;
    }
    current->next = other.head;
  }
  other.head = nullptr;
}

template< typename T >
void List< T >::reverse() noexcept {
  std::shared_ptr< Node > prev = nullptr, current = head, next = nullptr;
  while (current != nullptr) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  head = prev;
}

template< typename T >
template< typename Predicate >
void List< T >::remove_if(Predicate pred) {
  std::shared_ptr< Node > current = head;
  std::shared_ptr< Node > prev = nullptr;

  while (current != nullptr) {
    if (pred(current->data)) {
      if (prev) {
        prev->next = current->next;
      } else {
        head = current->next;
      }
      current = current->next;
    } else {
      prev = current;
      current = current->next;
    }
  }
}

template< typename T >
size_t List< T >::size() const {
  size_t count = 0;
  auto node = head;
  while (node != nullptr) {
    count++;
    node = node->next;
  }
  return count;
}

template< typename T >
bool List< T >::empty() const noexcept {
  return head == nullptr;
}

template< typename T >
void List< T >::insert(size_t index, const T &value) noexcept {
  if (index == 0 || !head) {
    head = std::make_shared< Node >(value, head);
    return;
  }

  auto current = head;
  size_t currentIndex = 0;
  while (current->next && currentIndex < index - 1) {
    current = current->next;
    ++currentIndex;
  }
  current->next = std::make_shared< Node >(value, current->next);
}

template< typename T >
void List< T >::erase(const T &value) noexcept {
  while (head && head->data == value) {
    head = head->next;
  }
  auto current = head;
  while (current && current->next) {
    if (current->next->data == value) {
      current->next = current->next->next;
    } else {
      current = current->next;
    }
  }
}

template< typename T >
T &List< T >::operator[](size_t index) {
  auto current = head;
  for (size_t i = 0; i < index; ++i) {
    if (!current) throw std::out_of_range("Index is out of range.");
    current = current->next;
  }
  return current->data;
}

#endif