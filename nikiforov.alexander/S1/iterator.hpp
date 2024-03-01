#ifndef ITERATOR_HPP
#define ITERATOR_HPP

template <typename T>
class Iterator
{
public:
  Iterator();
  ~Iterator() = default;

  T& operator*();
  const T& operator*() const;
  T* operator->();
  const T* operator->() const;

private:
  Node<T>* pNode;
  const List<T>* this_list;
};

template<typename T>
Iterator<T>::Iterator() : pNode(nullptr) {}

template<typename T>
T& Iterator<T>::operator*()
{
  return pNode->data;
}

template<typename T>
const T& Iterator<T>::operator*() const
{
  return pNode->data;
}

template<typename T>
T* Iterator<T>::operator->()
{
  return &(pNode->data);
}

template<typename T>
const T* Iterator<T>::operator->() const
{
  return &(pNode->data);
}

#endif