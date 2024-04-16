#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include "node.hpp"

namespace jirkov
{
    template<typename T>
    class List
    {
    public:
        class Iterator;
        class ConstIterator;

        List();
        ~List();
        void push_back(const T& value);
        void pop_back();
        void clear();
        size_t size();
        bool empty();

        class ConstIterator
        {
        public:
            ConstIterator();
            ConstIterator(const Node<T>* node);
            const T& operator*() const;
            ConstIterator& operator++();
            bool operator==(const ConstIterator& other) const;
            bool operator!=(const ConstIterator& other) const;

        private:
            const Node<T>* node;
        };

        class Iterator
        {
        public:
            Iterator();
            Iterator(Node<T>* node);
            T& operator*();
            Iterator& operator++();
            bool operator==(const Iterator& other) const;
            bool operator!=(const Iterator& other) const;

        private:
            Node<T>* node;
        };
    };

    template<typename T>
    List<T>::List() : head(nullptr), tail(nullptr) {}

    template<typename T>
    List<T>::~List()
    {
        clear();
    }

    template<typename T>
    void List<T>::push_back(const T& value)
    {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    template<typename T>
    void List<T>::pop_back()
    {
        if (tail != nullptr) {
            if (tail == head) {
                delete tail;
                head = nullptr;
                tail = nullptr;
            } else {
                Node<T>* prevNode = tail->prev;
                delete tail;
                tail = prevNode;
                tail->next = nullptr;
            }
        }
    }

    template<typename T>
    void List<T>::clear()
    {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }

    template<typename T>
    size_t List<T>::size()
    {
        size_t count = 0;
        Node<T>* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    template<typename T>
    bool List<T>::empty()
    {
        return head == nullptr;
    }

    template<typename T>
    List<T>::ConstIterator::ConstIterator() : node(nullptr) {}

    template<typename T>
    List<T>::ConstIterator::ConstIterator(const Node<T>* node) : node(node) {}

    template<typename T>
    const T& List<T>::ConstIterator::operator*() const
    {
        return node->data;
    }

    template<typename T>
    typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
    {
        node = node->next;
        return *this;
    }

    template<typename T>
    bool List<T>::ConstIterator::operator==(const ConstIterator& other) const
    {
        return node == other.node;
    }

    template<typename T>
    bool List<T>::ConstIterator::operator!=(const ConstIterator& other) const
    {
        return node != other.node;
    }

    template<typename T>
    List<T>::Iterator::Iterator() : node(nullptr) {}

    template<typename T>
    List<T>::Iterator::Iterator(Node<T>* node) : node(node) {}

    template<typename T>
    T& List<T>::Iterator::operator*()
    {
        return node->data;
    }

    template<typename T>
    typename List<T>::Iterator& List<T>::Iterator::operator++()
    {
        node = node->next;
        return *this;
    }

    template<typename T>
    bool List<T>::Iterator::operator==(const Iterator& other) const
    {
        return node == other.node;
    }

    template<typename T>
    bool List<T>::Iterator::operator!=(const Iterator& other) const
    {
        return node != other.node;
    }
}

#endif
