#include <iostream>
#include <string>
#include <memory>
#include "list.hpp"

anikanov::List< std::string > split(const std::string &str);

int main()
{
  using namespace anikanov;

  using list = List< unsigned long long >;
  using mainList = List< std::pair< std::string, list > >;

  std::unique_ptr< mainList > lists(new mainList);
  std::string inputName;
  std::string line;

  line = "";
  std::getline(std::cin, line);
  while (!std::cin.eof()) {
    if (line.empty()) {
      line = "";
      std::getline(std::cin, line);
      continue;
    }
    List< std::string > inputList = split(line);
    list numbers;
    inputName = inputList[0];
    inputList.pop(0);
    for (auto &i: inputList) {
      numbers.push_back(std::stoull(i));
    }

    std::pair< std::string, List< unsigned long long > > listPair;
    listPair.first = inputName;
    for (auto num: numbers) {
      listPair.second.push_back(num);
    }
    lists->push_back(listPair);
    line = "";
    std::getline(std::cin, line);
  }


  for (auto it = lists->begin(); it != lists->end();) {
    std::cout << it->first;
    if (++it != lists->end()) {
      std::cout << " ";
    }
  }

  if (lists->empty()) {
    std::cout << "0\n";
    return 0;
  } else {
    std::cout << "\n";
  }

  bool finished = false;
  bool startPrint = false;
  size_t idx = 0;
  List< unsigned long long > sums;
  bool badSum = false;

  while (!finished) {
    finished = true;
    startPrint = true;
    for (auto listIter = lists->begin(); listIter != lists->end(); ++listIter) {
      const auto &list = *listIter;
      if (idx < list.second.size()) {
        if (finished) {
          sums.push_back(0);
          finished = false;
        }
        auto numIter = list.second.begin();
        for (size_t i = 0; i < idx; ++i) {
          numIter++;
        }
        if (startPrint) {
          std::cout << *numIter;
          startPrint = false;
        } else {
          std::cout << " " << *numIter;
        }
        if (*sums.back() + *numIter < std::max(*sums.back(), *numIter)) {
          badSum = true;
        }
        *sums.back() += *numIter;
      }
    }
    std::cout << (finished ? "" : "\n");
    idx++;
  }

  if (badSum) {
    std::cerr << "overflow\n";
    return 1;
  }

  for (auto sumIter = sums.begin(); sumIter != sums.end();) {
    std::cout << *sumIter;
    if (++sumIter != sums.end()) {
      std::cout << " ";
    }
  }

  if (sums.empty()) {
    std::cout << "0";
  }

  std::cout << "\n";
  return 0;
}

anikanov::List< std::string > split(const std::string &str)
{
  anikanov::List< std::string > list;
  std::string cur = "";
  for (char pos : str) {
    if (pos != ' ') {
      cur += pos;
    } else if (!cur.empty()) {
      list.push_back(cur);
      cur = "";
    }
  }
  if (!cur.empty()) {
    list.push_back(cur);
  }
  return list;
}
