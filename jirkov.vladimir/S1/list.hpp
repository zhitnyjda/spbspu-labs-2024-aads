#ifndef LIST_HPP
#define LIST_HPP

#include <cassert>
#include "node.hpp"
#include "iterator.hpp"

namespace jirkov {
    template <typename T>
    class List {
    public:
        List() : head_(nullptr) {}
        ~List() {
            clear();
        }

        void pushFront(const T& data) {
            Node<T>* newNode = new Node<T>(data);
            newNode->next = head_;
            head_ = newNode;
        }

        void popFront() {
            assert(!isEmpty() && "List is empty.");
            Node<T>* temp = head_;
            head_ = head_->next;
            delete temp;
        }

        bool isEmpty() {
            return head_ == nullptr;
        }

        void clear() {
            while (!isEmpty()) {
                popFront();
            }
        }

        ListIterator<T> begin() {
            return ListIterator<T>(head_);
        }

        ListIterator<T> end() {
            return ListIterator<T>(nullptr);
        }

    private:
        Node<T>* head_;
    };
}

#endif
