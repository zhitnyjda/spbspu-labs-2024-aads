#ifndef NODE_HPP
#define NODE_HPP
namespace litsinger
{
  template< typename T >
  struct Node
  {
  public:
    Node();
    Node(T data);
    ~Node() = default;
    T data_;
    Node* prev;
    Node* next;
  };
}
#endif
