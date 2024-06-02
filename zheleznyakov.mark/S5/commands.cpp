#include "commands.hpp"
#include <string>

void zheleznyakov::commands::ascending(std::ostream & out, const data_t & data)
{
  out << data.empty() << '\n';
}

void zheleznyakov::commands::descending(std::ostream & out, const data_t & data)
{
  out << data.empty() << '\n';
}

void zheleznyakov::commands::breadth(std::ostream & out, const data_t & data)
{
  out << data.empty() << '\n';
}

void zheleznyakov::outInvalidCommand(std::ostream & out)
{
  out << "<INVALID COMMAND>\n";
}

void zheleznyakov::outEmpty(std::ostream & out)
{
  out << "<EMPTY>\n";
}
