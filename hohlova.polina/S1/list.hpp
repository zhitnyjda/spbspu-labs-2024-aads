#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

namespace hohlova
{
  template <typename T>
  struct List
  {
  private:
    template <typename U>
    class Node
    {
    public:
      Node* nextPoint;
      T  data;
      Node(T data = T(), Node* nextPoint = nullptr)
      {
        this->data = data;
        this->nextPoint = nextPoint;
      }
    };
  public:
    List();
    ~List();
    void pop_front();
    void push_back(const T& value);
    void clear();
    size_t size() const;

    void push_front(const T& value);
    void insert(const T& value, int index);
    void removeAt(int index);
    void pop_back();

    class Iterator;
    class ConstIterator;

    friend std::ostream& operator<<(std::ostream& os, const List<T>& list)
    {
      std::vector<std::string> names;
      std::vector<std::vector<unsigned long long>> values;

      for (auto it = list.begin(); it != list.end(); ++it)
      {
        names.push_back((*it).first);
        values.push_back((*it).second);
      }

      size_t max_size = 0;
      for (const auto& v : values)
      {
        max_size = std::max(max_size, v.size());
      }
      for (size_t i = 0; i < max_size; ++i)
      {
        for (size_t j = 0; j < names.size(); ++j)
        {
          if (i < values[j].size())
          {
            os << values[j][i];
          }
          if ((j + 1 < names.size()) && (i < values[j + 1].size()) && (i + 1 < max_size))
          {
            os << " ";
          }
        }
        os << "\n";
      }
      return os;
    }

    Iterator begin() const;
    Iterator end() const;

    ConstIterator cBegin() const;
    ConstIterator cEnd() const;

  private:
    Node<T>* head;
    int Size = 0;
  };
}

template<typename T>
class hohlova::List<T>::Iterator: public std::iterator<std::forward_iterator_tag, T>
{
public:
  Iterator();
  Iterator(Node<T>* ptr);
  ~Iterator() = default;

  void operator++();

  T& operator*();
  T* operator->();

  bool operator!=(const Iterator& other);
  bool operator==(const Iterator& other);

private:
  Node<T>* ptr;
};

template< typename T >
hohlova::List<T>::Iterator::Iterator():
  ptr(nullptr)
{}

template< typename T >
hohlova::List<T>::Iterator::Iterator(Node<T>* ptr):
  ptr(ptr)
{}

template< typename T >
void hohlova::List<T>::Iterator::operator++()
{
  ptr = ptr->nextPoint;
}

template< typename T >
T& hohlova::List<T>::Iterator::operator*()
{
  return ptr->data;
}

template< typename T >
T* hohlova::List<T>::Iterator::operator->()
{
  return std::addressof(ptr->data);
}

template< typename T >
bool hohlova::List<T>::Iterator::operator!=(const Iterator& other)
{
  return ptr != other.ptr;
}

template< typename T >
bool hohlova::List<T>::Iterator::operator==(const Iterator& other)
{
  return ptr == other.ptr;
}

template<typename T>
class hohlova::List<T>::ConstIterator: public std::iterator<std::forward_iterator_tag, T>
{
public:
  ConstIterator();
  ConstIterator(Node<T>* ptr);
  ~ConstIterator() = default;

  void operator++();

  const T& operator*();
  const T* operator->();

  bool operator!=(const Iterator& other) const;
  bool operator==(const Iterator& other) const;

private:
  Node<T>* ptr;
};

template< typename T >
hohlova::List<T>::ConstIterator::ConstIterator():
  ptr(nullptr)
{}

template< typename T >
hohlova::List<T>::ConstIterator::ConstIterator(Node<T>* ptr) :
  ptr(ptr)
{}

template< typename T >
void hohlova::List<T>::ConstIterator::operator++()
{
  ptr = ptr->nextPoint;
}

template< typename T >
const T& hohlova::List<T>::ConstIterator::operator*()
{
  return ptr->data;
}

template< typename T >
const T* hohlova::List<T>::ConstIterator::operator->()
{
  return std::addressof(ptr->data);
}

template< typename T >
bool hohlova::List<T>::ConstIterator::operator!=(const Iterator& other) const
{
  return ptr != other.ptr;
}

template< typename T >
bool hohlova::List<T>::ConstIterator::operator==(const Iterator& other) const
{
  return ptr == other.ptr;
}

template <typename T>
hohlova::List<T>::List()
{
  Size = 0;
  head = nullptr;
}

template <typename T>
hohlova::List<T>::~List()
{
  clear();
}

template <typename T>
void hohlova::List<T>::pop_front()
{
  Node<T>* temp = head;
  head = head->nextPoint;
  delete temp;
  Size--;
}

template <typename T>
void hohlova::List<T>::push_back(const T& value)
{
  if (head == nullptr)
  {
    head = new Node<T>(value);
  }
  else
  {
    Node<T>* current = head;
    while (current->nextPoint != nullptr)
    {
      current = current->nextPoint;
    }
    current->nextPoint = new Node<T>(value);
  }
    Size++;
}

template <typename T>
void hohlova::List<T>::clear()
{
  while (Size)
  {
    pop_front();
  }
}

template <typename T>
size_t hohlova::List<T>::size() const
{
  return Size;
}

template <typename T>
void hohlova::List<T>::push_front(const T& value)
{
  head = new Node<T>(value, head);
  Size++;
}

template <typename T>
void hohlova::List<T>::insert(const T& value, int index)
{
  if (index == 0)
  {
    push_front(value);
  }
  else
  {
    Node<T>* prevPoint = this->head;
    for (int i = 0; i < index - 1; i++)
    {
      prevPoint = prevPoint->nextPoint;
    }
    Node<T>* newNode = new Node<T>(value, prevPoint->nextPoint);
    prevPoint->nextPoint = newNode;
    Size++;
  }
}

template <typename T>
void hohlova::List<T>::removeAt(int index)
{
  if (index == 0)
  {
    pop_front();
  }
  else
  {
    Node<T>* prevPoint = this->head;
    for (int i = 0; i < index - 1; i++)
    {
      prevPoint = prevPoint->nextPoint;
    }
    Node<T>* forDelete = prevPoint->nextPoint;
    prevPoint->nextPoint = forDelete->nextPoint;
    delete forDelete;
    Size--;
  }
}

template <typename T>
void hohlova::List<T>::pop_back()
{
  removeAt(Size - 1);
}

template <typename T>
typename hohlova::List<T>::Iterator hohlova::List<T>::begin() const
{
  return Iterator(head);
}

template <typename T>
typename hohlova::List<T>::Iterator hohlova::List<T>::end() const
{
  return Iterator(nullptr);
}

template <typename T>
typename hohlova::List<T>::ConstIterator hohlova::List<T>::cBegin() const
{
  return ConstIterator(head);
}

template <typename T>
typename hohlova::List<T>::ConstIterator hohlova::List<T>::cEnd() const
{
  return ConstIterator(nullptr);
}
#endif
