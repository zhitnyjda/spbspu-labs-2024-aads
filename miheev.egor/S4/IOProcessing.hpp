#ifndef IO_PROCESSGIN_HPP
#define IO_PROCESSGIN_HPP

#include <string>
#include <utility>
#include "tree.hpp"

namespace miheev
{
  using Data = Tree< int, std::string >;
  std::string getWord(std::string&);
  void inputData(std::istream&, Data&);
  void inputDatasets(std::istream&, Tree< std::string, Data >&);
}

#endif
