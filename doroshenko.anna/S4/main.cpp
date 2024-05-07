#include <iostream>
#include <string>
#include <fstream>
#include "treeProcess.hpp"

int main()
{
	using namespace doroshenko;
	BST< std::string, BST< long long, std::string > > treeOfDicts;
	BST< long long, std::string > dict2;
	//inputTree(std::cin, treeOfDicts);

	std::string name1 = "dict1";
	long long key1 = 1;
	std::string value1 = "value1";

	std::string name2 = "dict2";
	long long key3 = 3;
	std::string value3 = "value3";

	long long key2 = 2;
	std::string value2 = "value2";
	BST< long long, std::string> dict1;
	dict1.insert(key1, value1);
	dict1.insert(key2, value2);

	dict2.insert(key1, value1);
	dict2.insert(key3, value3);

	std::cout << "\n";

  /*for (auto it = dict.cbegin(); it != dict.cend(); ++it)
  {
	  std::cout << "(" << it->first << ", " << it->second << ") " << "\n";
  }*/
	treeOfDicts.insert(name1, dict1);
	treeOfDicts.insert(name2, dict2);

	complement(treeOfDicts);
	print(treeOfDicts);
}
