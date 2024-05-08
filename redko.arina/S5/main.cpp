#include <iostream>
#include <fstream>
#include <functional>
#include "inputFunctions.hpp"
#include "dataFunctions.hpp"
#include "binarySearchTree.hpp"
#include "sumAndOrder.hpp"

int main(int argc, char ** argv)
{
  if (argc != 3)
  {
    std::cerr << "Error: wrong parameters\n";
    return 2;
  }

  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cerr << "Error: unable to open the file\n";
    return 2;
  }

  redko::BSTree< std::string, std::function< redko::SumAndOrder(redko::BSTree< int, std::string > *, redko::SumAndOrder) > > functions{};
  functions.insert({ "ascending", &redko::BSTree< int, std::string >::traverseLR<redko::SumAndOrder > });
  functions.insert({ "descending", &redko::BSTree< int, std::string >::traverseRL<redko::SumAndOrder > });
  functions.insert({ "breadth", &redko::BSTree< int, std::string >::traverseBreadth<redko::SumAndOrder > });

  redko::BSTree< int, std::string > data{};
  std::string description = "";
  std::getline(input, description);
  std::string elem = "";
  int key = 0;
  while (!description.empty())
  {
    key = redko::cutKey(description);
    elem = redko::cutName(description);
    data.insert({ key, elem });
  }
  if (!data.empty())
  {
    try
    {
      redko::SumAndOrder result = functions[argv[1]](&data, redko::SumAndOrder());
      std::cout << result.sum;
      while (!result.valueOrder.empty())
      {
        std::cout << ' ' << result.valueOrder.front();
        result.valueOrder.pop();
      }
      std::cout << '\n';
    }
    catch (const std::out_of_range & e)
    {
      redko::printMessage(std::cerr, "<INVALID PARAMETER>");
      return 2;
    }
    catch (const std::overflow_error & e)
    {
      redko::printMessage(std::cerr, "<OVERFLOW ERROR>");
      return 1;
    }
  }
  else
  {
    redko::printMessage(std::cout, "<EMPTY>");
  }

  return 0;
}
