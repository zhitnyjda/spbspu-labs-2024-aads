#include <iostream>
#include <algorithm>
#include <string>


namespace hohlova
{
  template < typename T >
  class List
  {
  public:
    List();
    ~List();
    void pop_front();
    void push_back(T data);
    void clear();
    int getSize() { return size; }
    T& operator[](const int index);
    void push_front(T data);
    void insert(T data, int index);
    void removeAt(int index);
    void pop_back();
  private:
    template < typename T >
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
    int size;
    Node<T>* head;
  };

  template<typename T>
  List<T>::List()
  {
    int size = 0;
    Node<T>* head = nullptr;
  }
  template<typename T>
  List<T>::~List()
  {
    clear();
  }

  template<typename T>
  void List<T>::pop_front()
  {
    Node<T>* temp = head;
    head = head->nextPoint;
    delete temp;
    size--;
  }

  template<typename T>
  void List<T>::push_back(T data)
  {
    if (head == nullptr)
    {
      head = new Node<T>(data);
    }
    else
    {
      Node<T>* currentPoint = this->head;

      while (currentPoint->nextPoint != nullptr)
      {
        currentPoint = currentPoint->nextPoint;
      }
      currentPoint->nextPoint = new Node<T>(data);

    }
    size++;
  }

  template<typename T>
  void List<T>::clear()
  {
    while (size)
    {
      pop_front();
    }
  }

  template<typename T>
  T& List<T>::operator[](const int index)
  {
    int count = 0;
    Node<T>* currentPoint = this->head;
    while (currentPoint != nullptr)
    {
      if (count == index)
      {
        return currentPoint->data;
      }
      currentPoint = currentPoint->nextPoint;
      count++;
    }
  }

  template<typename T>
  void List<T>::push_front(T data)
  {
    head = new Node<T>(data, head);
    size++;
  }

  template<typename T>
  void List<T>::insert(T data, int index)
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
      size++;
    }
  }

  template<typename T>
  void List<T>::removeAt(int index)
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
      size--;
    }
  }

  template<typename T>
  void List<T>::pop_back()
  {
    removeAt(size - 1);
  }
}
