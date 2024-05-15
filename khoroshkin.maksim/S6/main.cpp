#include <iostream>
#include <string>
#include <iomanip>
#include <functional>
#include "sort.hpp"
#include "inputProcessing.hpp"

int main(int argc, char * argv[])
{
  using namespace khoroshkin;
  srand(time(0));

  if (argc != 4)
  {
    std::cerr << "Error: wrong input!\n";
    return 1;
  }

  try
  {
    if (std::string(argv[1]) == "ascending")
    {
      if (std::string(argv[2]) == "ints")
      {
        std::less< int > comp;
        sortDataStructures< int >(std::cout, std::stoull(argv[3]), comp);
      }
      else
      {
        std::less< double > comp;
        sortDataStructures< double >(std::cout, std::stoull(argv[3]), comp);
      }
    }
    else
    {
      if (std::string(argv[2]) == "ints")
      {
        std::greater< int > comp;
        sortDataStructures< int >(std::cout, std::stoull(argv[3]), comp);
      }
      else
      {
        std::greater< double > comp;
        sortDataStructures< double >(std::cout, std::stoull(argv[3]), comp);
      }
    }
  }
  catch(const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
