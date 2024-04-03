#include "AdditionalFunctions.hpp"
#include <sstream>
#include <limits>

namespace kaseev {
  int readList(const std::string &line, kaseev::List<std::pair<std::string, kaseev::List<unsigned long long>>> &arr, bool &marker)
  {
    std::istringstream iss(line);
    std::string ListName;
    if (!(iss >> ListName))
    {
      std::cerr << "Empty line! \n";
      return 1;
    }
    kaseev::List<unsigned long long> tempList;
    unsigned long long num;
    while (iss >> num)
    {
        if (num > std::numeric_limits<int>::max())
        {
          marker = true;
        }
        tempList.pushBack(num);
    }

    std::pair<std::string, kaseev::List<unsigned long long>> list_pair;
    list_pair.first = ListName;
    list_pair.second = kaseev::List<unsigned long long>(tempList);
    arr.pushBack(list_pair);

    if (marker)
    {
      return 1;
    }
    return 0;
  }

  unsigned long long sumNumbersInString(const std::string &line)
  {
    std::istringstream iss(line);
    long long sum = 0;
    long long num;
    while (iss >> num)
    {
      if (sum > std::numeric_limits<int>::max() - num) {
        std::cerr << "overflow\n";
        exit(1);
      }
      sum += num;
    }
    return sum;
  }

  void sumNumbersInArray(const kaseev::List<std::pair<std::string, kaseev::List<int>>> &sums, bool &marker)
  {
    if (!marker)
    {
      for (int i = 0; i < sums.size(); ++i)
      {
        const auto &pair = sums[i];
        const std::string &line = pair.first;
        int sum = 0;
        sum = sumNumbersInString(line);
        std::cout << sum;
        if (i < sums.size() - 1)
        {
          std::cout << " ";
        }
      }
      std::cout << "\n";
    }
  }

  void printListNames(const kaseev::List<std::pair<std::string, kaseev::List<unsigned long long>>> &arr)
  {
    bool marker = false;
    for (int i = 0; i < arr.size(); ++i)
    {
      std::pair<std::string, kaseev::List<unsigned long long>> list = arr[i];
      std::cout << list.first;
      if (i < arr.size() - 1)
      {
        std::cout << " ";
        marker = true;
      }
    }
    if (marker || !(arr.empty()))
    {
      std::cout << "\n";
    }
  }

  kaseev::List<std::pair<std::string, kaseev::List<int>>>
  calculateSumList(const kaseev::List<std::pair<std::string, kaseev::List<unsigned long long>>> &arr)
  {
    bool finished = false;
    int index = 0;
    kaseev::List<std::pair<std::string, kaseev::List<int>>> sum;
    int IfSumEmpty = 0;
    while (!finished)
    {
      finished = true;
      std::string currentString;
      for (int i = 0; i < arr.size(); ++i)
      {
        const kaseev::List<unsigned long long> &sublist = arr[i].second;

        if (index < sublist.size())
        {
          if (!currentString.empty())
          {
            currentString += " ";
          }

          currentString += std::to_string(sublist[index]);
          finished = false;
        }
      }

      if (!finished)
      {
        std::cout << currentString << "\n";
        sum.pushBack({currentString, kaseev::List<int>()});
      }

      index++;
    }
    if (sum.empty())
    {
      sum.pushBack({"", List<int>{IfSumEmpty}});
    }
    return sum;
  }
}
