#include "utils.hpp"

void sobolevsky::inputFromFile(std::istream &file, sobolevsky::AVLtree< int, std::string, int > &data)
{
  while (!file.eof())
  {
    if (file.fail())
    {
      file.clear();
    }
    int key;
    file >> key;
    std::string value;
    file >> value;
    data.insert(std::make_pair(key, value));
  }
}

void sobolevsky::errorInvalidCommand(std::ostream &out)
{
  out << "<INVALID COMMAND>\n";
}

void sobolevsky::errorEmpty(std::ostream &out)
{
  out << "<EMPTY>\n";
}
