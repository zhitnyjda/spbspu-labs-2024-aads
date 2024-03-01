#ifndef LIST_HPP
#define LIST_HPP

namespace ponomarev
{
  template< typename T >
  class List
  {
    public:
      class ConstIterator
      {
        private:
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

    private:
      struct Node
      {
        public:
          T data;
          Node * prev = nullptr;
          Node * next = nullptr;
          Node(T data)
          {
            this->data = data;
          }
      };

      Node * head = nullptr;
      Node * tail = nullptr;
  };
}
