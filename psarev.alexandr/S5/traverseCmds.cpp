#include "traverseCmds.hpp"

std::ostream& psarev::outInvCommand(std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
  return out;
}

std::ostream& psarev::outEmpty(std::ostream& out)
{
  out << "<EMPTY>\n";
  return out;
}

using base_t = psarev::avlTree< long long, std::string >;

void psarev::fillTree(std::istream& in, base_t& data)
{
  while (!in.eof())
  {
    if (in.fail())
    {
      in.clear();
    }

    long long key;
    std::string value;

    in >> key;
    in >> value;
    data.insert({ key, value });
  }
}

void psarev::ascending(std::ostream& out, base_t& data)
{

}

void psarev::descending(std::ostream& out, base_t& data)
{

}

void psarev::breadth(std::ostream& out, base_t& data)
{

}
