#include "BinarySearchTree.hpp"
#include <iostream>

int main()
{
  using namespace kovshikov;
  Tree< size_t, std::string > tree;
  std::cout << tree.getSize() << " " << tree.isEmpty() << "\n"; //ok
  tree.insert(1, "one");
  tree.insert(3, "three");
  tree.insert(2, "two");
  tree.insert(7, "seven");
  tree.insert(6, "six");
  tree.insert(4, "four");
//  tree.insert(1, "one");
//  tree.insert(5, "five");
  std::cout << tree.getSize() << " " << tree.isEmpty() << "\n"; //ERROR
  //после добавления элементов возникает как будто бы бесконечный цикл при getSize()
  //и Empty()
  return 0;
}
