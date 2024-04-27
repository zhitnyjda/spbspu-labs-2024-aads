#ifndef FUNCS_HPP
#define FUNCS_HPP

#include "map.hpp"

namespace khoroshkin
{
  std::string getName(std::string & line);
  long long getKey(std::string & line);
  std::string getValue(std::string & line);
  void print(khoroshkin::Map< std::string, khoroshkin::Map< long long, std::string > > & map);
  void complement(khoroshkin::Map< std::string, khoroshkin::Map< long long, std::string > > & map);
  void intersect(khoroshkin::Map< std::string, khoroshkin::Map< long long, std::string > > & map);
  void unite(khoroshkin::Map< std::string, khoroshkin::Map< long long, std::string > > & map);
}

#endif
