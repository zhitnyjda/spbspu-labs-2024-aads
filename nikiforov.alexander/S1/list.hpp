#ifndef LIST_HPP
#define LIST_HPP
#include "node.hpp"

template <typename T>
class List
{
public:
	List();
	~List();

	void push_back(T data);
	void pop_front();
	void pop_back();
	bool is_empty();

private:

	Node<T>* head;
	size_t size_l;
};


template<typename T>
List<T>::List()
{
	head = nullptr;
	size_l = 0;
}

template<typename T>
List<T>::~List()
{
}

template<typename T>
void List<T>::push_back(T data)
{
	Node<T>* nd = new Node<T>(data);
	if (head == nullptr)
	{
		head = nd;
	}
	else
	{
		Node<T>* actual = head;
		while (actual->pNext != nullptr)
		{
			actual = actual->pNext;
		}
		actual->pNext = nd;
	}
	++size_l;
}

template<typename T>
void List<T>::pop_front()
{
	Node<T>* actual = head;
	head = head->pNext;
	delete actual;
	size_l--;
}

template<typename T>
void List<T>::pop_back()
{
	Node<T>* actual = head;
	for (size_t i = 0; i < size_l; i++)
	{
		actual = actual->pNext;
	}
	delete actual;

}

template<typename T>
bool List<T>::is_empty()
{
	if (head == nullptr)
	{
		return true;
	}
	return false;
}

#endif 
