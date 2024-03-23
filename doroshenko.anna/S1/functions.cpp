#include "functions.hpp"
#include <limits>

doroshenko::List< std::pair< std::string, doroshenko::List< size_t > > > doroshenko::listInput(std::istream& input)
{
  std::string inputString = "";
  doroshenko::List< std::pair< std::string, doroshenko::List< size_t > > > inputList;
  unsigned long long readNumber = 0;
  const size_t maximum = std::numeric_limits< size_t >::max();
  while(input >> inputString)
  {
    if (std::isalpha(inputString[0]))
    {
      inputList.pushBack({ inputString, doroshenko::List< size_t >() });
    }
    else
    {
      readNumber = std::stoull(inputString);
      if (readNumber > maximum)
      {
        throw std::overflow_error("overflow error");
      }
      else
      {
        inputList.tail_->data.second.pushBack(readNumber);
      }
    }
  }
  return inputList;
}

void doroshenko::listOutput(doroshenko::List< std::pair< std::string, doroshenko::List< size_t > > > list, std::ostream& output)
{
  ListIterator<std::pair< std::string, List< size_t > > > iterator = list.begin();
  size_t maxSize = getMaxSize(list);
  List< size_t > sums;
  ListIterator< size_t > iteratorForSums;
  const size_t maximum = std::numeric_limits< size_t >::max();
  size_t sum = 0;
  bool overflowError = false;
  if (!list.isEmpty())
  {
    while (iterator.node)
    {
      if (iterator.node != list.head_)
      {
        output << " ";
      }
      output << iterator.node->data.first;
      iterator++;
    }
    output << "\n";
    for (size_t index = 0; index < maxSize; index++)
    {
      iterator = list.begin();
      while (iterator.node)
      {
        if (iterator.node->data.second[index] != nullptr)
        {
          if (sum > 0)
          {
            output << " ";
          }
          std::cout << iterator.node->data.second[index]->data;
          if (maximum - sum < iterator.node->data.second[index]->data)
          {
            overflowError = true;
            output << "\n";
            throw std::overflow_error("overflow error");
          }
          else
          {
            sum = sum + iterator.node->data.second[index]->data;
          }
        }
        iterator++;
      }
      if (!overflowError)
      {
        sums.pushBack(sum);
      }
      sum = 0;
      overflowError = false;
      output << "\n";
    }

    iteratorForSums = sums.begin();
    if (sums.isEmpty())
    {
      output << 0;
    }
    else
    {
      while (iteratorForSums.node)
      {
        if (iteratorForSums.node != nullptr)
        {
          if (iteratorForSums.node != sums.head_)
          {
            output << " ";
          }
          output << iteratorForSums.node->data;
        }
        iteratorForSums++;
      }
    }
    output << "\n";
  }
  else
  {
    output << 0 << "\n";
  }
}

size_t doroshenko::getMaxSize(doroshenko::List< std::pair< std::string, doroshenko::List< size_t > > >& list)
{
  size_t size = 0;
  size_t maxSize = 0;
  doroshenko::ListIterator< std::pair< std::string, doroshenko::List< size_t > > > iterator = list.begin();
  while (iterator.node)
  {
    size = iterator.node->data.second.getSize();
    maxSize = size > maxSize ? size : maxSize;
    iterator++;
  }
  return maxSize;
}
