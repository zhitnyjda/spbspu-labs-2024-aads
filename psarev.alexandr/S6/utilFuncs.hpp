#ifndef UTIL_FUNCS_HPP
#define UTIL_FUNCS_HPP
#include <iostream>

namespace psarev
{
  std::ostream& outInvCommand(std::ostream& out);
  std::ostream& outEmpty(std::ostream& out);

  template< typename T >
  std::ostream& outDepot(std::ostream& out, const T& depot);
}

template< typename T >
std::ostream& psarev::outDepot(std::ostream& out, const T& depot)
{
  for (auto iter = depot.begin(); iter != depot.end(); iter++)
  {
    out << std::fixed << std::setprecision(1) << *iter;
    if ((std::next(iter) == depot.end())
    {
      out << "\n";
    }
    else
    {
      out << " ";
    }
  }
  return out;
}

#endif