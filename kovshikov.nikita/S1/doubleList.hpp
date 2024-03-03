#ifndef DOUBLELIST_HPP
#define DOUBLELIST_HPP
#include "node.hpp"
#include <cstddef>
#include <utility>

namespace kovshikov
{
	template <typename T>
	class DoubleList
	{
	public:
		DoubleList() : head_(nullptr), tail_(nullptr), size_(0) {};
		//DoubleList(Node<T>* head = nullptr, Node<T>* tail = nullptr, size_t size = 0) : head_(head), tail_(tail), size_(size) {}; //?? почему пишет что это конструктор по умолчанию?? когда это пользовательский
		DoubleList(const DoubleList& dl);
		DoubleList<T>& operator=(const DoubleList& dl);
		DoubleList<T>& operator=(DoubleList&& dl); //???
		DoubleList(DoubleList&& dl); //???
		~DoubleList(); //используется динамическая память, нужно прописать деструктор

    T& front() const; //work
		T& back() const;  //work

		bool empty() const; //work

		void pushFront(const T &value); //work
		void pushBack(const T& value); //work
		void popFront();  //work
		void popBack(); //work
		void clear();
		void swap(DoubleList& dl); //work

	private:
		Node<T>* head_;
		Node<T>* tail_;
		size_t size_; //а надо ли?

	};

	template <typename T>
	DoubleList<T>::~DoubleList()
	{
		clear();
	}

	template <typename T>
	DoubleList<T>::DoubleList(const DoubleList& dl)
	{
		this->head_ = dl.head_;
		this->tail_ = dl.tail_;
		this->size_ = dl.size_;
	}
	
	template <typename T>
	DoubleList<T>& DoubleList<T>::operator=(const DoubleList& dl)
	{
		DoubleList<T> newDl = DoubleList<T>(dl);
		return newDl;
	}

	template <typename T>
	DoubleList<T>::DoubleList(DoubleList&& dl)
	{
		this->head_ = dl.head_;
		this->tail_ = dl.tail_;
		this->size_ = std::move(dl.size_);
	}

	template<typename T>
	DoubleList<T>& DoubleList<T>::operator=(DoubleList&& dl)
	{
		// TODO: вставьте здесь оператор return
	}

    template <typename T>
	T& DoubleList<T>::front() const
	{
		return head_->data;  //&head_->data;
	}

	template <typename T>
	T& DoubleList<T>::back() const
	{
	  return tail_->data;
	}

	template <typename T>
	bool DoubleList<T>::empty() const
	{
		if (head_ == nullptr && tail_ == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	void DoubleList<T>::pushFront(const T &value)
	{
		Node<T>* newNode = new Node<T>(value); // генерация исключения?
		if (this->empty() == true)
		{
			head_ = newNode;
			tail_ = newNode;
		}
		newNode->next = head_;
		head_ = newNode;
	}

	template <typename T>
	void DoubleList<T>::pushBack(const T& value)
	{
		Node<T>* newNode = new Node<T>(value); //генерация исключения??
		if (this->empty() == true)
		{
			head_ = newNode;
			tail_ = newNode;
		}
		newNode->prev = tail_;
		tail_ = newNode;
		size_ += 1;
	}

	template <typename T>
	void DoubleList<T>::popFront()
	{
		Node<T>* temp = head_->next;
		delete head_;
		head_ = temp;
	}
	
	template <typename T>
	void DoubleList<T>::popBack()
	{
		Node<T>* temp = tail_->prev;
		delete tail_;
		tail_ = temp;
	}

	template <typename T>
	void DoubleList<T>::clear()
	{
		while (head_)
		{
			popFront();
		}
	}

	template <typename T>
	void DoubleList<T>::swap(DoubleList& dl)
	{
		Node<T>* tempHead = dl.head_;
		Node<T>* tempTail = dl.tail_;
		dl.head_ = this->head_;
		this->head_ = tempHead;
		dl.tail_ = this->tail_;
		this->tail_ = tempTail;
		tempHead = nullptr; // а надо ли если объект все равно уничтожится
		tempTail = nullptr;
	}



}

#endif

