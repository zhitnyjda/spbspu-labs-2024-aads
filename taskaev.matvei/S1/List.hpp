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
    class Iterator;

    List();
    ~List();
    List(const List&) = default;
    List(List&&) = default;

    T& front() const;
    void pushFront(const T& data);
    void pushBack(const T& data);
    void popFront();
    void clear();
    bool empty() const;
    void swap(List<T>& other);
    void remove(const T& value);
    void reverse();

    Iterator begin() const {return Iterator(head); };
    Iterator end() const  { return Iterator(); };
  };

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

}
#endif
