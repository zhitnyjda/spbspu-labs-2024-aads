#include <iostream>
#include <string>
#include <functional>
#include <string>
#include <fstream>
#include <utility>
#include "map.hpp"
#include "funcs.hpp"

int main(int argc, char * argv[])
{
  using namespace khoroshkin;
  if (argc != 2)
  {
    std::cerr << "Wrong input\n";
    return 2;
  }

  Map< std::string, Map< long long, std::string > > mapOfDataSets{};
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Cannot open file\n";
    return 2;
  }

  std::string line;
  while (getline(input, line))
  {
    size_t pos = 0;
    std::string name = getName(line, pos);
    khoroshkin::Map< long long, std::string > datasets{};
    while (pos < line.length())
    {
      long long key = getKey(line, pos);
      std::string value = getValue(line, pos);
      datasets.insert(key, value);
    }
    if (!datasets.isEmpty())
    {
      mapOfDataSets.insert(name, datasets);
    }
  }

  Map< std::string, std::function< void(Map< std::string, Map< long long, std::string > > & map) > > mapOfFuntions{};
  mapOfFuntions.insert("print", print);
  mapOfFuntions.insert("complement", complement);
  mapOfFuntions.insert("intersect", intersect);
  mapOfFuntions.insert("union", unite);

  while (!std::cin.eof())
  {
    std::string todo;
    std::cin >> todo;
    auto function = mapOfFuntions.find(todo);
    if (function == mapOfFuntions.end() && todo.length() > 1)
    {
      std::cout << "<INVALID COMMAND>\n";
      continue;
    }
    (*function).second(mapOfDataSets);
  }
  return 0;
}
