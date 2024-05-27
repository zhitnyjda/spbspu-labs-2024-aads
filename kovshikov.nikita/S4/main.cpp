#include "BinarySearchTree.hpp"
#include <iostream>

int main()
{
  using namespace kovshikov;
  Tree< size_t, std::string > tree;
/*  std::cout << tree.getSize() << " " << tree.isEmpty() << "\n"; //ok
  tree.insert(1, "one");
  tree.insert(3, "three");
  tree.insert(2, "two");
//  tree.printStart(); //
  tree.insert(7, "seven");
  tree.insert(6, "six");
  tree.insert(4, "four");
  tree.insert(5, "five");
  std::cout << tree.getSize() << " " << tree.isEmpty() << "\n"; //ok
  std::cout << tree.count(3) << " " << tree.count(8) << "\n"; //ok
  std::cout << tree.at(6) << "\n"; //ok
//  std::cout << tree[6] << "\n";
  tree.erase(3);
  std::cout << tree.getSize() << "\n";*/
  tree.insert(10, "ten");
  tree.insert(8, "eight");
  tree.insert(15, "fifteen");
  tree.insert(5, "five");
  tree.insert(9, "nine");
  tree.insert(13, "theerteen");
  tree.insert(17, "seventeen");
  tree.insert(4, "four");
  tree.insert(7, "seven");
  tree.insert(12, "twelve");
  tree.insert(14, "fourteen");
  tree.insert(16, "sixteen");
  tree.insert(19, "ninteen");
  tree.insert(18, "eighteen");
  tree.insert(20, "twenty");
  std::cout << tree.getSize() << " " << tree.isEmpty() << "\n";
  tree.erase(13);
  tree.erase(16);
  tree.erase(8);
  //tree.erase(10)
  std::cout << tree.getSize() << " " << tree.isEmpty() << "\n";
  return 0;
}
