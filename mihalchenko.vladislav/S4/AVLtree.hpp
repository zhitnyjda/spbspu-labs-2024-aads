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

    Node *root_;
    size_t size_ = 0;
  };
};


template <typename Key, typename Value, typename Compare>
mihalchenko::AVLTree<Key, Value, Compare>::Node::Node(Key key, Value data, int height, Node *left, Node *right, Node *previous) : pairOfKeyVal(std::make_pair(key, data)), height_(height), left_(left), right_(right), previous_(previous)
{
}

template <typename Key, typename Value, typename Compare>
mihalchenko::AVLTree<Key, Value, Compare>::AVLTree() : root_(nullptr), size_(0)
{
}

template <typename Key, typename Value, typename Compare>
mihalchenko::AVLTree<Key, Value, Compare>::AVLTree(size_t count, std::pair<const Key, Value> &pairKeyVal) : root_(nullptr), size_(0)
{
  for (size_t i = 0; i < count; ++i)
  {
    insert(pairKeyVal);
  }
}

template <typename Key, typename Value, typename Compare>
template <class InputIt>
mihalchenko::AVLTree<Key, Value, Compare>::AVLTree(InputIt start, InputIt stop)
{
  for (InputIt it = start; it != stop; ++it)
  {
    insert(*it);
  }
}

template <typename Key, typename Value, typename Compare>
mihalchenko::AVLTree<Key, Value, Compare>::AVLTree(std::initializer_list<std::pair<const Key, Value>> initAVL) : root_(nullptr), size_(0)
{
  for (auto it = initAVL.begin(); it != initAVL.end(); ++it)
  {
    insert(*it);
  }
}

template <typename Key, typename Value, typename Compare>
mihalchenko::AVLTree<Key, Value, Compare>::AVLTree(const AVLTree &copy) : root_(nullptr), size_(copy.size_)
{
  root_ = copyTree(copy.root_, nullptr);
}

template <typename Key, typename Value, typename Compare>
mihalchenko::AVLTree<Key, Value, Compare>::AVLTree(AVLTree &&move) : root_(nullptr), size_(std::move(move.size_))
{
  root_ = copyTree(std::move(move.root_), nullptr);
  move.clear();
  move.root_ = nullptr;
  move.size_ = 0;
}

template <typename Key, typename Value, typename Compare>
mihalchenko::AVLTree<Key, Value, Compare>::~AVLTree()
{
  clear();
  root_ = nullptr;
}

template <typename Key, typename Value, typename Compare>
void mihalchenko::AVLTree<Key, Value, Compare>::insert(mihalchenko::AVLTree<Key, Value, Compare>::value_std_pair pair)
{
  insert(pair.first, pair.second);
}

template <typename Key, typename Value, typename Compare>
void mihalchenko::AVLTree<Key, Value, Compare>::insert(Key key, Value value)
{
  root_ = insertNode(key, value, root_, nullptr);
  if (root_ != nullptr)
  {
    size_t value1 = 0;
    size_t value2 = 0;
    if (root_->left_)
    {
      value1 = root_->left_->height_;
    }
    if (root_->right_)
    {
      value2 = root_->right_->height_;
    }
    root_->height_ = std::max(value1, value2) + 1;
  }
  Node *checkNode = SearchHiHeight(find(key).constIter_.node_);
  doStableTree(checkNode);
}

#endif
