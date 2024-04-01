#ifndef LIST_H
#define LIST_H
#include <cassert>
#include <memory>

namespace taskaev
{
  template< typename T>
  class List
  {
  private:
    struct Node
    {
      T data;
      Node* next;
      Node(T value) : data(value), next(nullptr) {}
    };
    Node* head;
  public:
    class ConstIterator;
    class Iterator;

    List();
    ~List();
    List(const List<T> &other);
    List(List<T> && other);

    T& front() const;
    void pushFront(const T& data);
    void pushBack(const T& data);
    void popFront();
    void clear();
    bool empty() const;
    void swap(List<T>& other);
    void remove(const T& value);
    void reverse();
    void assign(const T& value);
    template <typename predicate>
    void remove_if(predicate p);

    Iterator begin() const {return Iterator(head); };
    Iterator end() const {return Iterator(); };

    ConstIterator cbegin() const {return ConstIterator(head); };
    ConstIterator cend() const {return ConstIterator(); };
  };

  template< typename T >
  class List<T>::ConstIterator
  {
  public:
    friend class List<T>;
    ConstIterator() : node(nullptr) {}
    ConstIterator(Node* value) : node(value) {}
    ~ConstIterator() = default;
    ConstIterator& operator++();
    ConstIterator operator++(int);
    const T& operator*() const;
    const T* operator->() const;
    bool operator==(const ConstIterator& rhs) const;
    bool operator!=(const ConstIterator& rhs) const;
  private:
    Node* node;
  };

  template<typename T>
  typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
  {
    assert(node != nullptr);
    node = node->next;
    return *this;
  }

  template<typename T>
  typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int)
  {
    assert(node != nullptr);
    ConstIterator result(*this);
    ++(*this);
    return result;
  }

  template<typename T>
  const T& List<T>::ConstIterator::operator*() const
  {
    assert(node != nullptr);
    return node->data;
  }

  template<typename T>
  const T* List<T>::ConstIterator::operator->() const
  {
    assert(node != nullptr);
    return std::addressof(node->data);
  }

  template<typename T>
  bool List<T>::ConstIterator::operator==(const ConstIterator& rhs) const
  {
    return node == rhs.node;
  }

  template<typename T>
  bool List<T>::ConstIterator::operator!=(const ConstIterator& rhs) const
  {
    return !(rhs == *this);
  }

  template< typename T >
  class List<T>::Iterator
  {
  public:
    friend class List<T>;
    Iterator() : node(nullptr) {}
    Iterator(Node* value) : node(value) {}
    ~Iterator() = default;
    Iterator& operator++();
    Iterator operator++(int);
    const T& operator*() const;
    const T* operator->() const;
    bool operator==(const Iterator& rhs) const;
    bool operator!=(const Iterator& rhs) const;
  private:
    Node* node;
  };

  template<typename T>
  typename List<T>::Iterator& List<T>::Iterator::operator++()
  {
    assert(node != nullptr);
    node = node->next;
    return *this;
  }

  template<typename T>
  typename List<T>::Iterator List<T>::Iterator::operator++(int)
  {
    assert(node != nullptr);
    Iterator result(*this);
    ++(*this);
    return result;
  }

  template<typename T>
  const T& List<T>::Iterator::operator*() const
  {
    assert(node != nullptr);
    return node->data;
  }

  template<typename T>
  const T* List<T>::Iterator::operator->() const
  {
    assert(node != nullptr);
    return std::addressof(node->data);
  }

  template<typename T>
  bool List<T>::Iterator::operator==(const Iterator& rhs) const
  {
    return node == rhs.node;
  }

  template<typename T>
  bool List<T>::Iterator::operator!=(const Iterator& rhs) const
  {
    return !(rhs == *this);
  }

  template <typename T>
  List<T>::List():head(nullptr){}

  template <typename T>
  List<T>::~List<T>()
  {
    clear();
  }

  template <typename T>
  List<T>::List(const List<T> &other):
    head(nullptr)
  {
    for (auto it : other)
    {
      pushBack(it);
    }
  }

  template <typename T>
  List<T>::List(List<T> &&other):
    head(other.head)
  {
    other.head = nullptr;
  }

  template <typename T>
  T& List<T>::front() const
  {
    return head->data;
  }

  template <typename T>
  void List<T>::pushFront(const T& data)
  {
    Node* node = new Node(data);
    node -> next = head;
    head = node;
  }

  template <typename T>
  void List<T>::pushBack(const T& data)
  {
    Node* node = new Node(data);
    if(empty())
    {
      head = node;
    }
    else
    {
      Node* temp = head;
      while(temp->next)
      {
        temp = temp->next;
      }
      temp->next = node;
    }
  }

  template <typename T>
  void List<T>::popFront()
  {
    if(head != nullptr)
    {
      Node* newNode = head;
      head = head->next;
      delete newNode;
    }
  }

  template <typename T>
  void List<T>::clear()
  {
    while (head) { popFront(); }
  }

  template <typename T>
  bool List<T>::empty() const {
    if(head == nullptr)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  template <typename T>
  void List<T>::swap(List<T>& other)
  {
    Node* temp = head;
    head = other->head;
    other->temp = head;
    delete temp;
  }

  template <typename T>
  void List<T>::remove(const T& value)
  {
    Node* node = head;
    Node* temp = nullptr;
    while(node != nullptr)
    {
      if(node->data == value)
      {
        if(temp == value) {head = node->next;}
        else {temp->next = node->next;}
        delete node;
        node = (temp == nullptr)? head : temp->next;
      }
      else
      {
        temp = node;
        node = node->next;
      }
    }
  }

  template <typename T>
  void List<T>::reverse()
  {
    Node* newNode = head;
    Node* temp = head->next;
    newNode->next = nullptr;
    while(temp)
    {
      Node* am = temp->next;
      temp->next = newNode;
      newNode = temp;
      temp = am;
    }
    head = newNode;
  }

  template <typename T>
  void List<T>::assign(const T& value)
  {
    Node* newNode = head;
    while(newNode != nullptr)
    {
      newNode->data = value;
      newNode = newNode->next;
    }
  }

  template <typename T>
  template<typename predicate>
  void List<T>::remove_if(predicate p)
  {
    Node* newNode = head;
    Node* temp = nullptr;
    while(newNode != nullptr)
    {
      if(p(newNode->data))
      {
        if(newNode == head)
        {
          head = newNode->next;
          delete newNode;
          newNode = head;
        }
        else
        {
          temp->next = newNode ->next;
          delete newNode;
          newNode = temp->next;
        }
      }
      else
      {
        temp = newNode;
        newNode = newNode->next;
      }
    }
  }

}
#endif
