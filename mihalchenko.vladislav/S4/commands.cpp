#include "commands.hpp"
#include <string>
#include <iostream>
#include <cctype>
#include <functional>
#include <utility>

std::string mihalchenko::resiveString(std::string &inputStr, size_t &pos, bool flag)
{
  std::string result = "";
  while (pos < inputStr.length() && inputStr[pos] != ' ')
  {
    if ((flag) || ((!flag) && std::isdigit(inputStr[pos])))
    {
      result += inputStr[pos++];
    }
    else if (!flag)
    {
      break;
    }
  }
  pos++;
  return result;
}

/*void mihalchenko::printErrorMessage(std::ostream & out)
{
  out << "ERROR\n";
}*/

void mihalchenko::printInvalidCommand(std::ostream &out)
{
  out << "<INVALID COMMAND>\n";
}

void mihalchenko::printEmptyMessage(std::ostream &out)
{
  out << "EMPTY\n";
}

void mihalchenko::print(typeParam &AVLTree)
{
  std::string name;
  std::cin >> name;
  auto iterList = AVLTree.find(name);
  if (iterList == AVLTree.end())
  {
    printInvalidCommand(std::cout);
    return;
  }
  else if ((*iterList).second.empty())
  {
    printEmptyMessage(std::cout);
    return;
  }
  // size_t lenOfTree = (*iterList).second.getSize();
  size_t lenOfTree = 0;
  for (auto it = (*iterList).second.begin(); it != (*iterList).second.end(); ++it)
  {
    lenOfTree++;
  }
  std::cout << (*iterList).first << " ";
  for (auto it = (*iterList).second.begin(); it != (*iterList).second.end(); ++it)
  {
    std::cout << (*it).first << " " << (*it).second;
    (lenOfTree == 1) ? std::cout << "\n" : std::cout << ' ';
    lenOfTree--;
  }
}

void mihalchenko::complement(typeParam &AVLTree)
{
  std::string nameNewGlossary, nameOneGlossary, nameTwoGlossary;
  std::cin >> nameNewGlossary >> nameOneGlossary >> nameTwoGlossary;
  if (((AVLTree.find(nameOneGlossary) == AVLTree.end()) || (AVLTree.find(nameTwoGlossary) == AVLTree.end())))
  {
    printInvalidCommand(std::cout);
    return;
  }
  mihalchenko::AVLTree<long long, std::string> complementTree{};
  for (auto it = (*AVLTree.find(nameOneGlossary)).second.begin(); it != (*AVLTree.find(nameOneGlossary)).second.end(); it++)
  {
    size_t countEqual = 0;
    for (auto itTwo = (*AVLTree.find(nameTwoGlossary)).second.begin(); itTwo != (*AVLTree.find(nameTwoGlossary)).second.end(); itTwo++)
    {
      if (((*it).first == (*itTwo).first) || ((*it).second == (*itTwo).second))
      {
        countEqual++;
      }
    }
    if (!countEqual)
    {
      complementTree.insert(*it);
    }
  }
  if (nameOneGlossary == nameNewGlossary)
  {
    AVLTree.erase(nameOneGlossary);
  }
  AVLTree.insert(nameNewGlossary, complementTree);
}

void mihalchenko::intersect(typeParam &AVLTree)
{
  std::string nameNewGlossary, nameOneGlossary, nameTwoGlossary;
  std::cin >> nameNewGlossary >> nameOneGlossary >> nameTwoGlossary;
  if (((AVLTree.find(nameOneGlossary) == AVLTree.end()) || (AVLTree.find(nameTwoGlossary) == AVLTree.end())))
  {
    printInvalidCommand(std::cout);
    return;
  }
  mihalchenko::AVLTree<long long, std::string> intersectTree{};
  for (auto it = (*AVLTree.find(nameOneGlossary)).second.begin(); it != (*AVLTree.find(nameOneGlossary)).second.end(); it++)
  {
    size_t countEqual = 0;
    for (auto itTwo = (*AVLTree.find(nameTwoGlossary)).second.begin(); itTwo != (*AVLTree.find(nameTwoGlossary)).second.end(); itTwo++)
    {
      if (((*it).first == (*itTwo).first) || ((*it).second == (*itTwo).second))
      {
        countEqual++;
      }
    }
    if (countEqual)
    {
      intersectTree.insert(*it);
    }
  }
  if (nameOneGlossary == nameNewGlossary)
  {
    AVLTree.erase(nameOneGlossary);
  }
  AVLTree.insert(nameNewGlossary, intersectTree);
}

void mihalchenko::unionAVL(typeParam &AVLTree)
{
  std::string nameNewGlossary, nameOneGlossary, nameTwoGlossary;
  std::cin >> nameNewGlossary >> nameOneGlossary >> nameTwoGlossary;
  if (((AVLTree.find(nameOneGlossary) == AVLTree.end()) || (AVLTree.find(nameTwoGlossary) == AVLTree.end())))
  {
    printInvalidCommand(std::cout);
    return;
  }
  mihalchenko::AVLTree<long long, std::string> unionTree{};
  for (auto it = (*AVLTree.find(nameOneGlossary)).second.begin(); it != (*AVLTree.find(nameOneGlossary)).second.end(); it++)
  {
    unionTree.insert(*it);
  }
  for (auto it = (*AVLTree.find(nameTwoGlossary)).second.begin(); it != (*AVLTree.find(nameTwoGlossary)).second.end(); it++)
  {
    size_t countEqual = 0;
    for (auto itTwo = (*AVLTree.find(nameOneGlossary)).second.begin(); itTwo != (*AVLTree.find(nameOneGlossary)).second.end(); itTwo++)
    {
      if (((*it).first == (*itTwo).first) || ((*it).second == (*itTwo).second))
      {
        countEqual++;
      }
    }
    if (!countEqual)
    {
      unionTree.insert(*it);
    }
  }
  if (nameOneGlossary == nameNewGlossary)
  {
    AVLTree.erase(nameOneGlossary);
  }
  else if (nameTwoGlossary == nameNewGlossary)
  {
    AVLTree.erase(nameTwoGlossary);
  }

  AVLTree.insert(nameNewGlossary, unionTree);
}

void mihalchenko::insertDataToTree(typeParam &TreeAndLeaves, std::string &inputStr)
{
  AVLTree<long long, std::string> branchAndLeaves{};
  size_t pos = 0;
  std::string nameGlossary = resiveString(inputStr, pos, true);
  while (pos < inputStr.length())
  {
    long long key = std::stoll(resiveString(inputStr, pos, false));
    std::string value = resiveString(inputStr, pos, true);
    branchAndLeaves.insert(key, value);
  }
  TreeAndLeaves.insert(nameGlossary, branchAndLeaves);
}
