#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <binarySearchTree.hpp>

int main(int argc, char *argv[])
{
  using namespace anikanov;
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [ascending|descending|breadth] filename\n";
    return 1;
  }

  std::string mode = argv[1];
  std::string filename = argv[2];
  BinarySearchTree< int, std::string, std::less<> > bst;
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Could not open file " << filename << "\n";
    return 1;
  }

  int key;
  std::string value;
  while (file >> key >> value) {
    bst.push(key, value);
  }
  file.close();

  struct Result {
    void operator()(const std::pair< const int, std::string > &key_value)
    {
      result += key_value.first;
      values += key_value.second + " ";
    }

    int result = 0;
    std::string values;
  } result;

  if (mode == "ascending") {
    bst.traverse_lnr(result);
  } else if (mode == "descending") {
    bst.traverse_rnl(result);
  } else if (mode == "breadth") {
    bst.traverse_breadth(result);
  } else {
    std::cerr << "Invalid traversal mode\n";
    return 1;
  }

  std::cout << result.result << " " << result.values << "\n";
  return 0;
}
