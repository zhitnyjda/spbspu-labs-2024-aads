#include "execCommands.hpp"

std::ostream& psarev::outError(std::ostream& out, const std::string& errText)
{
  out << errText << '\n';
  return out;
}

void psarev::fillTree(std::istream& in, avlTree< std::string, base_t >& dataSets)
{
  while (!in.eof())
  {
    std::string dataName;
    int key;
    in >> dataName;
    psarev::avlTree< int, std::string > curSet;

    while (in >> key)
    {
      std::string value;
      in >> value;
      curSet.insert(std::make_pair(key, value));
    }
    dataSets.insert(std::make_pair(dataName, curSet));
  }
}

void psarev::print(avlTree< std::string, avlTree< int, std::string > >& dataSets)
{
  std::string cmd;
  std::cin >> cmd;

  auto dataIter = dataSets.find(cmd);
  if (dataIter == dataSets.end())
  {
    outError(std::cout, "<INVALID COMMAND>");
    return;
  }
  else if ((*dataIter).second.isEmpty())
  {
    outError(std::cout, "<EMPTY>");
    return;
  }

  std::cout << (*dataIter).first << " ";
  for (auto iter = (*dataIter).second.begin(); iter != (*dataIter).second.end(); ++iter)
  {
    std::cout << (*iter).first << " " << (*iter).second;
    ((++iter) == (*dataIter).second.end()) ? std::cout << "\n" : std::cout << ' ';
    iter--;
  }
}

void psarev::complement(avlTree< std::string, avlTree< int, std::string > >& dataSets)
{
  std::string cmd, cmdF, cmdS;
  std::cin >> cmd >> cmdF >> cmdS;

  auto cmdFIter = dataSets.find(cmdF);
  auto cmdSIter = dataSets.find(cmdS);
  if ((cmdFIter == dataSets.end()) || (cmdSIter == dataSets.end()))
  {
    outError(std::cout, "<INVALID COMMAND>");
    return;
  }

  avlTree< int, std::string > sets;
  for (auto iter = (*cmdFIter).second.begin(); iter != (*cmdFIter).second.end(); iter++)
  {
    auto cmdIter = (*dataSets.find(cmdS)).second.find((*iter).first);
    if (cmdIter == (*dataSets.find(cmdS)).second.end())
    {
      sets.insert(*iter);
    }
  }
  if (cmdF == cmd)
  {
    dataSets.erase(cmdF);
    dataSets.insert({ cmd, sets });
  }
  else
  {
    dataSets.insert({ cmd, sets });
  }
}

void psarev::intersect(avlTree<std::string, psarev::avlTree<int, std::string>>& dataSets)
{
  //std::string cmd, cmdF, cmdS;
  //std::cin >> cmd >> cmdF >> cmdS;

  //auto firstData = dataSets.find(cmdF);
  //auto secondData = dataSets.find(cmdS);
  //if (firstData == dataSets.end() || secondData == dataSets.end())
  //{
  //  outError(std::cout, "<INVALID COMMAND>");
  //  return;
  //}
  //avlTree< int, std::string > sets;
  //for (auto iter = (*firstData).second.begin(); iter != (*firstData).second.end(); iter++)
  //{
  //  auto inSecondData = (*dataSets.find(cmdS)).second.find((*iter).first);
  //  if (inSecondData != (*dataSets.find(cmdS)).second.end())
  //  {
  //    sets.insert(*iter);
  //  }
  //}
  //if (cmdF == cmd)
  //{
  //  dataSets.erase(cmdF);
  //  dataSets.insert({ cmd, sets });
  //}
  //else
  //{
  //  dataSets.insert({ cmd, sets });
  //}
}

void psarev::unite(avlTree<std::string, avlTree<int, std::string>>& dataSets)
{
  //std::string cmd, cmdF, cmdS;
  //std::cin >> cmd >> cmdF >> cmdS;

  //auto cmdFIter = dataSets.find(cmdF);
  //auto cmdSIter = dataSets.find(cmdS);
  //if (cmdFIter == dataSets.end() || cmdSIter == dataSets.end())
  //{
  //  outError(std::cout, "<INVALID COMMAND>");
  //  return;
  //}
  //avlTree< int, std::string > sets;
  //for (auto iter = (*cmdFIter).second.begin(); iter != (*cmdFIter).second.end(); iter++)
  //{
  //  sets.insert(*iter);
  //}
  //for (auto iter = (*cmdSIter).second.begin(); iter != (*cmdSIter).second.end(); iter++)
  //{
  //  auto setIter = sets.find((*iter).first);
  //  if (setIter == sets.end())
  //  {
  //    sets.insert(*iter);
  //  }
  //}
  //if (cmdF == cmd)
  //{
  //  dataSets.erase(cmdF);
  //  dataSets.insert({ cmd, sets });
  //}
  //else if (cmdS == cmd)
  //{
  //  dataSets.erase(cmdS);
  //  dataSets.insert({ cmd, sets });
  //}
  //else
  //{
  //  dataSets.insert({ cmd, sets });
  //}
}

