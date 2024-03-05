#ifndef LIST_H
#define LIST_H

#include <iterator>
#include <memory>
#include <algorithm>
#include <vector>

template<typename T>
class List
{
public:
    struct Node
    {
        T data;
        std::shared_ptr<Node> next;

        Node(T data, std::shared_ptr<Node> next = nullptr) : data(data), next(next)
        {
        }
    };

    class Iterator
    {
    private:
        std::shared_ptr<Node> node;

    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

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

public:
    std::shared_ptr<Node> head;

    std::vector<unsigned long long> to_vector() const
    {
      std::vector<unsigned long long> elements;
      auto current = head;
      while (current != nullptr)
      {
        elements.push_back(current->data);
        current = current->next;
      }
      std::reverse(elements.begin(), elements.end());
      return elements;
    }

    List() : head(nullptr)
    {
    }

    void push_front(T data)
    {
      head = std::make_shared<Node>(data, head);
    }

    Iterator begin() const
    {
      return Iterator(head);
    }

    Iterator end() const
    {
      return Iterator();
    }
};

#endif
