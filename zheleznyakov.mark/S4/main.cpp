#include <iostream>
#include <string>
#include "tree.hpp"

int main()
{
  using namespace zheleznyakov;
  zheleznyakov::Tree< std::string, int > tree;
  std::cout << tree.size() << ' ' << (tree.empty() ? "Empty" : "Not empty") << '\n';
  tree.push("key1", 1);
  tree.push("key2", 2);
  std::cout << tree.at("key1") << '\n';
  std::cout << tree.at("key2") << '\n';
  std::cout << tree.size() << ' ' << (tree.empty() ? "Empty" : "Not empty") << '\n';
  return 0;
}
