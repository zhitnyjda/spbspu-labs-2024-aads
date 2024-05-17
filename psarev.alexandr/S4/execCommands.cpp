#include "execCommands.hpp"
#include <string>

std::ostream& psarev::outError(std::ostream& out, const std::string& errText)
{
  out << errText << '\n';
  return out;
}

void psarev::fillTree(std::istream& in, avlTree< std::string, base_t >& dataSets)
{
  std::string strData;
  while (getline(in, strData))
  {
    size_t trekPt = 0;
    std::string dataName = "";
    while ((strData[trekPt] != ' ') && (trekPt < strData.length()))
    {
      dataName += strData[trekPt++];
    }
    trekPt++;

    psarev::avlTree< int, std::string > curSet;
    while (trekPt < strData.length())
    {
      std::string strKey = "";
      while ((strData[trekPt] != ' ') && (trekPt < strData.length()) && (std::isdigit(strData[trekPt])))
      {
        strKey += strData[trekPt++];
      }
      trekPt++;
      int key = std::stoi(strKey);
      std::string value = "";
      while ((strData[trekPt] != ' ') && (trekPt < strData.length()))
      {
        value += strData[trekPt++];
      }
      trekPt++;

      curSet.insert(key, value);
    }
    dataSets.insert(dataName, curSet);
  }
}