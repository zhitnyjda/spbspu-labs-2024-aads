#include "errorsANDinput.hpp"

void sobolevsky::inputFromFile(std::istream &file, sobolevsky::AVLtree< int, std::string, int > &data)
{
  while (!file.eof())
  {
    if (file.fail())
    {
      file.clear();
    }
    int key;
    std::string value;
    if (file >> key >> value)
    {
      data.insert(std::make_pair(key, value));
    }
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

void sobolevsky::errorOverflow(std::ostream &out)
{
  out << "<OVERLFOW>\n";
}

void sobolevsky::errorUnderflow(std::ostream &out)
{
  out << "<UNDERFLOW>\n";
}
