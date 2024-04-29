#ifndef STACK_HPP
#define STACK_HPP

namespace sobolevsky
{
  template< typename T >
  class Stack
  {
  public:
    Stack();
    Stack(const Stack& rhs) noexcept;
    Stack(Stack&& rhs);
    ~Stack() = default;

    void push(T data);
    T top();
    void pop();
    bool empty();
    size_t size();
  private:
    class Node
    {
      friend class Stack< T >;
      T data;
      Node *last;
      Node(T data)
      {
        this->data = data;
        last = nullptr;
      }
    };

    Node *last;
    size_t size_;
  };
}

template< typename T >
sobolevsky::Stack< T >::Stack()
{
  last = nullptr;
  size_ = 0;
}

template< typename T >
sobolevsky::Stack< T >::Stack(const Stack& rhs) noexcept
{
  last = rhs.last;
  size_ = rhs.size_;
}

template< typename T >
sobolevsky::Stack< T >::Stack(Stack&& rhs)
{
  last(std::move(rhs.last));
  size_ = rhs.size_;
}

template< typename T >
void sobolevsky::Stack< T >::push(T data)
{
  Node *ptr = new Node(data);
  ptr->last = last;
  last = ptr;
  size_++;
}

template< typename T >
T sobolevsky::Stack< T >::top()
{
  if (last == nullptr)
  {
    throw std::logic_error("stack is empty");
  }
  return last->data;
}

template< typename T >
void sobolevsky::Stack< T >::pop()
{
  Node *tempNode = last;
  last = last->last;
  size_--;
  delete tempNode;
}

template< typename T >
bool sobolevsky::Stack< T >::empty()
{
  return (size_ == 0);
}

template< typename T >
size_t sobolevsky::Stack< T >::size()
{
  return size_;
}

#endif 
