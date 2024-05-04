#include "input.hpp"

void zheleznyakov::readLines(std::istream & input, Queue< std::string > & queue)
{
  std::string current;
  while (!input.eof())
  {
    std::getline(input, current);
    if (current != "")
    {
      queue.push(current);
    }
  }
}
