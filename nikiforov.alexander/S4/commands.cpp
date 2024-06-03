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
    out << dict->first;
    for (auto iter = dict->second.begin(); iter != dict->second.end(); ++iter)
    {
      out << " " << iter->first << " " << iter->second;
    }
    out << "\n";
  }
  else
  {

  }
}

