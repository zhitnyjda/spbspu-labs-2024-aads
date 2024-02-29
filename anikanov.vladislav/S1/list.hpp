#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"
#include "iterator.hpp"
#include <memory>

namespace anikanov {

  template<typename T>
  class List {
  public:
    List();
    ~List();

    void push_back(const T &value);
    bool empty();
    size_t size() const;
    Iterator< T > back();

    Iterator< T > begin() const;

    Iterator< T > end() const;

  private:
    std::shared_ptr< Node< T>> head, tail;
    size_t list_size;
  };

  template<typename T>
  size_t List< T >::size() const
  {
    return list_size;
  }

  template<typename T>
  List< T >::List() : head(nullptr), tail(nullptr), list_size(0)
  {
  }

  template<typename T>
  List< T >::~List()
  {
    while (head) {
      head = head->next;
    }
  }


  template<typename T>
  void List< T >::push_back(const T &value)
  {
    auto newNode = std::make_shared< Node< T>>(value);
    if (head == nullptr) {
      head = newNode;
      tail = newNode;
    } else {
      tail->next = newNode;
      tail = newNode;
    }
    list_size++;
  }

  template<typename T>
  bool List< T >::empty()
  {
    if (head == tail) {
      return true;
    }
    return false;
  }

  template<typename T>
  Iterator< T > List< T >::back()
  {
    return Iterator< T >(tail);
  }

  template<typename T>
  Iterator< T > List< T >::begin() const
  {
    return Iterator< T >(head);
  }

  template<typename T>
  Iterator< T > List< T >::end() const
  {
    return Iterator< T >(nullptr);
  }
}

#endif
