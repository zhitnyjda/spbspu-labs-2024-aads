#include "commands.hpp"
#include "AvlTree.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
  nikiforov::AvlTree< int, std::string> tree;
  int num = 0;
  std::string name = "";
  try
  {
    if (argc == 2)
    {
      std::ifstream input(argv[1]);
      if (!input)
      {
        std::cerr << "Error: unable to open the file\n";
        return 2;
      }

      while (!input.eof())
      {
        std::cin >> num >> name;
        auto p = std::make_pair(num, name);
        tree.insert(p);
      }
    }
    else if (argc == 1)
    {
      while (!std::cin.eof())
      {
        std::cin >> num >> name;
        if (!std::cin.eof())
        {
          auto p = std::make_pair(num, name);
          tree.insert(p);
        }
      }
      num = 0;
    }
    else
    {
      std::cerr << "Error: wrong number of parameters\n";
    }
    auto iterr = tree.find(3);
    std::cout << iterr->first;
    std::cout << tree.at(3);
    for (auto iter = tree.begin(); iter != tree.end(); iter++)
    {
      std::cout << iter->first << " " << iter->second << "\n";
    }
  }
  catch (const std::exception&)
  {

  }
  num = 0;
  return 0;
}
