#ifndef LIST_H
#define LIST_H

#include <memory>
#include <iostream>

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

    std::shared_ptr<Node> head;

    List() : head(nullptr)
    {
    }

    void push_front(T data)
    {
      head = std::make_shared<Node>(data, head);
    }

    void push_back(T data)
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
