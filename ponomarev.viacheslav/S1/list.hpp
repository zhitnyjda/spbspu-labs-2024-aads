#ifndef LIST_HPP
#define LIST_HPP

namespace ponomarev
{
  template< typename T >
  class List
  {
    private:
      struct Node
      {
        public:
          T data;
          Node * prev = nullptr;
          Node * next = nullptr;
          Node(T data)
          {
            this->data = data;
          }
      };

      Node * head = nullptr;
      Node * tail = nullptr;
  };
}
