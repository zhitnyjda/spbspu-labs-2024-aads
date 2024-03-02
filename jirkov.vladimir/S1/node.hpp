#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
class Node {
public:
    Node(const T& val) : value(val), next(nullptr) {}

    T value;
    Node<T>* next;
};

#endif
