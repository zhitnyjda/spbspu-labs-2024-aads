#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "AvlTree.hpp"
#include <string>
#include <iostream>

namespace nikiforov
{
  using dictionariesTree = AvlTree< std::string, AvlTree< int, std::string > >;

  std::string cutElem(std::string& str);

  void createDictionary(std::string& strVocab, AvlTree< int, std::string >& dict);

  void print(dictionariesTree& dictionaries, std::istream& in, std::ostream& out);

}

#endif