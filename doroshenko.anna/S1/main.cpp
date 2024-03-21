#include "list.hpp"
#include "functions.hpp"

int main()
{
  using namespace doroshenko;
  List< std::pair< std::string, List< size_t > > > list = listInput(std::cin);
  ListIterator<std::pair< std::string, List< size_t > > > iterator = list.begin();
  size_t maxSize = getMaxSize(list);
  List< size_t > sums;
  ListIterator< size_t > iteratorForSums;
  size_t sum = 0;
  if (!list.isEmpty())
  {
    while (iterator.node)
    {
      if (iterator.node != list.head_)
      {
        std::cout << " ";
      }
      std::cout << iterator.node->data.first;
      iterator++;
    }
    std::cout << '\n';
    for (size_t index = 0; index < maxSize; index++)
    {
      iterator = list.begin();
      while (iterator.node)
      {
        if (iterator.node->data.second[index] != nullptr)
        {
          if (sum > 0)
          {
            std::cout << " ";
          }
          std::cout << iterator.node->data.second[index]->data;
          sum = sum + iterator.node->data.second[index]->data;
        }
        iterator++;
      }
      sums.pushBack(sum);
      sum = 0;
      std::cout << '\n';
    }

    iteratorForSums = sums.begin();
    if (sums.isEmpty())
    {
      std::cout << 0;
    }
    else
    {
      while (iteratorForSums.node)
      {
        if (iteratorForSums.node != nullptr)
        {
          if (iteratorForSums.node != sums.head_)
          {
            std::cout << " ";
          }
          std::cout << iteratorForSums.node->data;
        }
        iteratorForSums++;
      }
    }
  }
  else
  {
    std::cout << 0 << '\n';
  }
  return 0;
}
