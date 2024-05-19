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

      curSet.insert({ key, value });
    }
    dataSets.insert({ dataName, curSet });
  }
}

void psarev::print(avlTree< std::string, avlTree< long long, std::string > >& Tree)
{
  std::string name;
  std::cin >> name;

  auto dataSet = Tree.find(name);
  if (dataSet == Tree.end())
  {
    outError(std::cout, "<INVALID COMMAND>");
    return;
  }
  else if ((*dataSet).second.isEmpty())
  {
    outError(std::cout, "<EMPTY>");
    return;
  }

  std::cout << (*dataSet).first << " ";
  for (auto it = (*dataSet).second.begin(); it != (*dataSet).second.end(); ++it)
  {
    std::cout << (*it).first << " " << (*it).second;
    ((++it) == (*dataSet).second.end()) ? std::cout << "\n" : std::cout << ' ';
    it--;
  }
}