#ifndef TRAVERSE_CMDS_HPP
#define TRAVERSE_CMDS_HPP
#include <iostream>
#include <string>
#include "avlTree.hpp"

namespace psarev
{
  using base_t = psarev::avlTree< long long, std::string >;

  std::ostream& outInvCommand(std::ostream& out);
  std::ostream& outEmpty(std::ostream& out);

  void fillTree(std::istream& in, base_t& data);
}

#endif