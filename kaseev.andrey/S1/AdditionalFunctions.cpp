// AdditionalFunctions.cpp
#include "AdditionalFunctions.hpp"
#include "sstream"

namespace kaseev {
  void readList(const std::string &line, kaseev::List<std::pair<std::string, kaseev::List<int>>>& arr) {
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

int sumNumbersInString(const std::string& line) {
  std::istringstream iss(line);
  int sum = 0;
  int num;
  while (iss >> num) {
    sum += num;
  }
  return sum;
}

void sumNumbersInArray(const kaseev::List<std::string>& sums) {
  for (int i = 0; i < sums.size(); ++i) {
    const std::string& line = sums[i];
    const int sum = sumNumbersInString(line);
    std::cout << "Sum of numbers in " << line << ": " << sum << std::endl;
  }
}
