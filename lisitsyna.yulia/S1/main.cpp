#include <iostream>
#include <sstream>
#include <string>
#include "list.hpp"

int main()
{
  List<std::pair<std::string, List<int>>> sequences;
  std::string line;
  while (getline(std::cin, line))
  {
    std::istringstream iss(line);
    std::string name;
    iss >> name;
    List<int> nums;
    int num;
  }
  sequences.push_back(std::make_pair(name, nums));
}
