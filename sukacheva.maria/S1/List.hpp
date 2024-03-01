#ifndef LIST_HPP
#define LIST_HPP

#include "ListIterator.hpp"

namespace sukacheva {
  template <class T>
  struct List
  {
	Node< T >* head;
	Node< T >* tail;

	using iterator = Iterator< T >;
	using const_iterator = Iterator< const T >;

	List() : head(nullptr), tail(nullptr){}
	~List();
	List(const List&) = default;
	List(List&&) = default;

	void pushFront(const T& data);
	void pushBack(const T& data);
	void popFront();
	void clean();
	void swap(List& other);
	bool empty();
	void printList();

	iterator begin() { return iterator(head); }
	iterator end() { return iterator(nullptr); }

	const_iterator cbegin() const { return head; }
	const_iterator cend() const { return nullptr; }
  };

  template<class T>
  void List<T>::printList()
  {
	Iterator< T > it = begin();
	do {
	  std::cout << it.node->data << " ";
	  it++;
	} while (it != tail);
	std::cout << it.node->data << " ";
  }

  template<class T>
  void sukacheva::List<T>::pushBack(const T& data)
  {
	Node< T >* newNode = new Node< T >(data);
	if (empty()) {
	  head = newNode;
	  tail = newNode;
	}
	else {
	  tail->next = newNode;
	  tail = newNode;
	}
  }

  template< class T>
  void List<T>::pushFront(const T& data) {
	Node< T >* newNode = new Node< T >(data);
	if (empty()) {
	  head = newNode;
	  tail = newNode;
	}
	else {
	  newNode->next = head;
	  head = newNode;
	}
	
  }

  template< class T>
  void List<T>::popFront() {
	Node< T >* front = head;
	if (front->next != nullptr) {
	  head = front->next;
	}
	else {
	  head = nullptr;
	  tail = nullptr;
	}
	delete front;
  }

  template< class T>
  bool List<T>::empty() {
	return (head == nullptr);
  }

  template< class T>
  void List<T>::clean() {
	while (head)
	{
	  popFront();
	}
  }

  template< class T>
  void List<T>::swap(List& other) {
	Node< T >* temp_head = head;
	Node< T >* temp_tail = tail;
	head = other.head;
	tail = other.tail;
	other.head = temp_head;
	other.tail = temp_tail;
	delete temp_head;
	delete temp_tail;
  }

  template< class T>
  List<T>::~List() {
	clean();
  }
}

#endif