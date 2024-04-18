#include <iostream>
#include <string>
#include "Queue.hpp"
#include "Stack.hpp"
using namespace taskaev;

int main(int argc, char* argv[])
{
  Queue< std::string > queue;
  Queue< std::string > postfix;
  Stack< std::string > stack;
  Stack< long long > results;
  std::string mathValue;
  if(argc == 1)
  {
    while(!std::cin.eof())
    {
      std::getline(std::cin, mathValue);
      try
      {
        inputMathValue(queue, mathValue);
        convertToPostfix(queue, postfix, stack);
        // result
      }
      catch(...)
      {
        std::cerr << e.what() << "\n";
        return 1;
      }
    }
  }
  else if(argc == 2)
  {
    // не помню наверно стоит посмотреть как работали в P4
  }
  else
  {
    std::cerr << "Error arguments, don't be greedy add more!\n";
    return 1;
  }
  return 0;
}
