#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include <algorithm>
#include <utility>
#include <functional>
#include <iterator>
#include <cassert>
#include <memory>

#include <iostream> //

//может быть updateHeight не надо использовать?
// и height_ тоже??

namespace kovshikov
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
 // class BinarySearchTree
  class Tree
  {
  public:

    Tree();
    Tree(const Tree& tree);
    Tree(Tree&& tree);

    ~Tree();

    class Node;
    class Iterator;
    class ConstIterator;

    using Pair = std::pair< Key, Value >;
    using Range = std::pair< Iterator, Iterator >;
    Compare comp;

   // void printStart(); /////////

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;

    Iterator find(const Key& key) const;
    size_t count(const Key& key) const;
    Range getEqualRange(const Key& key) const;

    void insert(const Key& key, const Value& value);
    void insert(Pair& pair);
    Value& operator[](const Key& key);
    Value& at(const Key& key);

    void clear();
    size_t erase(const Key& key);
    Iterator erase(Iterator iterator);

    void swap(Tree& other);

    Iterator end() const noexcept;
    Iterator begin() const noexcept;

    ConstIterator cend() const noexcept;
    ConstIterator cbegin() const noexcept;

  private:
    Node* root_;

    size_t getHeight(Node* node);
    long long getDifference(Node* node);
    void updateHeight(Node* node);
    void RightRight(Node* node);
    void LeftLeft(Node* node);

    Node* checkBalance(Node* node);
    void balance(Node* node);

    void clear(Node* node);
  };
 // using Tree = BinarySearchTree;
}


template< typename Key, typename Value, typename Compare >
class kovshikov::Tree< Key, Value, Compare >::Node
{
public:
  friend class Tree< Key, Value, Compare >;
  Node(Key key, Value value, Node* father = nullptr, size_t height = 0, Node* left = nullptr, Node* right = nullptr);

private:
  Node* left_;
  Node* right_;
  Node* father_;
  size_t height_;
  Pair element_;
};

template< typename Key, typename Value, typename Compare >
kovshikov::Tree< Key, Value, Compare >::Node::Node(Key key, Value value, Node* father, size_t height, Node* left, Node* right):
  left_(left),
  right_(right),
  father_(father),
  height_(height),
  element_(std::make_pair(key, value))
{};

template< typename Key, typename Value, typename Compare >
class kovshikov::Tree< Key, Value, Compare >::Iterator : public std::iterator< std::bidirectional_iterator_tag, Pair >
{
public:

  friend class Tree< Key, Value, Compare >;
  using this_t = Iterator;

  Iterator(): node_(nullptr), root_(nullptr) {};
  Iterator(Node* node, Node* root): node_(node), root_(root) {};
  Iterator(const this_t&) = default;
  ~Iterator() = default;

  this_t& operator=(const this_t&) = default;

  this_t& operator++();
  this_t operator++(int);

  this_t& operator--();
  this_t operator--(int);

  bool operator==(const this_t& other) const;
  bool operator!=(const this_t& other) const;

  Pair& operator*() const;
  Pair* operator->() const;

private:
  Node* node_;
  Node* root_;
};

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Iterator::this_t& kovshikov::Tree< Key, Value, Compare >::Iterator::operator++()
{
 // std::cout << "start ++\n"; //
  assert(node_ != nullptr);
  Node* current = node_;
 /* if(node_ -> father_ == nullptr)
  {
    std::cout << "next == nullptr\n"; //
  }*/
 // std::cout << node_ ->element_.first << "\n"; //
  if(current -> right_)
  {
   // std::cout << "A\n"; //
    current = current -> right_;
    while(current -> left_)
    {
      current = current -> left_;
    }
  }
  else
  {
   // std::cout << "B\n"; //
    Node* currentFather = current -> father_;
   /* if(currentFather == nullptr)
    {
      std::cout << "currentFather\n"; ////
    }*/
    while(currentFather && current == currentFather -> right_)
    {
     // std::cout << "цикл\n"; //
      current = currentFather;
      currentFather = currentFather -> father_;
    }
    current = currentFather;
   /* if(current == nullptr)
    {
      std::cout << "jwekfejwjewfiojeoeicjodsk\n"; //
    }
    else
    {
      std::cout << current -> element_.first << "\n"; //
    }*/
  }
  node_ = current;
 /* if(node_ == nullptr)
  {
    std::cout << "ERRORRRO\n"; /////////
  }
  else
  {
    std::cout << node_ ->element_.first << "\n"; //////////
  }
  std::cout << "++ end\n"; //*/
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Iterator::this_t kovshikov::Tree< Key, Value, Compare >::Iterator::operator++(int)
{
  assert(node_ != nullptr);
  this_t currentIterator = *this;
  ++(*this);
  return currentIterator;
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Iterator::this_t& kovshikov::Tree< Key, Value, Compare >::Iterator::operator--()
{
  assert(node_ != nullptr);
  Node* current = node_;
  if(current -> left)
  {
    current = current -> left;
    while(current -> right)
    {
      current = current -> right;
    }
  }
  else
  {
    Node* currentFather = current -> father;
    while(currentFather && current == currentFather -> left)
    {
      current = currentFather;
      currentFather = currentFather -> father;
    }
    current = currentFather;
  }
  node_ = current;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Iterator::this_t kovshikov::Tree< Key, Value, Compare >::Iterator::operator--(int)
{
  assert(node_ != nullptr);
  this_t currentIterator = *this;
  --(*this);
  return currentIterator;
}

template< typename Key, typename Value, typename Compare >
bool kovshikov::Tree< Key, Value, Compare >::Iterator::operator==(const this_t& other) const
{
  return node_ == other.node_;
}

template< typename Key, typename Value, typename Compare >
bool kovshikov::Tree< Key, Value, Compare >::Iterator::operator!=(const this_t& other) const
{
  return !(*this == other);
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Pair& kovshikov::Tree< Key, Value, Compare >::Iterator::operator*() const
{
  assert(node_ != nullptr);
  return node_ -> element_;
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Pair* kovshikov::Tree< Key, Value, Compare >::Iterator::operator->() const
{
  assert(node_ != nullptr);
  return std::addressof(node_ -> element_);
}

template< typename Key, typename Value, typename Compare >
class kovshikov::Tree< Key, Value, Compare >::ConstIterator : public std::iterator< std::bidirectional_iterator_tag, Pair >
{
public:

  friend class Tree< Key, Value, Compare >;
  using this_t = ConstIterator;

  ConstIterator(): iterator_(Iterator()) {};
  ConstIterator(Iterator iterator): iterator_(iterator) {};
  ConstIterator(const this_t&) = default;
  ~ConstIterator() = default;

  this_t& operator=(const this_t&) = default;

  this_t& operator++();
  this_t operator++(int);

  this_t& operator--();
  this_t operator--(int);

  bool operator==(const this_t& other) const;
  bool operator!=(const this_t& other) const;

  const Pair& operator*() const;
  const Pair* operator->() const;

private:
  Iterator iterator_;
};

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::ConstIterator& kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator++()
{
 // std::cout << "const ++1\n"; //
  assert(iterator_.node_ != nullptr);
 // std::cout << "const ++2\n"; //
  iterator_++;
 // std::cout << "const ++3\n"; //
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::ConstIterator kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator++(int)
{
 // std::cout << "(int)const ++1\n"; //
  if(iterator_.node_ == nullptr)
  {
   // std::cout << "wtf\n"; //
  }
  if(iterator_.root_ == nullptr)
  {
   // std::cout << "wtf2\n"; //
  }
  assert(iterator_.node_ != nullptr);
  ++iterator_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::ConstIterator& kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator--()
{
  assert(iterator_.node_ != nullptr);
  iterator_--;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::ConstIterator kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator--(int)
{
  assert(iterator_.node_ != nullptr);
  --iterator_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
bool kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator==(const this_t& other) const
{
  return iterator_ == other.iterator_;
}

template< typename Key, typename Value, typename Compare >
bool kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator!=(const this_t& other) const
{
  return !(*this == other);
}

template< typename Key, typename Value, typename Compare >
const typename kovshikov::Tree< Key, Value, Compare >::Pair& kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator*() const
{
  assert(iterator_.node_ != nullptr);
  return iterator_.node_ -> element_;
}

template< typename Key, typename Value, typename Compare >
const typename kovshikov::Tree< Key, Value, Compare >::Pair* kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator->() const
{
  assert(iterator_.node_ != nullptr);
  return std::addressof(iterator_.node_ -> element_);
}

template< typename Key, typename Value, typename Compare >
kovshikov::Tree< Key, Value, Compare >::Tree():
  comp(Compare()),
  root_(nullptr)
{};

template< typename Key, typename Value, typename Compare >
kovshikov::Tree< Key, Value, Compare >::Tree(const Tree& tree)
{
  root_ = nullptr;
  comp = tree.comp_;
  Iterator iterator = tree.begin();
  while(iterator != tree.end())
  {
    insert(iterator -> first, iterator -> second);
    iterator++;
  }
}

template< typename Key, typename Value, typename Compare >
kovshikov::Tree< Key, Value, Compare >::Tree(Tree&& tree):
  root_(tree.root_),
  comp(std::move(tree.comp))
{
  tree.root_ = nullptr;
}

template< typename Key, typename Value, typename Compare >
kovshikov::Tree< Key, Value, Compare >::~Tree()
{
  clear();
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Iterator kovshikov::Tree< Key, Value, Compare >::end() const noexcept
{
//  return Iterator(nullptr, root_);
 // std::cout << "END\n"; //
  Node* current = root_;
  if(current == nullptr)
  {
   // std::cout << "&&&\n"; //
    return Iterator(nullptr, nullptr);
  }
  while(current != nullptr)
  {
    current = current -> right_;
  }
  //тут не надо прибавлять 1, тк current укаэет на элемент идущий за max
 // std::cout << "END END\n"; //
  return Iterator(current, root_);
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Iterator kovshikov::Tree< Key, Value, Compare >::begin() const noexcept
{
 // std::cout << "BEGIN\n"; //
  Node* current = root_;
  Node* returned = nullptr;
  if(current == nullptr)
  {
   // std::cout << "??\n"; //
    return end();
  }
  while(current != nullptr)
  {
    returned = current;
    current = current -> left_;
  }
 // std::cout << returned -> element_.first;//////
 // std::cout << "BEGIN END\n"; //
  return Iterator(returned, root_); //тут была ошибка с тем что возвращал пустой указатель
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::ConstIterator kovshikov::Tree< Key, Value, Compare >::cend() const noexcept
{
 // std::cout << "CEND\n"; //
  Iterator iterator = this->end();
 // std::cout << "CEND END\n"; //
  return ConstIterator(iterator);
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::ConstIterator kovshikov::Tree< Key, Value, Compare >::cbegin() const noexcept
{
 // std::cout << "CBEGIN\n"; //
  Iterator iterator = this->begin();
 // std::cout << "CBEGIN END\n"; //
  return ConstIterator(iterator);
}

template< typename Key, typename Value, typename Compare >
bool kovshikov::Tree< Key, Value, Compare >::isEmpty() const noexcept
{
  return (root_ == nullptr) ? true : false;
}

template< typename Key, typename Value, typename Compare >
size_t kovshikov::Tree< Key, Value, Compare >::getSize() const noexcept
{
 // std::cout << "START GETSIZE\n"; //
  Iterator cstart = begin();
  Iterator cfinish = end();
//  std::cout << (cstart.node_) -> element_.first << "\n"; //разыменовывание приводит к утечке памяти
 /* if(cstart.node_ == nullptr)
  {
    std::cout << "NULLPTR\n"; //
  }*/
  size_t size = 0;
  while(cstart != cfinish)
  {
    size += 1;
   // std::cout << "WHILE\n"; //
    cstart++;
   // std::cout << "WHILE2\n"; //
   /* if(cstart == cfinish)
    {
      std::cout << "FATALITY\n"; //
    }*/
  }
 // std::cout << "FINISH GETSIZE\n"; //
  return size;
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Iterator kovshikov::Tree< Key, Value, Compare >::find(const Key& key) const
{
  Node* current = root_;
  while(current != nullptr)
  {
    if(current -> element_.first == key)
    {
      return Iterator(current, root_);
    }
    else if(comp(key, current -> element_.first))
    {
      current = current -> left_;
    }
    else
    {
      current = current -> right_;
    }
  }
  return end();
}

template< typename Key, typename Value, typename Compare >
size_t kovshikov::Tree< Key, Value, Compare >::count(const Key& key) const
{
  if(find(key) == end())
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Range kovshikov::Tree< Key, Value, Compare >::getEqualRange(const Key& key) const
{
  if(find(key) != begin())
  {
    Iterator start = find(key);
    Iterator finish = start + 1;
    return std::make_pair(start, finish);
  }
  else
  {
    return std::make_pair(end(), end());
  }
}

template< typename Key, typename Value, typename Compare >
size_t kovshikov::Tree< Key, Value, Compare >::getHeight(Node* node)
{
 // std::cout << "START GETHEIGHT\n"; //
  if(node == nullptr)
  {
    return 0;
  }
  return std::max(getHeight(node -> left_), getHeight(node -> right_)) + 1;
}

template< typename Key, typename Value, typename Compare >
long long kovshikov::Tree< Key, Value, Compare >::getDifference(Node* node)
{
 // std::cout << "START GETDIFFERENCE\n"; //
  return getHeight(node -> left_) - getHeight(node -> right_);
}

template< typename Key, typename Value, typename Compare >
void kovshikov::Tree< Key, Value, Compare >::updateHeight(Node* node)
{
 // std::cout << "START UPDATE\n"; //
  while(node != nullptr)
  {
    node -> height_ = std::max(getHeight(node -> left_), getHeight(node -> right_)) + 1;
    node = node -> father_;
  }
}

template< typename Key, typename Value, typename Compare >
void kovshikov::Tree< Key, Value, Compare >::RightRight(Node* node)
{
 // std::cout << "START RIGHTRIGHT\n"; //
  Node* bigFather = node -> father_;
  Node* newFather = node -> left_;
  Node* lastRight = newFather -> right_;

  node -> father_ = newFather;
  if(bigFather != nullptr)
  {
    if(comp(node -> element_.first, bigFather -> element_.first))
    {
      bigFather -> left_ = newFather;
    }
    else
    {
      bigFather -> right_ = newFather;
    }
  }
  else
  {
    root_ = newFather;
  }
  newFather -> father_ = bigFather;
  newFather -> right_ = node;
  node ->left_ = lastRight; //странно
  if(lastRight != nullptr)
  {
    lastRight -> father_ = node; //nullptr
  }
 // updateHeight(node);
 // std::cout << newFather -> element_.first << "\n"; //
 // std::cout << node -> element_.first << "\n"; //
}

template< typename Key, typename Value, typename Compare >
void kovshikov::Tree< Key, Value, Compare >::LeftLeft(Node* node)
{
 // std::cout << "START LEFTLEFT\n"; //
  Node* bigFather = node -> father_;
  Node* newFather = node -> right_;
  Node* lastLeft = newFather -> left_;

  node -> father_ = newFather;
  if(bigFather != nullptr)
  {
    if(comp(node -> element_.first, bigFather -> element_.first))
    {
      bigFather -> left_ = newFather;
    }
    else
    {
      bigFather -> right_ = newFather;
    }
  }
  else
  {
    root_ = newFather;
  }

  newFather -> father_ = bigFather;
  newFather -> left_ = node;
  node -> right_ = lastLeft;
  if(lastLeft != nullptr)
  {
    lastLeft -> father_ = node; //проверка на nullptr;
  }
 // updateHeight(node);
 // std::cout << newFather -> element_.first << "\n"; //
 // std::cout << node -> element_.first << "\n"; //
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Node* kovshikov::Tree< Key, Value, Compare >::checkBalance(Node* node)
{
  std::cout << "START CHECKBALANCE\n"; //
  while(node != nullptr)
  {
    if(std::abs(getDifference(node)) > 1)
    {
      return node;
    }
    else
    {
      node = node -> father_;
    }
  }
  std::cout << "FINISH CHECKBALANCE\n"; //
  return node;
}

template< typename Key, typename Value, typename Compare >
void kovshikov::Tree< Key, Value, Compare >::balance(Node* node)
{
  std::cout << "START BALANCE\n"; //
  Node* toBalance = node; //
  bool isBalance = false;
  while(isBalance == false)
  {
    toBalance = checkBalance(toBalance); // заменил node на checkBalance и переприсваивал
    if(toBalance == nullptr)
    {
      isBalance = true;
    }
    else
    {
      std::cout << "DO BALANCE\n"; //
      if(getDifference(toBalance) < -1 && getDifference(toBalance -> right_) <= 0)
      {
        std::cout << "START LEFTLEFT\n"; //
        LeftLeft(toBalance);
        std::cout << "LEFTLEFT\n"; //
      }
      else if(getDifference(toBalance) > 1 && getDifference(toBalance -> left_) >= 0)
      {
        RightRight(toBalance);
       // std::cout << "RIGHTRIGHT\n"; //
      }
      else if(getDifference(toBalance) < -1 && getDifference(toBalance -> right_) > 0)
      {
        RightRight(toBalance -> right_);
        LeftLeft(toBalance);
       // std::cout << "RL\n"; //
      }
      else if(getDifference(toBalance) > 1 && getDifference(toBalance -> left_) < 0)
      {
        LeftLeft(toBalance -> left_);
        RightRight(toBalance);
       // std::cout << "LR\n"; //
      }
      toBalance = toBalance -> father_;
    }
  }
  std::cout << "FINISH BALANCE\n"; //
}

template< typename Key, typename Value, typename Compare >
void kovshikov::Tree< Key, Value, Compare >::insert(const Key& key, const Value& value)
{
 // std::cout << "INSERT\n"; //
  if(find(key) == end())
  {
    Node* newNode = new Node(key, value);
    if(isEmpty())
    {
      root_ = newNode;
      //std::cout << "GET ROOT\n"; //
    }
    else
    {
      //std::cout << "NO ROOT\n"; //
      Node* current = root_;
      Node* father = nullptr;
      while(current != nullptr)
      {
        father = current;
        if(comp(key, current -> element_.first))
        {
          current = current -> left_;
        }
        else
        {
          current = current -> right_;
        }
      }
      newNode -> father_ = father;
      if(comp(key, father -> element_.first))
      {
        father -> left_ = newNode;
      }
      else
      {
        father -> right_ = newNode;
      }
    }
    //std::cout << "INSERT2\n"; //
    balance(newNode); //можно засунуть в else
    //std::cout << "END INSERT\n"; //
  }
 // std::cout << "END END\n"; //
}

template< typename Key, typename Value, typename Compare >
void kovshikov::Tree< Key, Value, Compare >::insert(Pair& pair)
{
  insert(pair.first, pair.second);
}

template< typename Key, typename Value, typename Compare >
Value& kovshikov::Tree< Key, Value, Compare >::operator[](const Key& key)
{
  if(find(key) == end())
  {
    insert(key, Value());
    return Value();
  }
  else
  {
    return find(key) -> second;
  }
}

template< typename Key, typename Value, typename Compare >
Value& kovshikov::Tree< Key, Value, Compare >::at(const Key& key)
{
  if(find(key) == end())
  {
    throw std::out_of_range("");
  }
  else
  {
    return find(key) -> second;
  }
}

template< typename Key, typename Value, typename Compare >
void kovshikov::Tree< Key, Value, Compare >::clear(Node* node)
{
  if(node != nullptr)
  {
    clear(node -> left_);
    clear(node -> right_);
    delete node;
  }
}

template< typename Key, typename Value, typename Compare >
void kovshikov::Tree< Key, Value, Compare >::clear()
{
  if(!isEmpty())
  {
    clear(root_);
  }
  root_ = nullptr;
}

template< typename Key, typename Value, typename Compare >
void kovshikov::Tree< Key, Value, Compare >::swap(Tree& other)
{
  std::swap(comp, other.comp);
  std::swap(root_, other.root_);
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Iterator kovshikov::Tree< Key, Value, Compare >::erase(Iterator iterator)
{
  Node* toDelete = iterator.node_;
  Node* bigFather = toDelete -> father_;
  Node* changer = nullptr;
  Node* temp = nullptr;
  Node* toBalance = nullptr;
  std::cout << toDelete ->element_.first << "\n"; //
  std::cout << bigFather ->element_.first << "\n"; //
  if(toDelete == nullptr)
  {
    return end();
  }
  if(toDelete -> left_ == nullptr && toDelete -> right_ == nullptr)
  {
    std::cout << "if\n"; //
    if(bigFather != nullptr)
    {
      std::cout << "if2\n"; //
      if(comp(toDelete -> element_.first, bigFather -> element_.first))
      {
        bigFather -> left_ = nullptr;
      }
      else
      {
        bigFather -> right_ = nullptr;
      }
      delete toDelete;
      std::cout << "if3\n"; //
      balance(bigFather); //ОШИБКА В БАЛАНСИРОВКЕ
      std::cout << "f4\n"; //
      return Iterator(bigFather, root_); //скорее всего не тот итератор возвращаю
    }
    else
    {
      delete toDelete;
      return end();
    }
  }
  else if(toDelete -> left_ == nullptr && toDelete -> right_ != nullptr)
  {
    std::cout << "else if\n"; //
    changer = toDelete -> right_;
    temp = changer -> left_;
    while(temp != nullptr)
    {
      changer = temp;
      temp = temp -> left_;
    }
    toBalance = changer -> father_;
    if(toBalance != toDelete)
    {
      toBalance -> left_ = nullptr;
    }
  }
  else
  {
    std::cout << "else\n"; //
    changer = toDelete -> left_;
    temp = changer -> right_;
    while(temp != nullptr)
    {
      changer = temp;
      temp = temp -> right_;
    }
    toBalance = changer -> father_;
    if(toBalance != toDelete)
    {
      toBalance -> right_ = nullptr;
    }
  }
  if(comp(toDelete -> element_.first, bigFather -> element_.first))
  {
    bigFather -> left_ = changer;
  }
  else
  {
    bigFather -> right_ = changer;
  }
  changer -> father_ = bigFather;
  if(toDelete -> left_ != nullptr && changer != toDelete -> left_)
  {
    std::cout << "A\n"; //
    changer -> left_ = toDelete -> left_; //по факту на самого себя
    toDelete -> left_ -> father_ = changer; // и тут
  }
  if(toDelete -> right_ != nullptr && changer != toDelete -> right_)
  {
    std::cout << "B\n"; //
    changer -> right_ = toDelete -> right_; // тоже самое
    toDelete -> right_ -> father_ = changer;// ---...----
  }

  if(toBalance != toDelete)
  {
    std::cout << "toBalance\n"; //
    delete toDelete;
    balance(toBalance);
  }
  else
  {
    std::cout << "changer\n"; //
    delete toDelete;
    balance(changer);
  }
//updateHeight(root_);
  std::cout << "end of erase\n"; //
  return Iterator(changer, root_);
}

template< typename Key, typename Value, typename Compare >
size_t kovshikov::Tree< Key, Value, Compare >::erase(const Key& key)
{
  Iterator iterator = find(key);
  if(iterator == end())
  {
    return 0;
  }
  else
  {
    erase(iterator);
    return 1;
  }
}
/*
template< typename Key, typename Value, typename Compare >
void kovshikov::Tree< Key, Value, Compare >::printStart()
{
  std::cout << root_ -> element_.first << "\n";
  std::cout << root_ -> left_ -> element_.first << "\n";
  std::cout << root_ -> right_ -> element_.first << "\n";
}
*/

#endif
