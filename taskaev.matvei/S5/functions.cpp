#include <iostream>
#include <string>
#include "functions.hpp"
#include "BSTree.hpp"
#include "Queue.hpp"

namespace taskaev
{
  void createTree(std::istream& in, BSTree< int, std::string >& tree)
  {
    std::string data = "";
    std::getline(in, data);
    if (!data.empty())
    {
      std::string temps = "";
      std::string names = "";
      size_t i = 0;
      int key = 0;
      while (i < data.length())
      {
        if (data[i] != ' ')
        {
          temps += data[i];
        }
        else
        {
          bool flag = true;
          bool flagTwo = false;
          if (temps[0] == '-' && temps.length())
          {
            flagTwo = false;
          }
          size_t i = 0;
          while (i < temps.length())
          {
            if (flagTwo == true)
            {
              if (i > 0 && !std::isDigit(temps[i]))
              {
                flag == false;
                break;
              }
            }
            else
            {
              if (!std::isDigit(temps[i]))
              {
                flag == false;
                break;
              }
            }
            i++;
          }
          if (flag == true)
          {
            key = std::stoi(temps);
            temps = "";
          }
          else
          {
            names = temps;
            temps = "";
            tree.insert(key, names);
          }
        }
        i++;
      }
      if (!names.empty())
      {
        names = temps;
        tree.insert(key, names);
      }
    }
  }

  void ascending(BSTree< int, std::string >& tree)
  {
    if (tree.empty())
    {
      errorEmpty(std::cout);
      return;
    }
    else
    {
      Queue< std::string > queue;
      int result = 0;
      tree.traverse_lnr([&](const std::pair< const int, std::string >& value)
        {
          int max = std::numeric_limits<int>::max();
          int min = -max;
          if (value.first > 0 && max - value.first < result)
          {
            throw;
          }
          else if (value.first < 0 && min - value.first > result)
          {
            throw;
          }
          result = result + value.first;
          queue.push(value.second);
        });
      std::cout << result << " ";
      while (!queue.isEmpty())
      {
        std::cout << queue.front();
        queue.pop();
        if (!queue.isEmpty())
        {
          std::cout << " ";
        }
        else
        {
          std::cout << "\n";
        }
      }
    }
  }

  void descending(BSTree< int, std::string >& tree)
  {
    if (tree.empty())
    {
      errorEmpty(std::cout);
      return;
    }
    else
    {
      Queue< std::string > queue;
      int result = 0;
      tree.traverse_rnl([&](const std::pair< const int, std::string >& value)
        {
          int max = std::numeric_limits<int>::max();
          int min = -max;
          if (value.first > 0 && max - value.first < result)
          {
            throw;
          }
          else if (value.first < 0 && min - value.first > result)
          {
            throw;
          }
          result = result + value.first;
          queue.push(value.second);
        });
      std::cout << result << " ";
      while (!queue.isEmpty())
      {
        std::cout << queue.front();
        queue.pop();
        if (!queue.isEmpty())
        {
          std::cout << " ";
        }
        else
        {
          std::cout << "\n";
        }
      }
    }
  }

  void breadth(BSTree< int, std::string >& tree)
  {
    if (tree.empty())
    {
      errorEmpty(std::cout);
      return;
    }
    else
    {
      Queue< std::string > queue;
      int result = 0;
      tree.traverse_breadth([&](const std::pair< const int, std::string >& value)
        {
          int max = std::numeric_limits<int>::max();
          int min = -max;
          if (value.first > 0 && max - value.first < result)
          {
            throw;
          }
          else if (value.first < 0 && min - value.first > result)
          {
            throw;
          }
          result = result + value.first;
          queue.push(value.second);
        });
      std::cout << result << " ";
      while (!queue.isEmpty())
      {
        std::cout << queue.front();
        queue.pop();
        if (!queue.isEmpty())
        {
          std::cout << " ";
        }
        else
        {
          std::cout << "\n";
        }
      }
    }
  }

  void errorEmpty(std::ostream& out)
  {
    out << "<EMPTY>\n";
  }

}
