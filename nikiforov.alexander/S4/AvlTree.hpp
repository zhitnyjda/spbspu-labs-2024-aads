#ifndef AvlTree_HPP
#define AvlTree_HPP
#include <functional>
#include <ios>

namespace nikiforov
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class AvlTree
  {
  public:
    class Iterator;
    class ConstIterator;

    using keyValue_t = std::pair< Key, Value >;

    AvlTree();
    ~AvlTree();

    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;

    bool is_empty() const noexcept;
    size_t getSize() const noexcept;

    Value& at(const Key& key);

    void insert(const keyValue_t& data);
    void erase(Iterator pos);
    size_t erase(const Key& k);
    void clear();

    Iterator find(const Key& key);

  private:

    struct Node
    {
      Node* right;
      Node* left;
      Node* parent;
      keyValue_t data;

      Node(keyValue_t data) :
        right(nullptr),
        left(nullptr),
        parent(nullptr),
        data(data)
      {}
    };

    Node* pRoot;
    size_t size;
    Compare cmp;

    Node* rotationRR(Node* pNode);
    Node* rotationLL(Node* pNode);
    Node* rotationRL(Node* pNode);
    Node* rotationLR(Node* pNode);

    Node* insertData(Node* pNode, const keyValue_t& data);
    size_t countSize(Node* pNode) const;
    size_t getHeight(Node* pNode);
    void updateHeight(Node* pNode);
    int heightDiff(Node* pNode);
    Node* balance(Node* pNode);
    void delAll(Node* pNode);
    Node* remove(Node* pNode, const Key& key);
    Node* minBranchValue(Node* pNode);
  };
}

namespace nikiforov
{
  template < typename Key, typename Value, typename Compare >
  class AvlTree< Key, Value, Compare >::ConstIterator : public std::iterator< std::bidirectional_iterator_tag, keyValue_t >
  {
  public:
    friend class AvlTree< Key, Value, Compare >;
    using this_t = ConstIterator;

    ConstIterator();
    ConstIterator(const this_t&) = default;
    ~ConstIterator() = default;

    this_t& operator=(const this_t&) = default;
    this_t& operator++();
    this_t operator++(int);
    this_t& operator--();
    this_t operator--(int);

    const keyValue_t& operator*() const;
    const keyValue_t* operator->() const;

    bool operator!=(const this_t&) const;
    bool operator==(const this_t&) const;

  private:
    Node* pNode;
    ConstIterator(Node* pNode);
  };
}

template < typename Key, typename Value, typename Compare >
nikiforov::AvlTree< Key, Value, Compare >::ConstIterator::ConstIterator() :
  pNode(nullptr)
{}

template < typename Key, typename Value, typename Compare >
nikiforov::AvlTree< Key, Value, Compare >::ConstIterator::ConstIterator(Node* pNode) :
  pNode(pNode)
{}

template < typename Key, typename Value, typename Compare >
typename nikiforov::AvlTree< Key, Value, Compare >::ConstIterator& nikiforov::AvlTree< Key, Value, Compare >::ConstIterator::operator++()
{
  if (pNode->right != nullptr)
  {
    pNode = pNode->right;
    while (pNode->left != nullptr)
    {
      pNode = pNode->left;
    }
  }
  else
  {
    while ((pNode->parent != nullptr) && (pNode == pNode->parent->right))
    {
      pNode = pNode->parent;
    }
    pNode = pNode->parent;
  }
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename nikiforov::AvlTree< Key, Value, Compare >::ConstIterator nikiforov::AvlTree< Key, Value, Compare >::ConstIterator::operator++(int)
{
  ConstIterator iter = *this;
  ++(*this);
  return iter;
}

template < typename Key, typename Value, typename Compare >
typename nikiforov::AvlTree< Key, Value, Compare >::ConstIterator& nikiforov::AvlTree< Key, Value, Compare >::ConstIterator::operator--()
{
  if (pNode == nullptr)
  {
    pNode = pRoot;
    while (pNode->right != nullptr)
    {
      pNode = pNode->right;
    }
  }
  else if (pNode->left != nullptr)
  {
    pNode = pNode->left;
    while (pNode->right != nullptr)
    {
      pNode = pNode->right;
    }
  }
  else
  {
    while ((pNode == pNode->parent->left) && (pNode->parent != nullptr))
    {
      pNode = pNode->parent;
    }
    pNode = pNode->parent;
  }
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename nikiforov::AvlTree< Key, Value, Compare >::ConstIterator nikiforov::AvlTree< Key, Value, Compare >::ConstIterator::operator--(int)
{
  ConstIterator iter = *this;
  --(*this);
  return iter;
}

template < typename Key, typename Value, typename Compare >
const typename nikiforov::AvlTree< Key, Value, Compare >::keyValue_t& nikiforov::AvlTree< Key, Value, Compare >::ConstIterator::operator*() const
{
  return pNode->data;
}

template < typename Key, typename Value, typename Compare >
const typename nikiforov::AvlTree< Key, Value, Compare >::keyValue_t* nikiforov::AvlTree< Key, Value, Compare >::ConstIterator::operator->() const
{
  return &(pNode->data);
}

template < typename Key, typename Value, typename Compare >
bool nikiforov::AvlTree< Key, Value, Compare >::ConstIterator::operator!=(const this_t& rhs) const
{
  return !(rhs == *this);
}

template < typename Key, typename Value, typename Compare >
bool nikiforov::AvlTree< Key, Value, Compare >::ConstIterator::operator==(const this_t& rhs) const
{
  return pNode == rhs.pNode;
}

namespace nikiforov
{
  template < typename Key, typename Value, typename Compare >
  class AvlTree< Key, Value, Compare >::Iterator : public std::iterator< std::bidirectional_iterator_tag, keyValue_t >
  {
  public:
    friend class AvlTree< Key, Value, Compare >;
    using this_t = Iterator;

    Iterator();
    Iterator(Node* pNode);
    Iterator(ConstIterator constIter);
    Iterator(const this_t&) = default;
    ~Iterator() = default;

    this_t& operator=(const this_t&) = default;
    this_t& operator++();
    this_t operator++(int);
    this_t& operator--();
    this_t operator--(int);

    keyValue_t& operator*();
    keyValue_t* operator->();
    const keyValue_t& operator*() const;
    const keyValue_t* operator->() const;

    bool operator!=(const this_t&) const;
    bool operator==(const this_t&) const;

  private:
    ConstIterator iter;
  };
}

template < typename Key, typename Value, typename Compare >
nikiforov::AvlTree< Key, Value, Compare >::Iterator::Iterator() :
  iter(ConstIterator())
{}

template< typename Key, typename Value, typename Compare >
nikiforov::AvlTree< Key, Value, Compare >::Iterator::Iterator(Node* pNode) :
  iter(ConstIterator(pNode))
{}

template < typename Key, typename Value, typename Compare >
nikiforov::AvlTree< Key, Value, Compare >::Iterator::Iterator(ConstIterator constIter) :
  iter(constIter)
{}

template< typename Key, typename Value, typename Compare >
typename nikiforov::AvlTree< Key, Value, Compare >::Iterator& nikiforov::AvlTree< Key, Value, Compare >::Iterator::operator++()
{
  iter++;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename nikiforov::AvlTree< Key, Value, Compare >::Iterator nikiforov::AvlTree< Key, Value, Compare >::Iterator::operator++(int)
{
  ++iter;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename nikiforov::AvlTree< Key, Value, Compare >::Iterator& nikiforov::AvlTree< Key, Value, Compare >::Iterator::operator--()
{
  iter--;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename nikiforov::AvlTree< Key, Value, Compare >::Iterator nikiforov::AvlTree< Key, Value, Compare >::Iterator::operator--(int)
{
  --iter;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename nikiforov::AvlTree< Key, Value, Compare >::keyValue_t& nikiforov::AvlTree< Key, Value, Compare >::Iterator::operator*()
{
  return iter.pNode->data;
}

template< typename Key, typename Value, typename Compare >
typename nikiforov::AvlTree< Key, Value, Compare >::keyValue_t* nikiforov::AvlTree< Key, Value, Compare >::Iterator::operator->()
{
  return &(iter.pNode->data);
}

template < typename Key, typename Value, typename Compare >
const typename nikiforov::AvlTree< Key, Value, Compare >::keyValue_t& nikiforov::AvlTree< Key, Value, Compare >::Iterator::operator*() const
{
  return iter.pNode->data;
}

template < typename Key, typename Value, typename Compare >
const typename nikiforov::AvlTree< Key, Value, Compare >::keyValue_t* nikiforov::AvlTree< Key, Value, Compare >::Iterator::operator->() const
{
  return &(iter.pNode->data);
}

template < typename Key, typename Value, typename Compare >
bool nikiforov::AvlTree< Key, Value, Compare >::Iterator::operator!=(const this_t& rhs) const
{
  return !(rhs == *this);
}

template < typename Key, typename Value, typename Compare >
bool nikiforov::AvlTree< Key, Value, Compare >::Iterator::operator==(const this_t& rhs) const
{
  return iter.pNode == rhs.iter.pNode;
}


template< typename Key, typename Value, typename Compare >
nikiforov::AvlTree< Key, Value, Compare >::AvlTree() :
  pRoot(nullptr), size(0)
{}

template<typename Key, typename Value, typename Compare>
nikiforov::AvlTree<Key, Value, Compare>::~AvlTree()
{
  clear();
}

template<typename Key, typename Value, typename Compare>
typename nikiforov::AvlTree<Key, Value, Compare>::Iterator nikiforov::AvlTree<Key, Value, Compare>::begin() noexcept
{
  if (is_empty())
  {
    return end();
  }
  Node* actualRoot = pRoot;
  while (actualRoot->left != nullptr)
  {
    actualRoot = actualRoot->left;
  }
  return Iterator(ConstIterator(actualRoot));
}

template<typename Key, typename Value, typename Compare>
typename nikiforov::AvlTree<Key, Value, Compare>::Iterator nikiforov::AvlTree<Key, Value, Compare>::end() noexcept
{
  return Iterator(ConstIterator(nullptr));
}

template<typename Key, typename Value, typename Compare>
typename nikiforov::AvlTree<Key, Value, Compare>::ConstIterator nikiforov::AvlTree<Key, Value, Compare>::cbegin() const noexcept
{
  if (is_empty())
  {
    return cend();
  }
  Node* actualRoot = pRoot;
  while (actualRoot->left != nullptr)
  {
    actualRoot = actualRoot->left;
  }
  return ConstIterator(actualRoot);
}

template<typename Key, typename Value, typename Compare>
typename nikiforov::AvlTree<Key, Value, Compare>::ConstIterator nikiforov::AvlTree<Key, Value, Compare>::cend() const noexcept
{
  return ConstIterator(nullptr);
}

template< typename Key, typename Value, typename Compare >
bool nikiforov::AvlTree< Key, Value, Compare >::is_empty() const noexcept
{
  return size == 0;
}

template< typename Key, typename Value, typename Compare >
size_t nikiforov::AvlTree< Key, Value, Compare >::getSize() const noexcept
{
  return size;
}

template< typename Key, typename Value, typename Compare >
Value& nikiforov::AvlTree< Key, Value, Compare >::at(const Key& key)
{
  auto iter = find(key);

  if (iter == end())
  {
    throw std::out_of_range("Such key does not exist\n");
  }
  else
  {
    return iter->second;
  }
}

template< typename Key, typename Value, typename Compare >
void nikiforov::AvlTree<Key, Value, Compare>::insert(const keyValue_t& data)
{
  pRoot = insertData(pRoot, data);
  size++;
}

template< typename Key, typename Value, typename Compare >
void nikiforov::AvlTree< Key, Value, Compare >::erase(Iterator pos)
{
  if (pos != nullptr)
  {
    Value key = pos.iter.pNode->data;
    pRoot = remove(pRoot, key);
    size--;
  }
}

template< typename Key, typename Value, typename Compare >
size_t nikiforov::AvlTree< Key, Value, Compare >::erase(const Key& key)
{
  if (find(key) != nullptr)
  {
    pRoot = remove(pRoot, key);
    size--;
    return 1;
  }
  return 0;
}

template<typename Key, typename Value, typename Compare>
void nikiforov::AvlTree<Key, Value, Compare>::clear()
{
  delAll(pRoot);
  pRoot = nullptr;
  size = 0;
}

template<typename Key, typename Value, typename Compare>
typename nikiforov::AvlTree<Key, Value, Compare>::Iterator nikiforov::AvlTree<Key, Value, Compare>::find(const Key& key)
{
  Node* actualRoot = pRoot;
  while (actualRoot)
  {
    if (actualRoot->data.first == key)
    {
      return Iterator(actualRoot);
    }
    else if (cmp(actualRoot->data.first, key))
    {
      actualRoot = actualRoot->right;
    }
    else
    {
      actualRoot = actualRoot->left;
    }
  }
  return end();
}

///





///



///

template<typename Key, typename Value, typename Compare>
void nikiforov::AvlTree<Key, Value, Compare>::updateHeight(Node* pNode)
{
  if (pNode == nullptr)
  {
    return 0;
  }
  return pNode->height = std::max(updateHeight(pNode->left), updateHeight(pNode->right)) + 1;
}

template<typename Key, typename Value, typename Compare>
size_t nikiforov::AvlTree<Key, Value, Compare>::countSize(Node* pNode) const
{
  if (pNode == nullptr)
  {
    return 0;
  }
  return (countSize(pNode->left) + countSize(pNode->right) + 1);
}

template<typename Key, typename Value, typename Compare>
typename nikiforov::AvlTree<Key, Value, Compare>::Node* nikiforov::AvlTree<Key, Value, Compare>::insertData(Node* pNode, const keyValue_t& data)
{
  if (pNode == nullptr)
  {
    pNode = new Node(data);
  }
  else
  {
    if (cmp(pNode->data.first, data.first))
    {
      pNode->right = insertData(pNode->right, data);
      pNode->right->parent = pNode;
    }
    else
    {
      pNode->left = insertData(pNode->left, data);
      pNode->left->parent = pNode;
    }
  }
  return balance(pNode);
}

template < typename Key, typename Value, typename Compare >
size_t nikiforov::AvlTree< Key, Value, Compare >::getHeight(Node* pNode)
{
  if (pNode != nullptr)
  {
    size_t lHeight = getHeight(pNode->left);
    size_t rHeight = getHeight(pNode->right);
    size_t height = std::max(lHeight, rHeight) + 1;
    return height;
  }
  else
  {
    return 0;
  }
}

template < typename Key, typename Value, typename Compare >
int nikiforov::AvlTree< Key, Value, Compare >::heightDiff(Node* pNode)
{
  return pNode != nullptr ? getHeight(pNode->left) - getHeight(pNode->right) : 0;
}

template < typename Key, typename Value, typename Compare >
typename nikiforov::AvlTree< Key, Value, Compare >::Node* nikiforov::AvlTree< Key, Value, Compare >::rotationRR(Node* pNode)
{
  Node* tmp = pNode->left;
  Node* parent = pNode->parent;
  pNode->left = tmp->right;
  if (pNode->left != nullptr)
  {
    pNode->left->parent = pNode;
  }
  tmp->right = pNode;
  tmp->right->parent = tmp;
  tmp->parent = parent;
  return tmp;
}

template < typename Key, typename Value, typename Compare >
typename nikiforov::AvlTree< Key, Value, Compare >::Node* nikiforov::AvlTree< Key, Value, Compare >::rotationLL(Node* pNode)
{
  Node* tmp = pNode->right;
  Node* parent = pNode->parent;
  pNode->right = tmp->left;
  if (pNode->right != nullptr)
  {
    pNode->right->parent = pNode;
  }
  tmp->left = pNode;
  tmp->left->parent = tmp;
  tmp->parent = parent;
  return tmp;
}

template < typename Key, typename Value, typename Compare >
typename nikiforov::AvlTree< Key, Value, Compare >::Node* nikiforov::AvlTree< Key, Value, Compare >::rotationRL(Node* pNode)
{
  pNode->right = rotationRR(pNode->right);
  return rotationLL(pNode);
}

template < typename Key, typename Value, typename Compare >
typename nikiforov::AvlTree< Key, Value, Compare >::Node* nikiforov::AvlTree< Key, Value, Compare >::rotationLR(Node* pNode)
{
  pNode->left = rotationLL(pNode->left);
  return rotationRR(pNode);
}

template < typename Key, typename Value, typename Compare >
typename nikiforov::AvlTree< Key, Value, Compare >::Node* nikiforov::AvlTree< Key, Value, Compare >::balance(Node* pNode)
{
  if (heightDiff(pNode) == 2)
  {
    if (heightDiff(pNode->left) > 0)
    {
      pNode = rotationRR(pNode);
    }
    else
    {
      pNode = rotationLR(pNode);
    }
  }
  else if (heightDiff(pNode) == -2)
  {
    if (heightDiff(pNode->right) > 0)
    {
      pNode = rotationRL(pNode);
    }
    else
    {
      pNode = rotationLL(pNode);
    }
  }

  return pNode;
}

template<typename Key, typename Value, typename Compare>
void nikiforov::AvlTree<Key, Value, Compare>::delAll(Node* pNode)
{
  if (pNode)
  {
    delAll(pNode->left);
    delAll(pNode->right);
  }
  delete pNode;
}

template<typename Key, typename Value, typename Compare>
typename nikiforov::AvlTree< Key, Value, Compare >::Node* nikiforov::AvlTree<Key, Value, Compare>::remove(Node* pNode, const Key& key)
{
  if (pNode == nullptr)
  {
    return pNode;
  }

  if (pNode->data.first == key)
  {
    if (pNode->left == nullptr || pNode->right == nullptr)
    {
      Node* actual = pNode->left ? pNode->left : pNode->right;

      if (actual == nullptr)
      {
        actual = pNode;
        pNode = nullptr;
      }
      else
      {
        *pNode = *actual;
      }
      delete actual;
    }
    else
    {
      Node* actual = minBranchValue(pNode->right);
      pNode->data = actual->data;
      pNode->right = remove(pNode->right, actual->data.first);
    }
  }
  else if (cmp(pNode->data.first, key))
  {
    pNode->right = remove(pNode->right, key);
  }
  else
  {
    pNode->left = remove(pNode->left, key);
  }

  return pNode == nullptr ? pNode : balance(pNode);
}

template<typename Key, typename Value, typename Compare>
typename nikiforov::AvlTree< Key, Value, Compare >::Node* nikiforov::AvlTree<Key, Value, Compare>::minBranchValue(Node* pNode)
{
  Node* actual = pNode;
  while (actual->left != nullptr)
  {
    actual = actual->left;
  }
  return actual;
}

#endif