#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <istream>
#include "datatypes.hpp"
#include "tree.hpp"

namespace zheleznyakov
{
  namespace commands
  {
    void print(std::istream &, std::ostream &, const dicts_t &);
  }

  void outInvalidCommand(std::ostream &);
  void outEmpty(std::ostream &);
}
#endif
