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
  while(iterator.node)
  {
    std::cout << iterator.node->data.first << " ";
    iterator++;
  }
  std::cout << "\n";
  for (size_t index = 0; index < maxSize; index++)
  {
    iterator = list.begin();
    while (iterator.node)
    {
      if (iterator.node->data.second[index]!= nullptr)
      {
        std::cout << iterator.node->data.second[index]->data << " ";
        sum = sum + iterator.node->data.second[index]->data;
      }
      iterator++;
    }
    sums.pushBack(sum);
    sum = 0;
    std::cout << "\n";
  }

  iteratorForSums = sums.begin();
  while (iteratorForSums.node)
  {
    if (iteratorForSums.node != nullptr)
    {
      std::cout << iteratorForSums.node->data << " ";
    }
    iteratorForSums++;
  }
  std::cout << "\n";

  return 0;
}
