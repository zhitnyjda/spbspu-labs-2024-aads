#ifndef FUNCS_HPP
#define FUNCS_HPP

#include "map.hpp"

namespace khoroshkin
{
  std::string getName(std::string & line, size_t & pos);
  long long getKey(std::string & line, size_t & pos);
  std::string getValue(std::string & line, size_t & pos);
  void print(khoroshkin::Map< std::string, khoroshkin::Map< long long, std::string > > & map);
  void complement(khoroshkin::Map< std::string, khoroshkin::Map< long long, std::string > > & map);
  void intersect(khoroshkin::Map< std::string, khoroshkin::Map< long long, std::string > > & map);
  void unite(khoroshkin::Map< std::string, khoroshkin::Map< long long, std::string > > & map);
}

#endif
