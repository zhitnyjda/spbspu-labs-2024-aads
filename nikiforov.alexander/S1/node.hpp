#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
struct Node
{
	T data;
	Node* pNext;

	Node(T data, Node* pNext = nullptr) : data(data), pNext(nullptr) {}

};

#endif 
