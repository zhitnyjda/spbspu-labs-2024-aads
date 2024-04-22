#ifndef LIST_HPP
#define LIST_HPP
#include <list>

template<typename T>
class List {
public:
  std::list<T> data;

  void push_back(const T& value) {
    data.push_back(value);
  }

  typename std::list<T>::iterator begin() {
    return data.begin();
  }

  typename std::list<T>::iterator end() {
    return data.end();
  }

  bool empty() const {
    return data.empty();
  }

  size_t size() const {
    return data.size();
  }
};
#endif
