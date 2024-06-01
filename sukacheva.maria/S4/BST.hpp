#ifndef BST_HPP
#define BST_HPP
#include <cassert>
#include <utility>
#include <functional>
#include <stdexcept>
#include "Node.hpp"

namespace sukacheva
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class BST
  {
  public:
    class Iterator;
    class ConstIterator;

    using Node = details::Node< Value, Key >;

    BST();
    BST(const BST& other) noexcept;
    BST(BST&& other) noexcept;
    ~BST();

    void insert(Key k, Value v);
    Value at(const Key& k);
    size_t getHeight(Node* node) const noexcept;
    bool empty() const noexcept;
    size_t size() const noexcept;
    Iterator find(const Key& k) const noexcept;
    Iterator erase(Iterator& pos) noexcept;
    void erase(const Key& k) noexcept;
    size_t count(const Key& k) const noexcept;
    void clear(Node* node);
    std::pair< Iterator, Iterator > equalRange(const Key& key) const noexcept;
    Iterator lowerBound(const Key& key) const noexcept;
    Iterator upperBound(const Key& key) const noexcept;

    Iterator begin() const;
    Iterator end() const;

    ConstIterator cbegin() const;
    ConstIterator cend() const;

    Value operator[](Key k);
  private:
    Node* root;
    Compare cmp;

    Node* findMin(Node* node) const;
    Node* findMax(Node* node) const;
    Node* push(Node* node, Key k, Value v);
    Node* balance(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
    Node* deleteNode(Node* node, const Key& k);
    void updateHeight(Node* node);
    int getBalanceFactor(Node* node);
  };

  template < typename Key, typename Value, typename Compare >
  class BST< Key, Value, Compare >::Iterator
  {
  public:
    friend class BST;
    Iterator();
    Iterator(Node* node_);
    ~Iterator() = default;
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;

    Iterator& operator++();
    Iterator operator++(int);

    std::pair< Key, Value >& operator*();
    std::pair< Key, Value >* operator->();

    bool operator!=(const Iterator&) const;
    bool operator==(const Iterator&) const;

  private:
    Node* findMin(Node* node);
    Node* node;
  };

  template < typename Key, typename Value, typename Compare >
  class BST< Key, Value, Compare >::ConstIterator
  {
  public:
    friend class BST;
    ConstIterator();
    ConstIterator(Node* node_);
    ~ConstIterator() = default;
    ConstIterator(const ConstIterator&) = default;
    ConstIterator& operator=(const ConstIterator&) = default;

    ConstIterator& operator++();
    ConstIterator operator++(int);

    const std::pair< Key, Value >& operator*() const;
    const std::pair< Key, Value >* operator->() const;

    bool operator!=(const ConstIterator&) const;
    bool operator==(const ConstIterator&) const;

  private:
    Node* findMin(Node* node);
    Node* node;
  };

  template< typename Key, typename Value, typename Compare >
  using iterator = typename BST< Key, Value, Compare >::Iterator;

  template< typename Key, typename Value, typename Compare >
  using constIterator = typename BST< Key, Value, Compare >::ConstIterator;

  template< typename Key, typename Value, typename Compare >
  using iteratorsPair = std::pair< iterator< Key, Value, Compare >, iterator< Key, Value, Compare > >;

  template< typename Key, typename Value, typename Compare >
  BST< Key, Value, Compare >::BST(const BST& other) noexcept
  {
    root = nullptr;
    cmp = other.cmp;
    ConstIterator it = other.cbegin();
    while (it != cend())
    {
      insert(it->first, it->second);
      it++;
    }
  }

  template< typename Key, typename Value, typename Compare >
  BST< Key, Value, Compare >::BST(BST&& other) noexcept :
    root(other.root),
    cmp(std::move(other.cmp))
  {
    other.root = nullptr;
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Iterator BST< Key, Value, Compare >::lowerBound(const Key& key) const noexcept
  {
    Node* current = root;
    Node* result = nullptr;
    while (current != nullptr)
    {
      if (!cmp(current->data.first, key))
      {
        result = current;
        current = current->left;
      }
      else
      {
        current = current->right;
      }
    }
    return Iterator(result);
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Iterator BST< Key, Value, Compare >::upperBound(const Key& key) const noexcept
  {
    Node* current = root;
    Node* result = nullptr;
    while (current != nullptr)
    {
      if (cmp(key, current->data.first))
      {
        result = current;
        current = current->left;
      }
      else
      {
        current = current->right;
      }
    }

    return Iterator(result);
  }

  template< typename Key, typename Value, typename Compare >
  iteratorsPair< Key, Value, Compare > BST< Key, Value, Compare >::equalRange(const Key& key) const noexcept
  {
    return std::make_pair(lower_bound(key), upper_bound(key));
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Iterator BST< Key, Value, Compare >::find(const Key& k) const noexcept
  {
    using iterator = typename BST< Key, Value >::Iterator;
    for (iterator it = begin(); it != end(); it++)
    {
      if (it->first == k)
      {
        return it;
      }
    }
    return nullptr;
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Iterator BST< Key, Value, Compare >::erase(Iterator& pos) noexcept
  {
    using iterator = typename BST< Key, Value >::Iterator;
    iterator it = pos;
    root = deleteNode(root, it->first);
    return it++;
  }

  template< typename Key, typename Value, typename Compare >
  size_t BST< Key, Value, Compare >::count(const Key& k) const noexcept
  {
    size_t counter = 0;
    using iterator = typename BST< Key, Value >::Iterator;
    for (iterator it = begin(); it != end(); it++)
    {
      if (it->first == k)
      {
        counter++;
      }
    }
    return counter;
  }

  template< typename Key, typename Value, typename Compare >
  Value BST< Key, Value, Compare >::at(const Key& k)
  {
    using iterator = typename BST< Key, Value >::Iterator;
    for (iterator it = begin(); it != end(); it++)
    {
      if (it->first == k)
      {
        return it->second;
      }
    }
    throw std::runtime_error("Key not found");
  }

  template< typename Key, typename Value, typename Compare >
  Value BST< Key, Value, Compare >::operator[](Key k)
  {
    return at(k);
  }

  template< typename Key, typename Value, typename Compare >
  BST< Key, Value, Compare >::BST():
    root(nullptr),
    cmp(Compare())
  {}

  template< typename Key, typename Value, typename Compare >
  BST< Key, Value, Compare >::~BST()
  {
    clear(root);
  }

  template< typename Key, typename Value, typename Compare >
  void BST< Key, Value, Compare >::clear(Node* node)
  {
    if (node)
    {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  template< typename Key, typename Value, typename Compare >
  size_t BST< Key, Value, Compare >::size() const noexcept
  {
    size_t size = 0;
    typename BST< Key, Value >::Iterator it = begin();
    while (it != end())
    {
      size++;
      it++;
    }
    return size;
  }

  template< typename Key, typename Value, typename Compare >
  bool BST< Key, Value, Compare >::empty() const noexcept
  {
    return size() > 0 ? false : true;
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Iterator BST< Key, Value, Compare >::begin() const
  {
    return Iterator(findMin(root));
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Iterator BST< Key, Value, Compare >::end() const
  {
    return Iterator(nullptr);
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::ConstIterator BST< Key, Value, Compare >::cbegin() const
  {
    return ConstIterator(findMin(root));
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::ConstIterator BST< Key, Value, Compare >::cend() const
  {
    return ConstIterator(nullptr);
  }

  template< typename Key, typename Value, typename Compare >
  BST< Key, Value, Compare >::ConstIterator::ConstIterator():
    node(nullptr)
  {}

  template< typename Key, typename Value, typename Compare >
  BST< Key, Value, Compare >::ConstIterator::ConstIterator(Node* node_) :
    node(node_)
  {}

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::ConstIterator& BST< Key, Value, Compare >::ConstIterator::operator++()
  {
    assert(node != nullptr);
    if (node->right != nullptr)
    {
      node = findMin(node->right);
    }
    else
    {
      while (node->parent != nullptr && node == node->parent->right)
      {
        node = node->parent;
      }
      node = node->parent;
    }
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::ConstIterator BST< Key, Value, Compare >::ConstIterator::operator++(int)
  {
    ConstIterator temp = *this;
    ++(*this);
    return temp;
  }

  template< typename Key, typename Value, typename Compare >
  const std::pair< Key, Value >& BST< Key, Value, Compare >::ConstIterator::operator*() const
  {
    return node->data;
  }

  template< typename Key, typename Value, typename Compare >
  const std::pair< Key, Value >* BST< Key, Value, Compare >::ConstIterator::operator->() const
  {
    return std::addressof(node->data);
  }

  template< typename Key, typename Value, typename Compare >
  bool BST< Key, Value, Compare >::ConstIterator::operator!=(const ConstIterator& other) const
  {
    return node != other.node;
  }

  template< typename Key, typename Value, typename Compare >
  bool BST< Key, Value, Compare >::ConstIterator::operator==(const ConstIterator& other) const
  {
    return node == other.node;
  }

  template< typename Key, typename Value, typename Compare >
  BST< Key, Value, Compare >::Iterator::Iterator():
    node(nullptr)
  {}

  template< typename Key, typename Value, typename Compare >
  BST< Key, Value, Compare >::Iterator::Iterator(Node* node_):
    node(node_)
  {}

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Iterator& BST< Key, Value, Compare >::Iterator::operator++()
  {
    assert(node != nullptr);
    if (node->right != nullptr)
    {
      node = findMin(node->right);
    }
    else
    {
      while (node->parent != nullptr && node == node->parent->right)
      {
        node = node->parent;
      }
      node = node->parent;
    }
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Iterator BST< Key, Value, Compare >::Iterator::operator++(int)
  {
    Iterator temp = *this;
    ++(*this);
    return temp;
  }

  template< typename Key, typename Value, typename Compare >
  std::pair< Key, Value >& BST< Key, Value, Compare >::Iterator::operator*()
  {
    return node->data;
  }

  template< typename Key, typename Value, typename Compare >
  std::pair< Key, Value >* BST< Key, Value, Compare >::Iterator::operator->()
  {
    return std::addressof(node->data);
  }

  template< typename Key, typename Value, typename Compare >
  bool BST< Key, Value, Compare >::Iterator::operator!=(const Iterator& other) const
  {
    return node != other.node;
  }

  template< typename Key, typename Value, typename Compare >
  bool BST< Key, Value, Compare >::Iterator::operator==(const Iterator& other) const
  {
    return node == other.node;
  }

  template < typename Key, typename Value, typename Compare >
  size_t BST< Key, Value, Compare >::getHeight(Node* node) const noexcept
  {
    if (node == nullptr)
    {
      return 0;
    }
    return node->height;
  }

  template < typename Key, typename Value, typename Compare >
  void BST< Key, Value, Compare >::updateHeight(Node* node)
  {
    if (node != nullptr)
    {
      node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
  }

  template < typename Key, typename Value, typename Compare >
  int BST< Key, Value, Compare >::getBalanceFactor(Node* node)
  {
    if (node == nullptr)
    {
      return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Node* BST< Key, Value, Compare >::Iterator::findMin(Node* node)
  {
    while (node && node->left != nullptr)
    {
      node = node->left;
    }
    return node;
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Node* BST< Key, Value, Compare >::ConstIterator::findMin(Node* node)
  {
    while (node && node->left != nullptr)
    {
      node = node->left;
    }
    return node;
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Node* BST< Key, Value, Compare >::findMax(Node* node) const
  {
    while (node && node->right != nullptr)
    {
      node = node->right;
    }
    return node;
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Node* BST< Key, Value, Compare >::findMin(Node* node) const
  {
    while (node && node->left != nullptr)
    {
      node = node->left;
    }
    return node;
  }

  template < typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Node* BST< Key, Value, Compare >::rotateLeft(Node* node)
  {
    Node* newRoot = node->right;
    node->right = newRoot->left;
    if (newRoot->left != nullptr)
    {
      newRoot->left->parent = node;
    }
    newRoot->parent = node->parent;
    if (node->parent == nullptr)
    {
      root = newRoot;
    }
    else if (node == node->parent->left)
    {
      node->parent->left = newRoot;
    }
    else
    {
      node->parent->right = newRoot;
    }
    newRoot->left = node;
    node->parent = newRoot;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
  }

  template < typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Node* BST< Key, Value, Compare >::rotateRight(Node* node)
  {
    Node* newRoot = node->left;
    node->left = newRoot->right;
    if (newRoot->right != nullptr)
    {
      newRoot->right->parent = node;
    }
    newRoot->parent = node->parent;
    if (node->parent == nullptr)
    {
      root = newRoot;
    }
    else if (node == node->parent->right)
    {
      node->parent->right = newRoot;
    }
    else
    {
      node->parent->left = newRoot;
    }
    newRoot->right = node;
    node->parent = newRoot;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
  }

  template < typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Node* BST< Key, Value, Compare >::balance(Node* node)
  {
    updateHeight(node);
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1)
    {
      if (getBalanceFactor(node->left) < 0)
      {
        node->left = rotateLeft(node->left);
      }
      return rotateRight(node);
    }
    if (balanceFactor < -1)
    {
      if (getBalanceFactor(node->right) > 0)
      {
        node->right = rotateRight(node->right);
      }
      return rotateLeft(node);
    }
    return node;
  }

  template < typename Key, typename Value, typename Compare >
  void BST< Key, Value, Compare >::insert(Key k, Value v)
  {
    root = push(root, k, v);
  }

  template < typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Node* BST< Key, Value, Compare >::push(Node* root, Key k, Value v)
  {
    Node* current = root;
    Node* prev = nullptr;
    while (current != nullptr)
    {
      prev = current;
      if (cmp(k, current->data.first))
      {
        current = current->left;
      }
      else if (cmp(current->data.first, k))
      {
        current = current->right;
      }
      else
      {
        return balance(root);
      }
    }
    Node* newNode = new Node(k, v, prev);
    if (prev == nullptr)
    {
      root = newNode;
    }
    else if (cmp(k, prev->data.first))
    {
      prev->left = newNode;
    }
    else
    {
      prev->right = newNode;
    }
    return balance(root);
  }

  template < typename Key, typename Value, typename Compare >
  void BST< Key, Value, Compare >::erase(const Key& k) noexcept
  {
    root = deleteNode(root, k);
  }

  template < typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Node* BST< Key, Value, Compare >::deleteNode(Node* node, const Key& k)
  {
    if (node == nullptr)
    {
      return node;
    }
    if (cmp(k, node->data.first))
    {
      node->left = deleteNode(node->left, k);
    }
    else if (cmp(node->data.first, k))
    {
      node->right = deleteNode(node->right, k);
    }
    else
    {
      if ((node->left == nullptr) || (node->right == nullptr))
      {
        Node* temp = node->left ? node->left : node->right;
        if (temp == nullptr)
        {
          temp = node;
          node = nullptr;
        }
        else
        {
          node = temp;
        }
        delete temp;
      }
      else
      {
        Node* temp = findMin(node->right);
        node->data.first = temp->data.first;
        node->data.second = temp->data.second;
        node->right = deleteNode(node->right, temp->data.first);
      }
    }
    if (node == nullptr)
    {
      return node;
    }
    return balance(node);
  }
}

#endif
