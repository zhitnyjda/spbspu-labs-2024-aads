#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "tree.hpp"

namespace zheleznyakov
{
  using dict_t = Tree< unsigned long long, std::string >;
  using dicts_t = Tree< std::string, dict_t >;

  namespace commands
  {
    void print(std::istream &, std::ostream &, const dicts_t &);
  }
}
#endif
