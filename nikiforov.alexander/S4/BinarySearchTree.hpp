#ifndef AvlTree_HPP
#define AvlTree_HPP
#include <functional>

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

    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;

    bool is_empty() const noexcept;
    size_t getSize() const noexcept;

    Value& at(const Key& key);
    Iterator find(const Key& key);


    void insert(const keyValue_t& data);


  private:

    struct Node
    {
      Node* right;
      Node* left;
      Node* parent;
      keyValue_t data;
      size_t height;

      Node(keyValue_t data) :
        right(nullptr),
        left(nullptr),
        parent(nullptr),
        data(data),
        height(1)
      {}
    };

    Node* pRoot;
    size_t size;
    Compare cmp;

    void clear(Node* pNode);
    Node* balance(Node* pNode);
    Node* rotationRR(pNode* node);
    Node* rotationLL(pNode* node);
    Node* rotationLR(pNode* node);
    Node* rotationRL(pNode* node);

    void updateHeight(Node* pNode);
    Node* insertData(Node* pNode, const keyValue_t& data);
    size_t getHeight(Node* pNode);
    int heightDiff(Node* pNode);
    Node* balance(Node* pNode);
  };
}

namespace nikiforov
{
  template < typename Key, typename Value, typename Compare >
  class AvlTree< Key, Value, Compare >::ConstIterator : public std::iterator< std::bidirectional_iterator_tag, keyValue_t >
  {
  public:
    friend class BSTree< Key, Value, Compare >;
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
    Node* pRoot;
    Node* pNode;
  };
}

template < typename Key, typename Value, typename Compare >
nikiforov::AvlTree< Key, Value, Compare >::ConstIterator::ConstIterator() :
  pRoot(nullptr),
  pNode(nullptr)
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
    while ((pNode == pNode->parent->right) && (pNode->parent != nullptr))
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
  return pNode->data;
}

template < typename Key, typename Value, typename Compare >
const typename nikiforov::AvlTree< Key, Value, Compare >::keyValue_t* nikiforov::AvlTree< Key, Value, Compare >::Iterator::operator->() const
{
  return &(pNode->data);
}

template < typename Key, typename Value, typename Compare >
bool nikiforov::AvlTree< Key, Value, Compare >::Iterator::operator!=(const this_t& rhs) const
{
  return !(rhs == *this);
}

template < typename Key, typename Value, typename Compare >
bool nikiforov::AvlTree< Key, Value, Compare >::Iterator::operator==(const this_t& rhs) const
{
  return pNode == rhs.pNode;
}


template< typename Key, typename Value, typename Comp >
nikiforov::AvlTree< Key, Value, Comp >::AvlTree() :
  root(nullptr), size(0)
{}


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
  if (find(key) == end())
  {
    throw std::out_of_range("Such key does not exist\n");
  }
  else
  {
    return (find(key))->second;
  }
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
    else if (key > actualRoot->data.first)
    {
      actualRoot = actualRoot->right;
    }
    else if (key < actualRoot->data.first)
    {
      actualRoot = actualRoot->left;
    }
  }
  return end();
  return Iterator();
}

template< typename Key, typename Value, typename Compare >
void nikiforov::AvlTree<Key, Value, Compare>::insert(const keyValue_t& data)
{

}

template<typename Key, typename Value, typename Compare>
nikiforov::AvlTree<Key, Value, Compare>::Node* nikiforov::AvlTree<Key, Value, Compare>::insertData(Node* pNode, const keyValue_t& data)
{
  if (pNode == nullptr)
  {
    pNode = new Node(data);
  }
  else
  {
    if (cmp(pNode->data.first, data.first))
    {
      pNode->right = insert(pNode->right, value);
      pNode->right->parent = pNode;
    }
    else
    {
      pNode->left = insert(pNode->left, value);
      pNode->left->parent = pNode;
    }
  }

  int bFactor = heightDiff(pNode);
  if (bFactor == 2)
  {
    if (heightDiff(pNode->left) > 0)
    {
      pNode = rotateRR(pNode);
    }
    else
    {
      pNode = rotateLR(pNode);
    }
  }
  else if (bFactor == -2)
  {
    if (heightDiff(pNode->right) > 0)
    {
      pNode = rotateRL(pNode);
    }
    else
    {
      pNode = rotateLL(pNode);
    }
  }
  return pNode;
}

template < typename Key, typename Value, typename Compare >
size_t nikiforov::AvlTree< Key, Value, Compare >::getHeight(Node* pNode)
{
  if (pNode != nullptr)
  {
    size_t lHeight = getHeight(pNode->left);
    size_t rHeight = getHeight(pNode->right);
    size_t height = std::max(lHeight, rHeight) + 1;
  }
  else
  {
    return 0;
  }
  return height;
}

template < typename Key, typename Value, typename Compare >
int nikiforov::AvlTree< Key, Value, Compare >::heightDiff(Node* pNode)
{
  return pNode != nullptr ? getHeight(pNode->left) - getHeight(pNode->right) : 0;
}

template<typename Key, typename Value, typename Compare>
nikiforov::AvlTree< Key, Value, Compare >::Node* nikiforov::AvlTree<Key, Value, Compare>::balance(Node* pNode)
{

  return nullptr;
}

template < typename Key, typename Value, typename Compare >
typename nikiforov::AvlTree< Key, Value, Compare >::Node* nikiforov::AvlTree< Key, Value, Compare >::rotateLL(pNode* node)
{
  pNode* tmp = node->right;
  Node* parent = node->parent;
  node->right = tmp->left;
  if (node->right != nullptr)
  {
    node->right->parent = node;
  }
  tmp->left = node;
  tmp->left->parent = tmp;
  tmp->parent = parent;
  return tmp;
}

template < typename Key, typename Value, typename Compare >
typename nikiforov::AvlTree< Key, Value, Compare >::Node* nikiforov::AvlTree< Key, Value, Compare >::rotateRR(Node* node)
{
  Node* tmp = node->left;
  Node* parent = node->parent;
  node->left = tmp->right;
  if (node->left != nullptr)
  {
    node->left->parent = node;
  }
  tmp->right = node;
  tmp->right->parent = tmp;
  tmp->parent = parent;
  return tmp;
}

template < typename Key, typename Value, typename Compare >
typename nikiforov::AvlTree< Key, Value, Compare >::Node* nikiforov::AvlTree< Key, Value, Compare >::rotateRL(Node* node)
{
  node->right = rotateRR(node->right);
  return rotateLL(node);
}

template < typename Key, typename Value, typename Compare >
typename nikiforov::AvlTree< Key, Value, Compare >::Node* nikiforov::AvlTree< Key, Value, Compare >::rotateLR(Node* node)
{
  node->left = rotateLL(node->left);
  return rotateRR(node);
}


#endif
