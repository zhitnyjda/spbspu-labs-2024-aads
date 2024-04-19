#include <iostream>
#include <string>
#include "Queue.hpp"
#include "Stack.hpp"
#include "function.hpp"
#include "IdentifierMath.hpp"
using namespace taskaev;

int main(int argc, char * argv[])
{
  Queue< IdentifierMath > queue;
  Queue< IdentifierMath > postfix;
  Stack< IdentifierMath > stack;
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
        results.push(calculate(postfix));
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
  while (!results.isEmpty()) {
    std::cout << results.top();
    results.pop();
    if (!results.isEmpty()) {
      std::cout << " ";
    }
  }
  std::cout << "\n";
  return 0;
}
