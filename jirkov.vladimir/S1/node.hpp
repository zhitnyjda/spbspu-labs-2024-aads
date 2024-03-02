#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(const T& value) : data(value), next(nullptr) {}
};

#endif
