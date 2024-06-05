#include "mainExtansion.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

void anikanov::printInvalidUsage(std::ostream &os, char **argv)
{
  os << "Usage: " << argv[0] << " [ascending|descending|breadth] filename\n";
}

void anikanov::printInvalidCommand(std::ostream &os)
{
  os << "<INVALID COMMAND>\n";
}

void anikanov::printEmpty(std::ostream &os)
{
  os << "<EMPTY>\n";
}
