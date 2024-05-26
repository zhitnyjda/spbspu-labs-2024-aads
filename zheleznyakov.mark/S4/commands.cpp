#include "commands.hpp"
#include <string>

void zheleznyakov::commands::print(std::istream & in, std::ostream & out, const dicts_t & dicts)
{
  std::string dictName = "";
  in >> dictName;
  auto dict = dicts[dictName];
  out << dict.size() << '\n';
}

void zheleznyakov::outInvalidCommand(std::ostream & out)
{
  out << "<INVALID COMMAND>\n";
}
