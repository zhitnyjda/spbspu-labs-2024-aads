#include <iostream>
#include "binarySearchTree.hpp"

using namespace anikanov;

int main()
{
  BinarySearchTree< int, std::string, std::less<> > bst;
  bst.push(1, "one");
  bst.push(2, "two");
  bst.push(3, "three");

  std::cout << "Size: " << bst.size() << std::endl;
  std::cout << "Empty: " << std::boolalpha << bst.empty() << std::endl;

  bst[4] = "four";
  bst[2] = "two new";

  std::cout << "key 4: " << bst[4] << std::endl;
  std::cout << "key 2: " << bst[2] << std::endl;

  bst.print();

  bst.drop(2);
  bst.print();

  return 0;
}
