#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <cassert>
#include <memory>
#include <initializer_list>

namespace sukacheva {
  template < typename  T >
  class List
  {
  public:

    struct Node
    {
    public:
      friend class List;
      Node(T data_) : data(data_), next(nullptr) {}
    private:
      T data;
      Node* next;
    };

    class Iterator;
    class ConstIterator;

    List() : head(nullptr), tail(nullptr), listSize(0) {}
    List(size_t count, const T& value);
    List(std::initializer_list<T> init);
    template< class InputIt >
    List(InputIt first, InputIt last);
    ~List();
    List(const List&);
    List(List&& other);

    Node* operator[](size_t index);

    void pushFront(const T& data);
    void pushBack(const T& data);
    void popFront();
    void clean() noexcept;
    void swap(List& other) noexcept;
    bool empty() noexcept;
    T& front() noexcept;
    T& back() noexcept;
    size_t getSize() noexcept;
    void reverse();
    void remove(const T& value);
    template< class UnaryPredicate >
    void remove_if(UnaryPredicate p);
    void assign(size_t count, const T& value);
    template< class InputIt >
    void assign(InputIt first, InputIt last);
    void assign(std::initializer_list<T> ilist);
    void splice(Iterator position, List& fwdlst);
    ConstIterator insert(ConstIterator position, const T& val);
    Iterator erase_after(ConstIterator pos);

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }

    ConstIterator cbegin() const { return head; }
    ConstIterator cend() const { return nullptr; }

  private:
    Node* head;
    Node* tail;
    size_t listSize;
  };

  template < typename T >
  class List< T >::Iterator
  {
  public:
    friend class List;
    Iterator(Node* node_) : node(node_) {}
    ~Iterator() = default;
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;

    Iterator& operator++();
    Iterator operator++(int);

    T& operator*();
    T* operator->();

    bool operator!=(const Iterator&) const;
    bool operator==(const Iterator&) const;
  private:
    Node* node;
  };

  template <typename T>
  class List< T >::ConstIterator {
  public:
    friend class List;
    ConstIterator(Node* node_) : node(node_) {}
    ~ConstIterator() = default;
    ConstIterator(const ConstIterator&) = default;
    ConstIterator& operator=(const ConstIterator&) = default;

    ConstIterator& operator++();
    ConstIterator operator++(int);

    bool operator!=(const ConstIterator& rhs) const;
    bool operator==(const ConstIterator& rhs) const;
  private:
    Node* node;
  };

}
  template< typename T >
  size_t sukacheva::List<T>::getSize() noexcept
  {
    return listSize;
  }

  template< typename T >
  T& sukacheva::List<T>::back() noexcept
  {
    return tail->data;
  }

  template< typename T >
  typename sukacheva::List<T>::Iterator sukacheva::List<T>::erase_after(ConstIterator pos)
  {
    Node* node = pos.node->next;
    Iterator it = node->next;
    pos.node->next = node->next;
    node->next = nullptr;
    return it;
  }

  template< typename T >
  typename sukacheva::List<T>::ConstIterator sukacheva::List<T>::insert(ConstIterator position, const T& val)
  {
    Node * node = new Node(val);
    ConstIterator constIt = node;
    node->next = position.node->next;
    position.node->next = node;
    return constIt++;
  }

  template< typename T >
  void sukacheva::List<T>::splice(Iterator position, List& fwdlst)
  {
    while (position.node)
    {
      insert(position, position.node->data);
    }
  }

  template< typename T >
  void sukacheva::List<T>::assign(std::initializer_list<T> ilist)
  {
    clean();
    Iterator it = ilist.begin();
    while (it) {
      pushBack(it.node->data);
      it++;
    }
  }

  template< typename T >
  template< typename InputIt>
  void sukacheva::List<T>::assign(InputIt first, InputIt last)
  {
    clean();
    while (first != last) {
      pushBack(first);
      first++;
    }
  }

  template< typename T >
  void sukacheva::List<T>::assign(size_t count, const T& value)
  {
    clean();
    for (size_t i = 0; i != count; ++i) {
      pushBack(value);
    }
  }

  template< typename T >
  template< typename UnaryPredicate>
  void sukacheva::List<T>::remove_if(UnaryPredicate p)
  {
    size_t index = 0;
    Iterator it = begin();
    while (it.node)
    {
      if (p) {
        if (it == begin()) {
          it++;
          head = this->operator[](index + 1);
          listSize--;
        }
        else {
          it++;
          this->operator[](index - 1)->next = this->operator[](index + 1);
          listSize--;
        }
      }
      else {
        index++;
        it++;
      }
    }
  }

  template< typename T >
  void sukacheva::List<T>::remove(const T& value)
  {
    size_t index = 0;
    Iterator it = begin();
    while (it.node)
    {
      if (*it == value) {
        if (it == begin()) {
          it++;
          head = this->operator[](index + 1);
          listSize--;
        }
        else {
          it++;
          this->operator[](index - 1)->next = this->operator[](index + 1);
          listSize--;
        }
      }
      else {
        index++;
        it++;
      }
    }
  }

  template< typename T >
  void sukacheva::List<T>::reverse()
  {
    size_t tempSize = listSize;
    for (size_t i = tempSize - 1; i != -1; i--)
    {
      pushBack(this->operator[](i)->data);
    }
    for (size_t i = 0; i != tempSize; i++)
    {
      popFront();
    }
  }

  template< typename T >
  T& sukacheva::List<T>::front() noexcept
  {
    return head->data;
  }

  template< typename T >
  typename sukacheva::List< T >::Node* sukacheva::List<T>::operator[](size_t index)
  {
    Iterator it = begin();
    for (size_t i = 0; i != index; i++) {
      if (it == nullptr) {
        return nullptr;
      }
      it++;
    }
    return it.node;
  }

  template< typename T >
  void sukacheva::List<T>::pushBack(const T& data)
  {
    Node* newNode = new Node(data);
    if (empty()) {
      head = newNode;
      tail = newNode;
    }
    else {
      tail->next = newNode;
      tail = newNode;
    }
    listSize++;
  }

  template< typename T >
  void sukacheva::List<T>::pushFront(const T& data)
  {
    Node* newNode = new Node(data);
    if (empty()) {
      head = newNode;
      tail = newNode;
    }
    else {
      newNode->next = head;
      head = newNode;
    }
    listSize++;
  }

  template< typename T >
  void sukacheva::List<T>::popFront() {
    Node* front = head;
    Iterator it = begin();
    if (it != nullptr)
    {
      head = front->next;
    }
    else {
      head = nullptr;
      tail = nullptr;
    }
    delete front;
    listSize--;
  }

  template< typename T >
  bool sukacheva::List<T>::empty() noexcept
  {
    return (head == nullptr);
  }

  template< typename T >
  void sukacheva::List<T>::clean() noexcept
  {
    while (head)
    {
      popFront();
    }
  }

  template< typename T >
  void sukacheva::List<T>::swap(List& other) noexcept
  {
    Node* temp_head = head;
    Node* temp_tail = tail;
    size_t tempSize = other.listSize;
    other.listSize = listSize;
    listSize = tempSize;
    head = other.head;
    tail = other.tail;
    other.head = temp_head;
    other.tail = temp_tail;
    delete temp_head;
    delete temp_tail;
  }

  template< typename T >
  sukacheva::List<T>::~List()
  {
    clean();
  }

  template< typename T >
  sukacheva::List<T>::List(const List&) :
    head(nullptr),
    tail(nullptr),
    listSize(0)
  {
    Iterator it = begin();
    while (it.node) {
      this->pushBack(it.node->data);
      ++it;
    }
  }

  template< typename T >
  sukacheva::List<T>::List(List&& other):
    head(other.head),
    tail(other.tail),
    listSize(other.listSize)
  {
    other.head = nullptr;
    other.tail = nullptr;
    other.listSize = 0;
  }

  template< typename T >
  sukacheva::List<T>::List(size_t count, const T& value) : List()
  {
    for (size_t i = 0; i != count; ++i) {
      pushBack(value);
    }
  }

  template<class T>
  sukacheva::List<T>::List(std::initializer_list<T> init) : List()
  {
    Iterator it = init.begin();
    while (it) {
      pushBack(it.node->data);
      it++;
    }
  }

  template< typename T >
  template< typename InputIt >
  sukacheva::List<T>::List(InputIt first, InputIt last) : List()
  {
    while (first != last) {
      pushBack(first);
      first++;
    }
  }

  template<typename T>
  typename sukacheva::List<T>::ConstIterator& sukacheva::List<T>::ConstIterator::operator++()
  {
    node = node->next;
    return *this;
  }

  template<typename T>
  typename sukacheva::List<T>::ConstIterator sukacheva::List<T>::ConstIterator::operator++(int)
  {
    ConstIterator result(*this);
    ++(*this);
    return result;
  }

  template< typename T >
  bool sukacheva::List<T>::ConstIterator::operator==(const ConstIterator& rhs) const {
    return node == rhs.node;
  }

  template< typename T >
  bool sukacheva::List<T>::ConstIterator::operator!=(const ConstIterator& rhs) const {
    return !(rhs == *this);
  }

  template< typename T >
  typename sukacheva::List<T>::Iterator& sukacheva::List<T>::Iterator::operator++()
  {
    node = node->next;
    return *this;
  }

  template< typename T >
  typename sukacheva::List<T>::Iterator sukacheva::List<T>::Iterator::operator++(int) {
    Iterator result(*this);
    ++(*this);
    return result;
  }

  template< typename T >
  bool sukacheva::List<T>::Iterator::operator==(const Iterator& rhs) const {
    return node == rhs.node;
  }

  template< typename T >
  bool sukacheva::List<T>::Iterator::operator!=(const Iterator& rhs) const {
    return !(rhs == *this);
  }

  template< typename T >
  T& sukacheva::List<T>::Iterator::operator*()
  {
    assert(node != nullptr);
    return node->data;
  }

  template< typename T >
  T* sukacheva::List<T>::Iterator::operator->() {
    assert(node != nullptr);
    return std::addressof(node->data);
  }

#endif
