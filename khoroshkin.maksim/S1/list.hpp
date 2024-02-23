#ifndef LIST_HPP
#define LIST_HPP

namespace khoroshkin
{
  template< typename T >
  class List
  {
  public:
    List();
    ~List() = default;

    void push_back(T data);
    void pop_front();
    void clear();
    int GetSize() {return Size;};
    T & operator[](const int index);

  private:
    template< typename S >
    class Node
    {
    public:
      S data;
      Node< S >  * pNext;

      Node(S data = S(), Node * pNext = nullptr)
      {
        this->data = data;
        this->pNext = pNext;
      }
    };

    int Size;
    Node< T > * head;
  };
}

template< typename T >
khoroshkin::List< T >::List()
{
  Size = 0;
  head = nullptr;
}

template< typename T >
void khoroshkin::List< T >::push_back(T data)
{
  if (head == nullptr)
  {
      head = new Node< T >(data);
  }
  else
  {
    Node< T > * current = this->head;
    while (current->pNext != nullptr)
    {
      current = current->pNext;
    }
    current->pNext = new Node< T >(data);
  }
  Size++;
}

template< typename T >
T & khoroshkin::List< T >::operator[](const int index)
{
  int counter = 0;
  Node< T > * current = this->head;
  while (current != nullptr)
  {
    if (counter == index)
    {
      return current->data;
    }
    current = current->pNext;
    counter++;
  }
}

template < typename T >
void khoroshkin::List< T >::pop_front()
{
  Node< T > * temp = head;
  head = head->pNext;
  delete temp;
  Size--;
}

template < typename T >
void khoroshkin::List< T >::clear()
{
  while (Size)
  {
    pop_front();
  }
}

#endif
