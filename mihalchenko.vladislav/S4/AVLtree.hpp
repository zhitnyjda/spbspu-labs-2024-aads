#ifndef AVLTREE_HPP
#define AVLTREE_HPP
#include <utility>
#include <iterator>
#include <initializer_list>
#include <functional>
#include <iostream>

/*#include <functional>
template<typename A, typename B, typename C = std::less<>>
constexpr bool fun(A a, B b, C cmp = C{})
{
    return cmp(a, b);
} */

namespace mihalchenko
{
  template <typename Key, typename Value, typename Compare = std::less<Key>>
  class AVLTree
  {
  public:
    class ConstIterator;
    class Iterator;

    AVLTree();

    template <class InputIt>
    AVLTree(InputIt start, InputIt stop);

    AVLTree(size_t count, std::pair<const Key, Value> &pairKeyVal);
    AVLTree(std::initializer_list<std::pair<const Key, Value>> initAVL);
    AVLTree(const AVLTree &copy);
    AVLTree(AVLTree &&move);
    ~AVLTree();

    void insert(Key key, Value value);
    using value_std_pair = std::pair<const Key, Value>;
    void insert(std::pair<const Key, Value> pairKeyVal);
    bool empty() const noexcept;
    size_t getSize() const noexcept;
    size_t erase(const Key &key);
    void clear();

    template <class... Args>
    void emplace(Args &&...args);

    Value &operator[](const Key &key);
    Iterator find(const Key &key);
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;
    Iterator begin() noexcept;
    Iterator end() noexcept;

  private:
    class Node
    {
    public:
      friend class AVLTree;
      Node(Key key, Value data, int height = 0, Node *left = nullptr, Node *right = nullptr, Node *previous = nullptr);

    private:
      std::pair<const Key, Value> pairOfKeyVal;
      int height_;
      Node *left_;
      Node *right_;
      Node *previous_;
    };

    Node *insertNode(Key k, Value v, Node *node, Node *prev);
    Iterator findNode(const Key &key, Node *node);

    void leftSpin(Node *node);
    void leftRightSpin(Node *node);
    void rightSpin(Node *node);
    void rightLeftSpin(Node *node);

    int calcHeight(Node *node);
    Node *SearchHiHeight(Node *node);

    Node *copyTree(Node *node, Node *previous);
    void doStableTree(Node *checkNode);
    void clear(Node *node);
    void recombinationLinks(Node *deletedNode, Node *prevDelNode);

    Node *root_;
    size_t size_ = 0;
  };
}

template <typename Key, typename Value, typename Compare>
class mihalchenko::AVLTree<Key, Value, Compare>::ConstIterator : public std::iterator<std::bidirectional_iterator_tag, std::pair<const Key, Value>>
// https://learn.microsoft.com/ru-ru/cpp/standard-library/bidirectional-iterator-tag-struct?view=msvc-170
{
public:
  friend class AVLTree<Key, Value, Compare>;
  ConstIterator();
  ConstIterator(Node *node, Node *root);
  ConstIterator(const ConstIterator &) = default;
  ~ConstIterator() = default;

  ConstIterator &operator++();
  ConstIterator operator++(int);
  ConstIterator &operator--();
  ConstIterator operator--(int);

  const std::pair<const Key, Value> &operator*() const;
  const std::pair<const Key, Value> *operator->() const;

  bool operator!=(const ConstIterator &rhs) const;
  bool operator==(const ConstIterator &rhs) const;

  ConstIterator &operator=(const ConstIterator &) = default;

private:
  Node *node_;
  Node *root_;
};

template <typename Key, typename Value, typename Compare>
class mihalchenko::AVLTree<Key, Value, Compare>::Iterator : public std::iterator<std::bidirectional_iterator_tag, Key, Value, Compare>
{
public:
  friend class AVLTree<Key, Value, Compare>;
  Iterator();
};

template <typename Key, typename Value, typename Compare>
mihalchenko::AVLTree<Key, Value, Compare>::Node::Node(Key key, Value data, int height, Node *left, Node *right, Node *previous) : pairOfKeyVal(std::make_pair(key, data)), height_(height), left_(left), right_(right), previous_(previous)
{
}
#endif
