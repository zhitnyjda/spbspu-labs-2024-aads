#include "input.hpp"

void zheleznyakov::readLines(std::istream & input, Queue< std::string > &queue)
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

void zheleznyakov::tokenize(std::string str, zheleznyakov::Stack< std::string > & dest)
{
  std::string currentToken;
  for (char c : str)
  {
    if (std::isspace(c))
    {
      if (!currentToken.empty())
      {
        dest.push(currentToken);
        currentToken.clear();
      }
    }
    else
    {
      currentToken += c;
    }
  }
  if (!currentToken.empty())
  {
    dest.push(currentToken);
  }
}
