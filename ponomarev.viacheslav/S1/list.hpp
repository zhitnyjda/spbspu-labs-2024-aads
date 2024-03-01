#ifndef LIST_HPP
#define LIST_HPP

namespace ponomarev
{
  template< typename T >
  class List
  {
    List() = default;
    List(std::initializer_list< T > items)
    {
      for (auto &item : items)
      {
        push_back(item);
      }
    }

    ~List()
    {
      clear()
    }

    void clear() noexcept
    {
      while (head)
      {
        delete std::exchange(head, head->next);
      }
      tail = nullptr;
    }

    void push(T item)
    {
      auto newNode = new Node { std::move(item) };
      if (head)
      {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
      }
      else
      {
        head = tail = newNode;
      }
    }

    public:
      class ConstIterator
      {
        private:
          friend class List;
          explicit ConstIterator(const Node * ptr) noexcept:
            elem { ptr } {}
        public:
          T & operator*() const noexcept
          {
            assert(elem != nullptr);
            return elem->data;
          }

          ConstIterator & operator++() noexcept
          {
            assert(elem != nullptr);
            elem = elem->next;
            return *this;
          }

          ConstIterator & operator--() noexcept
          {
            assert(elem != nullptr);
            elem = elem->prev;
            return *this;
          }

          ConstIterator operator++(int) noexcept
          {
            assert(elem != nullptr);
            auto copy = *this;
            elem = elem->next;
            return copy;
          }

          ConstIterator operator--() noexcept
          {
            assert(elem != nullptr);
            auto copy = *this;
            elem = elem->prev;
            return copy;
          }

          bool operator==(ConstIterator other) const noexcept
          {
            return elem == other.elem;
          }

          bool operator!=(ConstIterator other) const noexcept
          {
            return !(*this == other);
          }
        protected:
          const Node *get() const noexcept
          {
            return elem;
          }

          const Node * elem;
      };

      class Iterator : public ConstIterator
      {
        private:
          friend class List;
          explicit Iterator(Node * ptr) noexcept:
            ConstIterator { ptr } {}

        public:
          T & operator*() noexcept
          {
            return const_cast< T & >(ConstIterator::operator*());
          }

          Iterator & operator++() noexcept
          {
            ConstIterator::operator++();
            return *this;
          }

          Iterator & operator--() noexcept
          {
            ConstIterator::operator--();
            return *this;
          }

          Iterator operator++(int) noexcept
          {
            auto res = ConstIterator::operator++(0);
            return Iterator { const_cast< Node * >(res.get()) };
          }

          Iterator operator--(int) noexcept
          {
            auto res = ConstIterator::operator--(0);
            return Iterator { const_cast< Node * >(res.get()) };
          }
        };
        using iterator = Iterator;
        using const_iterator = ConstIterator;
    private:
      struct Node
      {
        public:
          T data;
          Node * prev = nullptr;
          Node * next = nullptr;
          Node(T data) noexcept : data { std::move(item) } {}
      };

      Node * head = nullptr;
      Node * tail = nullptr;
  };
}
