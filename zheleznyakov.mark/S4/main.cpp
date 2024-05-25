#include <iostream>
#include <string>
#include "tree.hpp"

int main()
{
  using namespace zheleznyakov;
  using subtree_t = Tree< std::string, int >;
  subtree_t tree;
  std::cout << tree.size() << ' ' << (tree.empty() ? "Empty" : "Not empty") << '\n';
  tree.push("key1", 1);
  tree.push("key2", 2);
  std::cout << tree.at("key1") << '\n';
  std::cout << tree.at("key2") << '\n';
  std::cout << tree.size() << ' ' << (tree.empty() ? "Empty" : "Not empty") << '\n';
  Tree< std::string, subtree_t > uptree;
  uptree.push("key3", tree);
  std::cout << uptree.at("key3").at("key1") << '\n';
  return 0;
}
