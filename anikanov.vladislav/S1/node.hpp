#ifndef NODE_HPP
#define NODE_HPP

#include <memory>

namespace anikanov {

  template<typename T>
  struct Node {
    T data;
    std::shared_ptr< Node< T > > next;

    explicit Node(T val) : data(val), next(nullptr)
    {
    }

    Node(const Node &other) : data(other.data), next(other.next)
    {
    }
  };

}


#endif
