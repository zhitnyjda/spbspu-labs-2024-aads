#ifndef NODE_HPP
#define NODE_HPP
namespace Panov
{
  template< typename T >
  struct Node
  {
  public:
    Node();
    Node(T data);
    ~Node() = default;
    T data_;
    Node* prev_;
    Node* next_;
  };
}
#endif
