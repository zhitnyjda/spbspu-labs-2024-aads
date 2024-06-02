#include "commands.hpp"
#include <string>

void zheleznyakov::outInvalidCommand(std::ostream & out)
{
  out << "<INVALID COMMAND>\n";
}

void zheleznyakov::outEmpty(std::ostream & out)
{
  out << "<EMPTY>\n";
}
