#ifndef NODE_HPP
#define NODE_HPP

namespace jirkov {

    template<typename T>
    struct Node {
        T value;
        Node* next;

        Node(const T& value) : value(value), next(nullptr) {}
    };

} // namespace jirkov

#endif

// list.hpp
#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include "node.hpp"

namespace jirkov {
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
            ConstIterator(const Node<T>* node) : current(node) {}
            // реализация операторов ++, --, *, == и != может быть добавлена
        private:
            const Node<T>* current;
        };

    private:
        Node<T>* head;
        Node<T>* tail;
        size_t listSize;
    };

    template<typename T>
    List<T>::List() : head(nullptr), tail(nullptr), listSize(0) {}

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
        } else {
            tail->next = newNode;
        }
        tail = newNode;
        ++listSize;
    }

    template<typename T>
    void List<T>::pop_back()
    {
        if (head == nullptr) {
            return;
        }
        if (head == tail) {
            delete tail;
            head = nullptr;
            tail = nullptr;
        } else {
            Node<T>* current = head;
            while (current->next != tail) {
                current = current->next;
            }
            delete tail;
            tail = current;
            tail->next = nullptr;
        }
        --listSize;
    }

    template<typename T>
    void List<T>::clear()
    {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        listSize = 0;
    }

    template<typename T>
    size_t List<T>::size()
    {
        return listSize;
    }

    template<typename T>
    bool List<T>::empty()
    {
        return listSize == 0;
    }

}

#endif
