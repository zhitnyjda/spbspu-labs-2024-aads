#ifndef ITERATOR_HPP
#define ITERATOR_HPP

template <typename T>
class List;

template <typename T>
class Iterator {
public:
    Iterator(T* node) : current(node) {}

    T& operator*() const {
        return *current;
    }

    Iterator<T>& operator++() {
        current = current->next;
        return *this;
    }

    Iterator<T> operator++(int) {
        Iterator<T> temp(*this);
        ++(*this);
        return temp;
    }

    bool operator==(const Iterator<T>& other) const {
        return current == other.current;
    }

    bool operator!=(const Iterator<T>& other) const {
        return !(*this == other);
    }

private:
    T* current;
};

#endif
