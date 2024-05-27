#include "BinarySearchTree.hpp"
#include <iostream>

int main()
{
  using namespace kovshikov;
  Tree< size_t, std::string > tree;
  std::cout << tree.getSize() << " " << tree.isEmpty() << "\n"; //ok
  tree.insert(1, "one");
  std::cout << "AAA\n"; //
  tree.insert(3, "three");
  tree.insert(2, "two");
  //ОШИБКА В БАЛАНСИРОВКЕ ПРОЯВЛЯЕТСЯ ПОСЛЕ ДОБАВЛЕНИЯ 2;
// std::cout << tree.getSize() << " " << tree.isEmpty() << "\n"; //ok
  return 0;
}
