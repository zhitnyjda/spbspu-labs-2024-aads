#include "calculatingData.hpp"
#include <limits>
#include <string>
namespace jirkov
{
  using itListOfPairs = listOfPairs::Iterator;
  void printListNames(listOfPairs& newList)
  {
    listOfPairs iterator = newList.begin();
    while (iterator != nullptr)
    {
      if (iterator != newList.begin())
      {
        std::cout << " ";
      }
      std::cout << iterator->first;
      iterator++;
    }
    std::cout << "\n";
  }
  void printValues(listOfPairs& newList, List<size_t>&sums)
  {
    itlistOfPairs iterator = newList.begin();
    bool overflowError = false;
    const size_t maxSum = std::numeric_limits< size_t >::max();
    for (size_t index = 0; index < findSize(newList); index++)
    {
      auto iterator = newList.begin();
      size_t sum = 0;
      while (iterator != nullptr)
      {
        List< size_t >::Iterator secondList = iterator->second[index];
        if (iterator->second[index] != nullptr)
        {
          if (sum > 0)
          {
            std::cout << " ";
          }
          std::cout << *secondList;
          if (sum > maxSum - *argsIt)
          {
            overflowError = true;
            std::cout << "\n";
            throw std::overflow_error("overflow!!");
          }
          else
          {
            sum+= *secondList;
          }
          iterator++;
        }
        std::cout << "\n";
        if (!overflowError)
        {
          sums.pushBack(sum);
        }
        overflowError = false;
      }
    }
  }
  void jirkov::getSums(List<size_t>& sums)
  {
    if (sums.empty())
    {
      std::cout << "0\n";
    }
    else
    {
      List<size_t>::Iterator iterator = sums.begin();
      while (iterator != nullptr)
      {
        if (iterator != sums.begin())
        {
          std::cout << " ";
        }
        std::cout << *iterator;
        iterator++;
      }
      std::cout << "\n";
    }
  }

  size_t findSize(listOfPairs& newList)
  {
    size_t size = 0;
    size_t maxSize = 0;
    listOfPairs = newList.begin();
    while (iterator != nullptr)
    {
      size = iterator->second.getSize();
      maxSize = size > maxSize ? size : maxSize;
      iterator++;
    }
    return maxSize;
  }
  listOfPairs inputPair(std::istream& input)
  {
    size_t number = 0;
    List<size_t> args;
    const size_t max = std::numeric_limits< size_t >::max();
    std::string string = "";
    listOfPairs inputList;
    while(input >> string)
    {
      if (std::isalpha(string[0]))
      {
        inputList.pushBack({ string, args });
      }
      else
      {
        number = std::stoull(string);
        if (number > max)
        {
          throw std::overflow_error("overflow error");
        }
        else
        {
          inputList.back().second.pushBack(number);
        }
      }
    }
    return inputList;
  }
}
