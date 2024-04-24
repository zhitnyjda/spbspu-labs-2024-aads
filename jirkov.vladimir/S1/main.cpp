#include <limits>
#include "list.hpp"
#include "inputPair.hpp"

int main()
{
  using namespace jirkov;
  try
  {
    List<std::pair<std::string,List<size_t>>>list = listInput(std::cin);
    const size_t maximum = std::numeric_limits< size_t >::max();
    size_t sum = 0;
    bool overflowError = false;
    Iterator<std::pair<std::string, List<size_t>>>iterator = list.begin();
    List< size_t > sums;
    Iterator< size_t > it;
    if (!list.empty())
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
            if (maximum - sum < iterator.node->data.second[index]->data)
            {
              overflowError = true;
              std::cout << "\n";
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
        std::cout << "\n";
      }

      it = sums.begin();
      if (sums.empty())
      {
        std::cout << 0;
      }
      else
      {
        while (it.node)
        {
          if (it.node != nullptr)
          {
            if (it.node != sums.head_)
            {
              std::cout << " ";
            }
            std::cout << it.node->data;
          }
          it++;
        }
      }
      std::cout << "\n";
    }
    else
    {
      std::cout << "0\n";
    }
    return 0;
  }
  catch (std::overflow_error& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
