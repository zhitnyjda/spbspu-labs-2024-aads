#ifndef NODE_HPP
#define NODE_HPP

namespace kovshikov
{
	template <typename T>
	struct Node
	{
		T data;
		Node* prev;
		Node* next;
		Node() : data(0), prev(nullptr), next(nullptr) {};
		Node(T existentData = 0, Node* existentPrev = nullptr, Node* existentNext = nullptr): 
		data(existentData), 
		prev(existentPrev), 
		next(existentNext) 
		{};
		~Node() = default; 
	};
}

#endif
