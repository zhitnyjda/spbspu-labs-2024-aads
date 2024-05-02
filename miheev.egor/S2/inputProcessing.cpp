#include "inputProcessing.hpp"
#include "expressionElement.hpp"
#include "queue.hpp"

namespace miheev
{
  std::string getElem(std::string&);
}

std::string miheev::getElem(std::string& s)
{
  std::string substring = s.substr(0, s.find(" "));
  if (s.find(" ") == std::string::npos)
  {
    s = "";
  }
  else
  {
    s = s.substr(s.find(" ") + 1);
  }
}

miheev::Stack< long long > miheev::processInput(std::istream& in)
{
  Stack< miheev::element_t > stack();
  Queue< miheev::element_t > queue();
  Stack< long long > results();
  
}