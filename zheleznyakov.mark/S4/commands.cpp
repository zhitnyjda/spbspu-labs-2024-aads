#include "commands.hpp"
#include <iostream>
#include <string>

void zheleznyakov::commands::print(std::istream & in, std::ostream & out, const dicts_t & dicts)
{
  std::string dictName;
  in >> dictName;
  auto dict = dicts[dictName];
  if (dict.empty())
  {
    outEmpty(out);
    return;
  }
  auto it = dict.begin();
  while (it != dict.end())
  {
    out << it->first << ' ' << it->second;
    out << (++it == dict.end() ? '\n' : ' ');
  }
}

void zheleznyakov::outInvalidCommand(std::ostream & out)
{
  out << "<INVALID COMMAND>\n";
}

void zheleznyakov::outEmpty(std::ostream & out)
{
  out << "<EMPTY>\n";
}
