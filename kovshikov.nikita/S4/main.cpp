#include <iostream>
#include <string>
#include <fstream>
#include "BinarySearchTree.hpp"
#include "treeProcess.hpp"

int main(int argc, char ** argv )
{
  if(argc != 2)
  {
    std::cerr << "NO FILE SPECIFIED" << "\n";
    return 1;
  }

  using namespace kovshikov;
  Tree< std::string, Tree< long long, std::string > > allTree;
  std::ifstream file(argv[1]);
  readData(file, allTree);

  Tree< std::string, std::function < void(Tree< std::string, Tree< long long, std::string > >&) > > commands;
  commands.insert("print", print);
  commands.insert("complement", getComplement);
  commands.insert("intersect", getIntersect);
  commands.at("intersect")(allTree);
 // commands.at("complement")(allTree);
  commands.at("print")(allTree);
  //std::cout << allTree.getSize() << "\n";
  return 0;
}






/*  long long size = allTree.getSize();
  std::cout << size << "\n";
  std::cout << allTree.at("first").getSize() << "\n";
  std::cout << allTree.at("second").getSize() << "\n";
  std::cout << allTree.at("third").getSize() << "\n";
  std::cout << "__________________" << "\n";
  std::cout << allTree.at("third").at(6) << " " << allTree.at("third").at(7) << " " << allTree.at("third").at(10) << "\n";
  std::cout << allTree.at("third").at(11) << "\n";
}
*/



/*  using namespace kovshikov;
  Tree< size_t, std::string > tree;

  std::cout << tree.getSize() << " " << tree.isEmpty() << "\n"; //ok
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
  std::cout << tree.getSize() << "\n";


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
  std::cout << tree.getSize() << " " << tree.isEmpty() << "\n"; //ok
  tree.erase(10);
  tree.erase(13);
  tree.erase(16);
  tree.erase(8);
  tree.erase(20);
  tree.erase(18);
  std::cout << tree.getSize() << " " << tree.isEmpty() << "\n"; //ok
  std::cout << tree[5] << "\n";
  tree[100] = "hangred";
  std::cout << tree[100] << "\n";
  tree[75];
  std::cout << tree.count(75) << "\n";
  try
  {
    tree.at(8);
  }
  catch(const std::out_of_range& error)
  {
    std::cout << "ERROR\n";
  }
  Tree< size_t, std::string > otherTree;
  otherTree.insert(1, "one");
  otherTree.insert(2, "two");
  tree.swap(otherTree); //ok
  std::cout << tree.getSize() << "\n";
  std::cout << otherTree.getSize() << "\n";
  otherTree.clear(); //ok
  std::cout << otherTree.isEmpty() << "\n";
  Tree< size_t, std::string > dub(tree);
  std::cout << dub.getSize() << "\n";
  tree.clear();
  std::cout << dub.getSize() << "\n";
  return 0;
*/
