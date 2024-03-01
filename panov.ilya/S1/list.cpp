#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include "iterator.hpp"
namespace Panov {
  template<typename T>
  class List {
    using iterator = Iterator<T>;
    using constIterator = Iterator<const T>;
  public:
    List();
    List(size_t n, const T& data);
    List(const List<T>& other);
    List(List<T>&& other);
    ~List();
    List<T>& operator=(const List<T>& other);
    List<T>& operator=(List<T>&& other);
    iterator begin();
    constIterator cbegin() const;
    iterator end();
    constIterator cend() const;
    T& front();
    T& back();
    size_t size() const

  private:
    Node <T>* head_;
    Node <T>* tail_;
    size_t size_;
  };

  template<typename T>
  Node<T>::Node() :
    data_(T()),
    prev_(nullptr),
    next_(nullptr) {}

  template<typename T>
  Node<T>::Node(T data) :
    data_(data),
    prev_(nullptr),
    next_(nullptr) {}

  template<typename T>
  List<T>::List() :
    head_(new Node <T>),
    tail_(nullptr),
    size_(0) {}

  template<typename T>
  List<T>::List(size_t n, const T& data) :
    head_(new Node <T>),
    tail_(nullptr),
    size_(n) {
    for (size_t i = 0; i != n; ++i) {
      push_front(data);
    }
  }

  template<typename T>
  List<T>::List(const List<T>& other) :
    head_(new Node <T>),
    tail_(nullptr),
    size_(0) {
    Node <T>* node = other.head_;
    for (size_t i = 0; i != other.size_; ++i) {
      push_back(node->data_);
      node = node->next_;
    }
  }
}
#endif
