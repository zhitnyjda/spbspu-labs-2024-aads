#include "Commands.hpp"
#include <string>
#include <sstream>
#include "ErrorMessage.hpp"

namespace sukacheva
{
  void inputTree(treeOfTrees& treeOfDicts, std::istream& in) {
    std::string treeStr;
    while (std::getline(in, treeStr))
    {
      if (!treeStr.empty())
      {
        BST< size_t, std::string > tree;
        std::istringstream iss(treeStr);
        size_t key;
        std::string value;
        std::string name;
        iss >> name;
        while (iss >> key >> value)
        {
          tree.insert(key, value);
        }
        treeOfDicts.insert(name, tree);
      }
    }
  }


  void print(treeOfTrees& treeOfDicts, std::string name, std::ostream& out)
  {
    if (treeOfDicts.empty())
    {
      EmptyMessage(out);
      return;
    }
    BST< size_t, std::string > dict = treeOfDicts.find(name)->second;
    using iterator = BST< size_t, std::string >::Iterator;
    out << name;
    if (dict.empty())
    {
      EmptyMessage(out);
      return;
    }
    out << " ";
    size_t counter = 0;
    for (iterator it = dict.begin(); it != dict.end(); it++)
    {
      out << it->first << " " << it->second;
      counter++;
      if (counter != dict.size())
      {
        out << " ";
      }
      else
      {
        out << "\n";
      }
    }
  }

  void printCommand(treeOfTrees& treeOfDicts, std::istream& in, std::ostream& out)
  {
    std::string name;
    in >> name;
    if (in.fail())
    {
      throw std::logic_error("< WRONG INPUT >\n");
    }
    print(treeOfDicts, name, out);
  }

  void comlement(treeOfTrees& treeOfDicts, std::istream& in, std::ostream& out)
  {
    std::string nameNew;
    std::string nameFirst;
    std::string nameSecond;
    in >> nameNew >> nameFirst >> nameSecond;
    if (in.fail())
    {
      throw std::logic_error("< WRONG INPUT >\n");
    }
    if (treeOfDicts.empty())
    {
      EmptyMessage(out);
      return;
    }
    BST< size_t, std::string > secondDict = treeOfDicts.find(nameSecond)->second;
    BST< size_t, std::string > newDict = treeOfDicts.find(nameFirst)->second;;
    using iterator = BST< size_t, std::string >::Iterator;
    for (iterator it = secondDict.begin(); it != secondDict.end(); it++)
    {
      if (newDict.find(it->first) != nullptr)
      {
        newDict.erase(it->first);
      }
    }
    treeOfDicts.insert(nameNew, newDict);
    print(treeOfDicts, nameNew, out);
  }

  void intersect(treeOfTrees& treeOfDicts, std::istream& in, std::ostream& out)
  {
    std::string nameNew;
    std::string nameFirst;
    std::string nameSecond;
    in >> nameNew >> nameFirst >> nameSecond;
    if (in.fail())
    {
      throw std::logic_error("< WRONG INPUT >\n");
    }
    if (treeOfDicts.empty())
    {
      EmptyMessage(out);
      return;
    }
    BST< size_t, std::string > secondDict = treeOfDicts.find(nameSecond)->second;
    BST< size_t, std::string > firstDict = treeOfDicts.find(nameFirst)->second;
    BST< size_t, std::string > newDict;
    using iterator = BST< size_t, std::string >::Iterator;
    for (iterator it = secondDict.begin(); it != secondDict.end(); it++)
    {
      if (firstDict.find(it->first) != nullptr)
      {
        newDict.insert(it->first, it->second);
      }
    }
    treeOfDicts.insert(nameNew, newDict);
    print(treeOfDicts, nameNew, out);
  }

  void unionCommand(treeOfTrees& treeOfDicts, std::istream& in, std::ostream& out)
  {
    std::string nameNew;
    std::string nameFirst;
    std::string nameSecond;
    in >> nameNew >> nameFirst >> nameSecond;
    if (in.fail())
    {
      throw std::logic_error("< WRONG INPUT >\n");
    }
    if (treeOfDicts.empty())
    {
      EmptyMessage(out);
      return;
    }
    BST< size_t, std::string > secondDict = treeOfDicts.find(nameSecond)->second;
    BST< size_t, std::string > newDict = treeOfDicts.find(nameFirst)->second;;
    using iterator = BST< size_t, std::string >::Iterator;
    for (iterator it = secondDict.begin(); it != secondDict.end(); it++)
    {
      if (newDict.find(it->first) == nullptr)
      {
        newDict.insert(it->first, it->second);
      }
    }
    treeOfDicts.insert(nameNew, newDict);
    print(treeOfDicts, nameNew, out);
  }
}
