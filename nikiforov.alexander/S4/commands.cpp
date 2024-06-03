#include "commands.hpp";

std::string nikiforov::cutElem(std::string& str)
{
  std::string elem = str.substr(0, str.find_first_of(" ", 0));
  if (str.find_first_of(" ") == std::string::npos)
  {
    str = "";
  }
  else
  {
    str = str.substr(str.find_first_of(" ") + 1);
  }
  return elem;
}

void nikiforov::createDictionary(std::string& strVocab, AvlTree< int, std::string >& dict)
{
  std::string key;
  std::string value;

  while (!strVocab.empty())
  {
    key = cutElem(strVocab);
    if (isdigit(key[0]))
    {
      value = cutElem(strVocab);
      dict.emplace(stoi(key), value);
    }
  }
}

void nikiforov::print(dictionariesTree& dictionaries, std::istream& in, std::ostream& out)
{
  std::string nameDict;
  in >> nameDict;
  auto dict = dictionaries.find(nameDict);
  if (dict != nullptr)
  {
    if (!dict->second.is_empty())
    {
      out << dict->first;
      for (auto iter = dict->second.begin(); iter != dict->second.end(); ++iter)
      {
        out << " " << iter->first << " " << iter->second;
      }
      out << "\n";
    }
    else
    {
      emptyMessage(std::cout);
    }
  }
  else
  {
    errorMessage(std::cout);
  }
}

void nikiforov::complement(dictionariesTree& dictionaries, std::istream& in, std::ostream& out)
{
  std::string newNameDict, firstName, secondName;
  in >> newNameDict >> firstName >> secondName;

  auto firstDict = dictionaries.find(firstName);
  auto secondDict = dictionaries.find(secondName);
  if (firstDict != dictionaries.end() && secondDict != dictionaries.end())
  {
    AvlTree< int, std::string > newDict;
    for (auto it = firstDict->second.begin(); it != firstDict->second.end(); ++it) {
      if (secondDict->second.find(it->first) == secondDict->second.end())
      {
        newDict.emplace(it->first, it->second);
      }
    }

    auto findSameDict = dictionaries.find(newNameDict);
    if (findSameDict != dictionaries.end())
    {
      dictionaries.erase(findSameDict->first);
    }
    dictionaries.emplace(newNameDict, newDict);
  }
}

void nikiforov::intersect(dictionariesTree& dictionaries, std::istream& in, std::ostream& out)
{
  std::string newNameDict, firstName, secondName;
  in >> newNameDict >> firstName >> secondName;

  auto firstDict = dictionaries.find(firstName);
  auto secondDict = dictionaries.find(secondName);
  if (firstDict != dictionaries.end() && secondDict != dictionaries.end())
  {
    AvlTree< int, std::string > newDict;
    for (auto it = firstDict->second.begin(); it != firstDict->second.end(); ++it) {
      if (secondDict->second.find(it->first) != secondDict->second.end())
      {
        newDict.emplace(it->first, it->second);
      }
    }

    auto findSameDict = dictionaries.find(newNameDict);
    if (findSameDict != dictionaries.end())
    {
      dictionaries.erase(findSameDict->first);
    }
    dictionaries.emplace(newNameDict, newDict);
  }
}

std::ostream& nikiforov::errorMessage(std::ostream& out)
{
  return out << "<INVALID COMMAND>\n";
}

std::ostream& nikiforov::emptyMessage(std::ostream& out)
{
  return out << "<EMPTY>\n";
}
