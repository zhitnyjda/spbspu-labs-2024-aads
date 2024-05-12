#define private public // не бейте, это для дебага
#include <iostream>
#include "tree.hpp"

int main()
{
  // Да здравствуют тесты
  using namespace miheev;
  Tree< int, int > tree;
  tree.rawInsert(2, 2);
  tree.rawInsert(4, 4);
  tree.rawInsert(-1000, -1000);
  tree.rawInsert(-3, 2);
  tree.rawInsert(1, 1);
  tree.printKeys();
  std::cout << '\n';
  // tree.printValues(std::cout);
  Tree <int, int> tree2;
  tree2 = tree;
  tree2.printKeys();
  Tree< int, NULL > set;
  std::cout << '\n';
  return 0;
}
