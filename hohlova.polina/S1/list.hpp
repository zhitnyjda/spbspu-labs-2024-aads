#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "node.hpp"

namespace hohlova
{
  template < typename T >
  struct List
  {
  public:
    List();
    ~List();
    void pop_front();
    void push_back(const std::vector<T>& nums);
    void clear();
    size_t size() const;

    const std::vector<T>& operator[](size_t index) const { return data[index]; }
    std::vector<T>& operator[](size_t index) { return data[index]; }

    void push_front(std::vector<std::vector<T>> data);
    void insert(std::vector<std::vector<T>> data, int index);
    void removeAt(int index);
    void pop_back();
  private:
    std::vector<std::vector<T>> data;
    int Size = 0;
    Node<T>* head;
  };
}

template< typename T >
hohlova::List<T>::List()
{
  int Size = 0;
  Node<T>* head = nullptr;
}

template< typename T >
hohlova::List<T>::~List()
{
  clear();
}

template< typename T >
void hohlova::List<T>::pop_front()
{
  Node<T>* temp = head;
  head = head->nextPoint;
  delete temp;
  Size--;
}

template< typename T >
void hohlova::List<T>::push_back(const std::vector<T>& nums)
{
  data.push_back(nums);
}

template< typename T >
void hohlova::List<T>::clear()
{
  while (Size)
  {
    pop_front();
  }
}

template < typename T >
size_t hohlova::List<T>::size() const
{
  return data.size();
}

template< typename T >
void hohlova::List<T>::push_front(std::vector<std::vector<T>> data)
{
  head = new Node<T>(data, head);
  Size++;
}

template< typename T >
void hohlova::List<T>::insert(std::vector<std::vector<T>> data, int index)
{
  if (index == 0)
  {
    push_front(data);
  }
  else
  {
    Node<T>* prevPoint = this->head;
    for (int i = 0; i < index - 1; i++)
    {
      prevPoint = prevPoint->nextPoint;
    }
    Node<T>* newNode = new Node<T>(data, prevPoint->nextPoint);
    prevPoint->nextPoint = newNode;
    Size++;
  }
}

template< typename T >
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

template< typename T >
void hohlova::List<T>::pop_back()
{
  removeAt(Size - 1);
}

#endif
