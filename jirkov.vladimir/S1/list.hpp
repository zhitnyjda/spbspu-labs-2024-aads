#ifndef LIST_HPP
#define LIST_HPP

#include "iterator.hpp"
#include "node.hpp"

template <typename T>
class List {
public:
    List() : head(nullptr), tail(nullptr), size(0) {}

    ~List() {
        clear();
    }

    void push_back(const T& value) {
        Node<T>* newNode = new Node<T>(value);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        size++;
    }

    void pop_back() {
        if (head == nullptr) {
            return;
        }

        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            size = 0;
            return;
        }

        Node<T>* temp = head;
        while (temp->next != tail) {
            temp = temp->next;
        }

        delete tail;
        tail = temp;
        tail->next = nullptr;
        size--;
    }

    void clear() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }

        tail = nullptr;
        size = 0;
    }

    Iterator<Node<T>> begin() const {
        return Iterator<Node<T>>(head);
    }

    Iterator<Node<T>> end() const {
        return Iterator<Node<T>>(nullptr);
    }

private:
    Node<T>* head;
    Node<T>* tail;
    int size;
};

#endif
