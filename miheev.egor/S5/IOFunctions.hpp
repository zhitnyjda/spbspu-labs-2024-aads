#ifndef IO_FUNCTIONS_HPP
#define IO_FUNCTIONS_HPP

#include <ios>
#include <tree.hpp>

namespace miheev
{
  using tree_t = Tree< int, std::string >;
  void readTree(std::istream&, tree_t&);
}

#endif