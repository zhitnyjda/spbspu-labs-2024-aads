#include "utilFuncs.hpp"

std::ostream& psarev::outInvCommand(std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
  return out;
}

std::ostream& psarev::outEmpty(std::ostream& out)
{
  out << "<EMPTY>\n";
  return out;
}