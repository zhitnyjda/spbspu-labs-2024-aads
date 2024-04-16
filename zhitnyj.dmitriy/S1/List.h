#ifndef LIST_H
#define LIST_H

#include <memory>
#include <iostream>

template<typename T>
class List
{
private:
  struct Node
  {
    T data;
    std::shared_ptr<Node> next;

    Node(T data, std::shared_ptr<Node> next = nullptr) : data(data), next(next)
    {
    }
  };

  std::shared_ptr<Node> head;

public:
    List() : head(nullptr)
    {
    }

    List(size_t count, const T& value)
    {
      for (size_t i = 0; i < count; ++i)
      {
        push_back(value);
      }
    }

    List(std::initializer_list<T> init)
    {
      for (const auto& value : init)
      {
        push_back(value);
      }
    }

    List(const List& other)
    {
      for (auto node = other.head; node != nullptr; node = node->next)
      {
        push_back(node->data);
      }
    }

    List& operator=(const List& other)
    {
      if (this != &other)
      {
        for (auto node = other.head; node != nullptr; node = node->next)
        {
          push_back(node->data);
        }
      }
      return *this;
    }

    void push(T data) noexcept
    {
      head = std::make_shared<Node>(data, head);
    }

    void pop() noexcept
    {
      if (head != nullptr)
      {
        head = head->next;
      }
    }

    void clear() noexcept
    {
      head = nullptr;
    }

    void swap(List& other) noexcept
    {
      auto temp = head;
      head = other.head;
      other.head = temp;
    }

    void fill(const T& value, size_t n) noexcept
    {
      clear();
      for (size_t i = 0; i < n; ++i)
      {
        push_back(value);
      }
    }

    void splice(List<T>& other) noexcept
    {
      if (other.head == nullptr)
      {
        return;
      }

      if (head == nullptr)
      {
        head = other.head;
      }
      else
      {
        auto current = head;
        while (current->next != nullptr)
        {
          current = current->next;
        }
        current->next = other.head;
      }
      other.head = nullptr;
    }

    List(List&& other) noexcept: head(std::move(other.head))
    {
      other.head = nullptr;
    }

    List& operator=(List&& other) noexcept
    {
      if (this != &other)
      {
        head = std::move(other.head);
        other.head = nullptr;
      }
      return *this;
    }

    List<T>& operator[](size_t index)
    {
      auto current = head;
      for (size_t i = 0; i < index; ++i)
      {
        if (!current) throw std::out_of_range("Index is out of range.");
        current = current->next;
      }
      return current->data;
    }

    void assign(size_t count, const T& value) noexcept
    {
      clear();
      fill(value, count);
    }

    template<typename InputIterator>
    void assign(InputIterator first, InputIterator last) noexcept
    {
      clear();
      for (auto it = first; it != last; ++it)
      {
        push_back(*it);
      }
    }

    void assign(std::initializer_list<T> list) noexcept
    {
      clear();
      for (const auto& value : list)
      {
        push_back(value);
      }
    }

    void insert(size_t index, const T& value) noexcept
    {
      if (index == 0 || !head)
      {
        head = std::make_shared<Node>(value, head);
        return;
      }

      auto current = head;
      size_t currentIndex = 0;
      while (current->next && currentIndex < index - 1)
      {
        current = current->next;
        ++currentIndex;
      }
      current->next = std::make_shared<Node>(value, current->next);
    }

    void erase(const T& value) noexcept
    {
      while (head && head->data == value)
      {
        head = head->next;
      }
      auto current = head;
      while (current && current->next)
      {
        if (current->next->data == value)
        {
          current->next = current->next->next;
        }
        else
        {
          current = current->next;
        }
      }
    }

    void reverse() noexcept
    {
      std::shared_ptr<Node> prev = nullptr, current = head, next = nullptr;
      while (current != nullptr)
      {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
      }
      head = prev;
    }

    int empty() const noexcept
    {
      return head == nullptr;
    }

    void push_front(const T &data)
    {
      head = std::make_shared<Node>(data, head);
    }

    void push_back(const T &data)
    {
      auto newNode = std::make_shared<Node>(data);
      if (!head)
      {
        head = newNode;
      }
      else
      {
        auto current = head;
        while (current->next)
        {
          current = current->next;
        }
        current->next = newNode;
      }
    }

    size_t size() const
    {
      size_t count = 0;
      auto node = head;
      while (node != nullptr)
      {
        count++;
        node = node->next;
      }
      return count;
    }

    class Iterator
    {
    private:
        std::shared_ptr<Node> node;

    public:
        Iterator(std::shared_ptr<Node> node = nullptr) : node(node)
        {
        }

        T& operator*() const
        {
          return node->data;
        }

        T* operator->()
        {
          return &node->data;
        }

        Iterator& operator++()
        {
          node = node->next;
          return *this;
        }

        Iterator operator+(int n) const
        {
          Iterator temp = *this;
          for (int i = 0; i < n && temp.node != nullptr; ++i)
          {
            temp.node = temp.node->next;
          }
          return temp;
        }

        Iterator& operator+=(int n)
        {
          for (int i = 0; i < n && node != nullptr; i++)
          {
            node = node->next;
          }
          return *this;
        }

        Iterator operator++(int)
        {
          Iterator tmp = *this;
          node = node->next;
          return tmp;
        }

        friend bool operator==(const Iterator& a, const Iterator& b)
        {
          return a.node == b.node;
        }

        friend bool operator!=(const Iterator& a, const Iterator& b)
        {
          return a.node != b.node;
        }
    };

    Iterator begin() const
    {
      return Iterator(head);
    }
    Iterator end() const
    {
      return Iterator(nullptr);
    }
};

#endif
