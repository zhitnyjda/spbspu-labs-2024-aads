#include "DataProcessing.hpp"
#include <string>
#include <sstream>
#include "ErrorMessage.hpp"

namespace sukacheva
{
  BinaryTree inputTree(std::string& line)
  {
    std::istringstream iss(line);
    BinaryTree currentDict;
    int key;
    std::string value;
    while (iss >> key >> value)
    {
      currentDict.insert(key, value);
    }
    return currentDict;
  }

  void printResult(KeySum& result, std::ostream& out)
  {
    out << result.result << " ";
    while (!result.values.empty())
    {
      std::cout << result.values.front();
      result.values.pop();
      if (!result.values.empty())
      {
        std::cout << " ";
      }
    }
    std::cout << "\n";
  }

  void ascendingCommand(BinaryTree tree, std::ostream& out)
  {
    if (tree.empty())
    {
      EmptyMessage(out);
      return;
    }
    KeySum result;
    tree.traverse_lnr(result);
    printResult(result, out);
  }

  void descendingCommand(BinaryTree tree, std::ostream& out)
  {
    if (tree.empty())
    {
      EmptyMessage(out);
      return;
    }
    KeySum result;
    tree.traverse_rnl(result);
    printResult(result, out);
  }

  void breadthCommand(BinaryTree tree, std::ostream& out)
  {
    if (tree.empty())
    {
      EmptyMessage(out);
      return;
    }
    KeySum result;
    tree.traverse_breadth(result);
    printResult(result, out);
  }
}
