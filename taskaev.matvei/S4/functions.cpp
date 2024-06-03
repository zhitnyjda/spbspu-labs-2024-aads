#include "functions.hpp"
#include <string>
using namespace taskaev;

void createTree(std::istream& in, Tree& tree)
{
  std::string data = "";
  while (std::getline(in, data))
  {
    if (!data.empty())
    {
      std::string temps = "";
      std::string names = "";
      size_t key = 0;
      std::string val = "";
      BSTree< size_t, std::string > tre;
      bool flag = true;
      size_t i = 0;
      while (i < data.length())
      {
        if (data[i] != ' ')
        {
          temps += data[i];
        }
        else if (data[i] == ' ' && flag == true)
        {
          names = temps;
          temps = "";
          flag = false;
        }
        else
        {
          if (std::isdigit(temps[0]))
          {
            key = std::stoll(temps);
            temps = "";
          }
          else
          {
            val = temps;
            temps = "";
            tre.insert(key, val);
          }
        }
        i++;
      }
      if (key == 0)
      {
        names = temps;
      }
      if (!val.empty())
      {
        val = temps;
        tre.insert(key, val);
      }
      tree.insert(names, tre);
    }
  }
}

void helpPrint(SubTree& tree, Iterator it, Iterator end)
{
  if (iterator != end)
  {
    std::pair< size_t, std::string > pair = *iterator;
    if (++iterator == end)
    {
      std::cout << pair.first << " " << pair.second << "\n";
    }
    else
    {
      std::cout << pair.first << " " << pair.second << " ";
    }
    printTree(tree, iterator, end);
  }
}

void print(Tree& tree)
{
  std::string datas;
  std::cin >> datas;
  BSTree< size_t, std::string > tres = tree.at(datas);
  if (tres.empty())
  {
    errorEmpty(std::cout);
  }
  else
  {
    BSTree< size_t, std::string >::Iterator iterator = tres.begin();
    BSTree< size_t, std::string >::Iterator end = tres.end();
    std::cout << datas << " ";
    printTree(tres, iterator, end); // типо тут рекурсия вывода
  }
}

void complement(Tree& tree)
{
  std::string names, oneName, twoName;
  std::cin >> names >> oneName >> twoName;
  BSTree< size_t, std::string > tres;
  findComplementItems(tree.at(oneName), tree.at(twoName), tres);
  findComplementItems(tree.at(twoName), tree.at(oneName), tres);
  tree.insert(names, tres);
}

void findcomplement(SubTree& two, SubTree& one, SubTree& tree)
{
  for (auto it = sourceTree.begin(); it != sourceTree.end(); ++it) {
    bool flag = false;
    for (auto iter = otherTree.begin(); iter != otherTree.end(); ++iter) {
      if (it->first == iter->first) {
        flag = true;
        break;
      }
    }
    if (!flag) {
      newTree.insert(*it);
    }
  }
}

void intersect(Tree& tree)
{
  std::string names, oneName, twoName;
  std::cin >> names >> oneName >> twoName;
  BSTree< size_t, std::string > tres;
  BSTree< size_t, std::string > oneTres = tree.at(oneName);
  BSTree< size_t, std::string > twoTres = tree.at(twoName);
  for (auto it = oneTres.begin(); it != oneTres.end(); ++it)
  {
    size_t key = it->first;
    if (twoTres.find(key) != twoTres.cend()) //проверка на элементстаким ключом во 2 дереве
    {
      tres.insert(*it);
    }
  }
  tree.insert(names, tres);
}

SubTree mergeTrees(SubTree& treeOne, SubTree& treeTwo)
{
  BSTree< size_t, std::string > result = treeOne;

  for (auto it = treeTwo.begin(); it != treeTwo.end(); ++it)
  {
    size_t key = it->first;
    if (result.find(key) == result.cend())
    {
      result.insert(*it);
    }
  }
  return result;
}

void unions(Tree& tree)
{
  std::string names, oneName, twoName;
  std::cin >> names >> oneName >> twoName;
  BSTree<size_t, std::string> newTree = mergeTrees(tree.at(oneName), tree.at(twoName));
  tree.insert(names, newTree);
}

void errorInvalid(std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
}

void errorEmpty(std::ostream& out)
{
  out << "<EMPTY>\n";
}

