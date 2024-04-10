#include "DataProcessing.hpp"
#include <string>
#include <utility>
#include <limits>
#include "List.hpp"

namespace sukacheva {

  using itListOfPairs = listOfPairs::Iterator;
  listOfPairs listInput(std::istream& in)
  {
    std::string name = "";
    List< size_t > args;
    listOfPairs resultList;
    in >> name;
    while (in) {
      resultList.pushBack({ name, args });
      while (in >> name && std::isdigit(name[0])) {
        resultList.back().second.pushBack(std::stoul(name));
      }
    }
    return resultList;
  }

  size_t maxListSize(listOfPairs& newList)
  {
    size_t size = 0;
    size_t maxSize = 0;
    itListOfPairs it = newList.begin();
    while (it != nullptr) {
      size = it->second.getSize();
      maxSize = (maxSize < size ? size : maxSize);
      it++;
    }
    return maxSize;
  }

  void printNameList(listOfPairs& newList)
  {
    itListOfPairs it = newList.begin();
    do {
      std::cout << it->first;
      if (it++ != newList.end()) {
        std::cout << " ";
      }
    } while (it != nullptr);
    std::cout << "\n";
  }

  void printArgs(listOfPairs& newList)
  {
    itListOfPairs it = newList.begin();
    List<size_t> sumOfArgs;
    const size_t maxSum = std::numeric_limits< size_t >::max();
    bool overflowFlag = false;
    for (size_t i = 0; i < maxListSize(newList); i++) {
      it = newList.begin();
      size_t sum = 0;
      while (it != nullptr) {
        List< size_t >::Iterator argsIt = it.getData().second[i];
        if (it->second[i])
        {
          if (sum != 0) {
            std::cout << " ";
          }
          std::cout << argsIt.getData();
          if (sum > maxSum - argsIt.getData())
          {
            overflowFlag = true;
            std::cout << "\n";
            throw std::overflow_error("overflow!!");
          }
          else
          {
            sum += argsIt.getData();
          }
        }
        it++;
      }
      std::cout << "\n";
      sumOfArgs.pushBack(sum);
    }
    if (!overflowFlag)
    {
      List<size_t>::Iterator itSum = sumOfArgs.begin();
      do {
        std::cout << *itSum;
        if (itSum++ != nullptr) {
          std::cout << " ";
        }
      } while (itSum != nullptr);
      std::cout << "\n";
    }
  }
}
