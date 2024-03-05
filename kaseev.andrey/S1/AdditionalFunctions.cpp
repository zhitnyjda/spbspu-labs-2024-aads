// AdditionalFunctions.cpp
#include "AdditionalFunctions.hpp"
#include "sstream"

namespace kaseev {
  void readList(const std::string &line, kaseev::List<std::pair<std::string, kaseev::List<int>>> &arr)
  {
    std::istringstream iss(line);
    std::string ListName;
    if (!(iss >> ListName))
    {
      std::cerr << "Empty line! \n";
      return;
    }
    kaseev::List<int> tempList;
    int num;
    while (iss >> num)
    {
      tempList.pushBack(num);
    }
    std::pair<std::string, kaseev::List<int>> list_pair;
    list_pair.first = ListName;
    list_pair.second = tempList;
    arr.pushBack(list_pair);
  }

  int sumNumbersInString(const std::string &line)
  {
    std::istringstream iss(line);
    int sum = 0;
    int num;
    while (iss >> num)
    {
      sum += num;
    }
    return sum;
  }

  void sumNumbersInArray(const kaseev::List<std::pair<std::string, kaseev::List<int>>> &sums)
  {
    for (int i = 0; i < sums.size(); ++i)
    {
      const auto &pair = sums[i];
      const std::string &line = pair.first;
      int sum = 0;
      sum = sumNumbersInString(line);
      std::cout << sum << " ";
    }
    std::cout << "\n";
  }
}
