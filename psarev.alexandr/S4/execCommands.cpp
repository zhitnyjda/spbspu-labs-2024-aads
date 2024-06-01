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
    if (in.fail())
    {
      in.clear();
    }

    std::string setName;
    int key;
    in >> setName;
    psarev::avlTree< int, std::string > curSet;

    while (in >> key)
    {
      std::string value;
      in >> value;
      curSet.insert({ key, value });
    }

    dataSets.insert({setName, curSet });
  }
}

void psarev::print(avlTree< std::string, avlTree< int, std::string > >& dataSets)
{
  std::string setName;
  std::cin >> setName;

  auto setIter = dataSets.find(setName);
  if (setIter == dataSets.end())
  {
    outError(std::cout, "<INVALID COMMAND>");
    return;
  }
  else if ((*setIter).second.isEmpty())
  {
    outError(std::cout, "<EMPTY>");
    return;
  }

  std::cout << (*setIter).first << " ";
  for (auto it = (*setIter).second.begin(); it != (*setIter).second.end(); ++it)
  {
    std::cout << (*it).first << " " << (*it).second;
    ((++it) == (*setIter).second.end()) ? std::cout << "\n" : std::cout << ' ';
    it--;
  }
}

void psarev::complement(avlTree< std::string, avlTree< int, std::string > >& dataSets)
{
  std::string newSet, fSet, sSet;
  std::cin >> newSet >> fSet >> sSet;

  auto fSetIter = dataSets.find(fSet);
  auto sSetIter = dataSets.find(sSet);
  if ((fSetIter == dataSets.end()) || (sSetIter == dataSets.end()))
  {
    outError(std::cout, "<INVALID COMMAND>");
    return;
  }

  avlTree< int, std::string > sets;
  for (auto iter = (*fSetIter).second.begin(); iter != (*fSetIter).second.end(); iter++)
  {
    auto newIter = (*dataSets.find(sSet)).second.find((*iter).first);
    if (newIter == (*dataSets.find(sSet)).second.end())
    {
      sets.insert(*iter);
    }
  }

  if (fSet == newSet)
  {
    dataSets.erase(fSet);
    dataSets.insert({ newSet, sets });
  }
  else
  {
    dataSets.insert({ newSet, sets });
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
