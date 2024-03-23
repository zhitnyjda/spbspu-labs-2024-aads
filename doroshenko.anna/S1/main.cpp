#include <limits>
#include "list.hpp"
#include "functions.hpp"

int main()
{
  using namespace doroshenko;
  try
  {
    List< std::pair< std::string, List< size_t > > > list = listInput(std::cin);
    ListIterator<std::pair< std::string, List< size_t > > > iterator = list.begin();
    size_t maxSize = getMaxSize(list);
    List< size_t > sums;
    ListIterator< size_t > iteratorForSums;
    const size_t maximum = std::numeric_limits< size_t >::max();
    size_t sum = 0;
    bool overflowError = false;
    bool error = false;
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
      std::cout << "\n";
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
            if (maximum - sum <  iterator.node->data.second[index]->data)
            {
              overflowError = true;
              error = true;
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
        std::cout << "\n";
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
      std::cout << "\n";
      if (error)
      {
        throw std::overflow_error("overflow error");
      }
    }
    else
    {
      std::cout << 0 << "\n";
    }
    return 0;
  }
  catch (std::overflow_error& e)
  {
    std::cerr << e.what();
    return 1;
  }
}
