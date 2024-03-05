#include <cstring>
#include "list.hpp"

int main()
{
  hohlova::List<std::pair<std::string, hohlova::List<int>>> seq;
  std::string name;
  hohlova::List<int> nums;
  while (std::cin)
  {
    seq.push_front({ name, nums });
    while (std::cin >> name && std::isdigit(name[0]))
    {
      seq.push_front({name, nums});
    }
  }
  if (!std::cin)
  {
    for (int i = 0; i < seq.getSize(); i++)
    {
      std::cout << nums[i] << std::endl;
    }
  }
  return 0;
}

