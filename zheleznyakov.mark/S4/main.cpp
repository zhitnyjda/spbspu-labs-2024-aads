#include <iostream>
#include <string>
#include "tree.hpp"

int main()
{
  using namespace zheleznyakov;
  zheleznyakov::Tree< std::string, int > tree;
  tree.push("key5", 3);
  tree.push("key2", 5);
  tree.push("key4", 15);
  tree.push("key6", 12);
  tree.push("key3", 7);
  tree.push("key1", 10);
  tree.push("key7", 17);
  std::cout << tree.size() << std::endl;
  return 0;
}
