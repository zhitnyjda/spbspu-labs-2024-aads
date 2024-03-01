// AdditionalFunctions.cpp
#include "AdditionalFunctions.hpp"
#include "sstream"

namespace kaseev {
  void readList(std::string &line, kaseev::List<std::pair<std::string, kaseev::List<int>>>& arr) {
    std::istringstream iss(line);
    std::string ListName;
    if (!(iss >> ListName)) {
      std::cerr << "Empty line!" << std::endl;
      return;
    }
    kaseev::List<int> tempList;
    int num;
    while (iss >> num) {
      tempList.pushBack(num);
    }
    std::pair<std::string, kaseev::List<int>> list_pair;
    list_pair.first = ListName;
    list_pair.second = tempList;
    arr.pushBack(list_pair);
  }
}
