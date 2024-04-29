#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "queue.hpp"
#include "stack.hpp"
#include "helpFunc.hpp"

int main(int argc, char *argv[])
{
  sobolevsky::Stack< std::string > stack;
  sobolevsky::Queue< size_t > queue;
  if(argc == 1)
  {
    sobolevsky::fillStack(std::cin, stack);
  }
  else if(argc == 2)
  {
    std::ifstream input(argv[1]);
    sobolevsky::fillStack(input, stack);
  }
  else
  {
    std::cerr << "Empty input\n";
    return 1;
  }

  size_t sz = stack.size();
  for(size_t i = 0; i < sz; i++)
  {
    try
    {
      size_t size = 0;
      std::shared_ptr< std::string[] > ptr(sobolevsky::fromInfixToPostfix(stack.top(), size));
      if (i < (sz - 1))
      {
        std::cout << sobolevsky::countPostfix(ptr, size) << " ";
      }
      else
      {
        std::cout << sobolevsky::countPostfix(ptr, size) << "\n";
      }
      stack.pop();
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }
  }

  return 0;
}
