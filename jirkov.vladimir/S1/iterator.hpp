#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cassert>
#include "node.hpp"

namespace jirkov {
    template <typename T>
    struct ListIterator {
        Node<T>* node;

        ListIterator() : node(nullptr) {}
        ListIterator(Node<T>* pointer) : node(pointer) {}

        ListIterator<T>& operator++() {
            assert(node && "Iterator points to null.");
            node = node->next;
            return *this;
        }

        ListIterator<T> operator++(int) {
            ListIterator<T> temp(*this);
            ++(*this);
            return temp;
        }

        T& operator*() {
            assert(node && "Iterator points to null.");
            return node->data;
        }

        T* operator->() {
            assert(node && "Iterator points to null.");
            return &(node->data);
        }

        bool operator!=(const ListIterator<T>& rhs) const {
            return node != rhs.node;
        }

        bool operator==(const ListIterator<T>& rhs) const {
            return node == rhs.node;
        }
    };
}

#endif
