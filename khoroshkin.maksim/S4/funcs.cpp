#include "funcs.hpp"
#include <string>
#include <iostream>
#include <cctype>

std::string khoroshkin::getName(std::string & line, size_t & pos)
{
  std::string result = "";
  while (pos < line.length() && line[pos] != ' ')
  {
    result += line[pos++];
  }
  pos++;
  return result;
}

long long khoroshkin::getKey(std::string & line, size_t & pos)
{
  std::string result = "";
  while (pos < line.length() && line[pos] != ' ' && std::isdigit(line[pos]))
  {
    result += line[pos++];
  }
  pos++;
  return std::stoll(result);
}

std::string khoroshkin::getValue(std::string & line, size_t & pos)
{
  std::string result = "";
  while (pos < line.length() && line[pos] != ' ')
  {
    result += line[pos++];
  }
  pos++;
  return result;
}

void khoroshkin::print(khoroshkin::Map< std::string, khoroshkin::Map< long long, std::string > > & map)
{
  std::string name;
  std::cin >> name;
  auto dataset = map.find(name);
  if (dataset == map.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  else if ((*dataset).second.isEmpty())
  {
    std::cout << "<EMPTY>\n";
    return;
  }
  
  std::cout << (*dataset).first << " ";
  for (auto it = (*dataset).second.begin(); it != (*dataset).second.end(); ++it)
  {
    std::cout << (*it).first << " " << (*it).second;
    ((++it) == (*dataset).second.end()) ? std::cout << "\n" : std::cout << ' ';
    it--;
  }
}

void khoroshkin::complement(khoroshkin::Map< std::string, khoroshkin::Map< long long, std::string > > & map)
{
  std::string name, nameFirst, nameSecond;
  std::cin >> name >> nameFirst >> nameSecond;
  auto firstData = map.find(nameFirst);
  auto secondData = map.find(nameSecond);
  if (firstData == map.end() || secondData == map.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  khoroshkin::Map< long long, std::string > datasets{};
  for (auto it = (*firstData).second.begin(); it != (*firstData).second.end(); it++)
  {
    auto inSecondData = (*map.find(nameSecond)).second.find((*it).first);
    if (inSecondData == (*map.find(nameSecond)).second.end())
    {
      datasets.insert(*it);
    }
  }
  map.insert(name, datasets);
}

void khoroshkin::intersect(khoroshkin::Map< std::string, khoroshkin::Map< long long, std::string > > & map)
{
  std::string name, nameFirst, nameSecond;
  std::cin >> name >> nameFirst >> nameSecond;
  auto firstData = map.find(nameFirst);
  auto secondData = map.find(nameSecond);
  if (firstData == map.end() || secondData == map.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  khoroshkin::Map< long long, std::string > datasets{};
  for (auto it = (*firstData).second.begin(); it != (*firstData).second.end(); it++)
  {
    auto inSecondData = (*map.find(nameSecond)).second.find((*it).first);
    if (inSecondData != (*map.find(nameSecond)).second.end())
    {
      datasets.insert(*it);
    }
  }
  map.insert(name, datasets);
}

void khoroshkin::unite(khoroshkin::Map< std::string, khoroshkin::Map< long long, std::string > > & map)
{
  std::string name, nameFirst, nameSecond;
  std::cin >> name >> nameFirst >> nameSecond;
  auto firstData = map.find(nameSecond);
  auto secondData = map.find(nameSecond);
  if (firstData == map.end() || secondData == map.end())
  {
    std::cout << "<EMPTY>\n";
    return;
  }
  khoroshkin::Map< long long, std::string > datasets{};
  for (auto it = (*firstData).second.begin(); it != (*firstData).second.end(); it++)
  {
    datasets.insert(*it);
  }
  for (auto it = (*secondData).second.begin(); it != (*secondData).second.end(); it++)
  {
    datasets.insert(*it);
  }
  map.insert(name, datasets);
}
