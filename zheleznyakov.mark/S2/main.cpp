#include <iostream>
#include "stack.hpp"
#include "queue.hpp"
#include "input.hpp"

int main(int argc, char * argv[])
{
  zheleznyakov::Queue< std::string > problems;
  if (argc == 2)
  {
    std::ifstream input(argv[1]);
    zheleznyakov::readLines(input, problems);
  }
  else if (argc == 1)
  {
    zheleznyakov::readLines(std::cin, problems);
  }
  else
  {
    std::cerr << "Bad arguments\n";
    return 1;
  }
  while (!problems.empty())
  {
    zheleznyakov::Queue< std::string > infix;
    zheleznyakov::Queue< std::string > postfix;
    zheleznyakov::tokenize(problems.front(), infix);
    zheleznyakov::infixToPostfix(infix, postfix);
    while (!postfix.empty())
    {
      std::cout << postfix.front() << ' ';
      postfix.pop();
    }
    std::cout << '\n';
    problems.pop();
  }
  return 0;
}
