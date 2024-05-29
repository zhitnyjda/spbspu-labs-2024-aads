#include "commands.hpp"
#include <string>
#include <iostream>
#include <cctype>
#include <functional>
#include <utility>

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
