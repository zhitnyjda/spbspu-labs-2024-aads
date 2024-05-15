#define private public // не бейте, это для дебага
#include <iostream>
#include "tree.hpp"
#include <map>

int main()
{
  // Да здравствуют тесты
  using namespace miheev;
  Tree< int, int > tree;
  tree.insert(7, 7);
  tree.insert(5, 5);
  tree.insert(1, 1);
  tree.insert(13, 13);
  tree.insert(15, 15);
  tree.insert(4, 4);
  tree.insert(3, 3);
  tree.insert(2, 2);
  tree.insert(6, 6);

  tree.erase(2);
  tree.erase(3);
  // std::cout << tree.contains(2) << '\n';
  // tree[111] = 112;
  // std::cout << tree.at(111) << '\n';

  // std::map< int, int > m;
  // m.insert({1, 1});
  // m.insert({2, 2});
  // auto iter(m.begin());
  // std::cout << (--iter)->first << '\n';
  // std::cout << (--iter)->first << '\n';
  // std::cout << (--iter)->first << '\n';
  // tree.insert(1, 1);
  // tree.insert(2, 2);
  // tree.insert(3, 3);
  // tree.insert(4, 4);
  // tree.insert(5, 5);
  // tree.insert(6, 6);
  // tree.insert(7, 7);
  // tree.insert(8, 8);
  // tree.insert(9, 9);
  // tree.insert(10, 10);
  // tree.insert(11, 11);
  Tree< int, int >::Iterator iter = tree.begin();
  for (; iter != tree.end();)
  {
    std::cout << iter->first << '\n';
    ++iter;
  }
  // tree.clear();
  // tree.printKeys();
  // std::cout << "\n";
  // tree.rawDelete(13);
  // tree.printKeys();
  // std::cout << '\n';
  // tree.printKeys(std::cout);
  // std::cout << '\n';
  return 0;
}
