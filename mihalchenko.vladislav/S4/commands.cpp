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

void mihalchenko::print(mihalchenko::AVLTree<std::string, mihalchenko::AVLTree<long long, std::string>> &AVLTree)
{
  std::string name;
  std::cin >> name;
  auto dataset = AVLTree.find(name);
  if (dataset == AVLTree.end())
  {
    return;
  }
  else if ((*dataset).second.empty())
  {
    return;
  }

  std::cout << (*dataset).first << " ";
  for (auto it = (*dataset).second.begin(); it != (*dataset).second.end(); ++it)
  {
    std::cout << (*it).first << " " << (*it).second;
    ((++it) == (*dataset).second.end()) ? std::cout << "\n" : std::cout << ' ';
    it--;
  }
}

void mihalchenko::complement(mihalchenko::AVLTree<std::string, mihalchenko::AVLTree<long long, std::string>> &AVLTree)
{
  std::string name, nameFirst, nameSecond;
  std::cin >> name >> nameFirst >> nameSecond;
  auto firstData = AVLTree.find(nameFirst);
  auto secondData = AVLTree.find(nameSecond);
  if (firstData == AVLTree.end() || secondData == AVLTree.end())
  {
    return;
  }
  mihalchenko::AVLTree<long long, std::string> datasets{};
  for (auto it = (*firstData).second.begin(); it != (*firstData).second.end(); it++)
  {
    auto inSecondData = (*AVLTree.find(nameSecond)).second.find((*it).first);
    if (inSecondData == (*AVLTree.find(nameSecond)).second.end())
    {
      datasets.insert(*it);
    }
  }
  if (nameFirst == name)
  {
    AVLTree.erase(nameFirst);
    AVLTree.insert(name, datasets);
  }
  else
  {
    AVLTree.insert(name, datasets);
  }
}

void mihalchenko::intersect(mihalchenko::AVLTree<std::string, mihalchenko::AVLTree<long long, std::string>> &AVLTree)
{
  std::string name, nameFirst, nameSecond;
  std::cin >> name >> nameFirst >> nameSecond;
  auto firstData = AVLTree.find(nameFirst);
  auto secondData = AVLTree.find(nameSecond);
  if (firstData == AVLTree.end() || secondData == AVLTree.end())
  {
    return;
  }
  mihalchenko::AVLTree<long long, std::string> datasets{};
  for (auto it = (*firstData).second.begin(); it != (*firstData).second.end(); it++)
  {
    auto inSecondData = (*AVLTree.find(nameSecond)).second.find((*it).first);
    if (inSecondData != (*AVLTree.find(nameSecond)).second.end())
    {
      datasets.insert(*it);
    }
  }
  if (nameFirst == name)
  {
    AVLTree.erase(nameFirst);
    AVLTree.insert(name, datasets);
  }
  else
  {
    AVLTree.insert(name, datasets);
  }
}

void mihalchenko::unionAVL(mihalchenko::AVLTree<std::string, mihalchenko::AVLTree<long long, std::string>> &AVLTree)
{
  std::string name, nameFirst, nameSecond;
  std::cin >> name >> nameFirst >> nameSecond;
  auto firstData = AVLTree.find(nameFirst);
  auto secondData = AVLTree.find(nameSecond);
  if (firstData == AVLTree.end() || secondData == AVLTree.end())
  {
    return;
  }
  mihalchenko::AVLTree<long long, std::string> datasets{};
  for (auto it = (*firstData).second.begin(); it != (*firstData).second.end(); it++)
  {
    datasets.insert(*it);
  }
  for (auto it = (*secondData).second.begin(); it != (*secondData).second.end(); it++)
  {
    auto inSet = datasets.find((*it).first);
    if (inSet == datasets.end())
    {
      datasets.insert(*it);
    }
  }
  if (nameFirst == name)
  {
    AVLTree.erase(nameFirst);
    AVLTree.insert(name, datasets);
  }
  else if (nameSecond == name)
  {
    AVLTree.erase(nameSecond);
    AVLTree.insert(name, datasets);
  }
  else
  {
    AVLTree.insert(name, datasets);
  }
}

void mihalchenko::insertDataToTree(std::ifstream &input, typeParam &TreeAndLeaves, std::string &inputStr)
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
