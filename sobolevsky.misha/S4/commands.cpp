#include "commands.hpp"
#include <limits>
#include <string>

void sobolevsky::inputFromFile(std::istream &file, AVLtree< std::string, AVLtree< int, std::string, int >,  int > &data)
{
  while (!file.eof())
  {
    if (file.fail())
    {
      file.clear();
    }
    std::string name;
    file >> name;
    AVLtree< int, std::string, int > tempTree;
    int key;
    while (file >> key)
    {
      std::string value;
      file >> value;
      tempTree.insert(std::make_pair(key, value));
    }
    data.insert(std::make_pair(name, tempTree));
  }
}

void sobolevsky::getError(std::ostream &out, std::string text)
{
  out << text << "\n";
}

void sobolevsky::getPrint(std::istream &in, std::ostream &out, AVLtree< std::string, AVLtree< int, std::string, int >,  int > &data)
{
  std::string name;
  in >> name;
  out << name << " ";
  AVLtree< int, std::string, int > currTree(data.at(name));
  for (AVLtree< int, std::string, int >::ConstIterator iter(currTree.cbegin()); iter != currTree.cend();)
  {
    out << iter->first << " " << iter->second;
    iter++;
    out << (iter != currTree.cend() ? " " : "\n");
  }
}

void sobolevsky::getComplement(std::istream &in, std::ostream &out, AVLtree< std::string, AVLtree< int, std::string, int >,  int > &data)
{
  std::string newName;
  std::string name1;
  std::string name2;
  in >> newName >> name1 >> name2;
  AVLtree< int, std::string, int > newTree;
  for (AVLtree< int, std::string, int >::ConstIterator iter(data.at(name1).cbegin()); iter != data.at(name1).cend(); iter++)
  {
    if (data.at(name2).find(iter->first) == data.at(name2).end())
    {
      newTree.insert(std::make_pair(iter->first, iter->second));
    }
  }
  data.insert(std::make_pair(newName, newTree));
}

void sobolevsky::getIntersect(std::istream &in, std::ostream &out, AVLtree< std::string, AVLtree< int, std::string, int >,  int > &data)
{
  std::string newName;
  std::string name1;
  std::string name2;
  in >> newName >> name1 >> name2;
  AVLtree< int, std::string, int > newTree;
  for (AVLtree< int, std::string, int >::ConstIterator iter(data.at(name1).cbegin()); iter != data.at(name1).cend(); iter++)
  {
    if (data.at(name2).find(iter->first) != data.at(name2).end())
    {
      newTree.insert(std::make_pair(iter->first, iter->second));
    }
  }
  data.insert(std::make_pair(newName, newTree));
}

void sobolevsky::getUnion(std::istream &in, std::ostream &out, AVLtree< std::string, AVLtree< int, std::string, int >,  int > &data)
{
  std::string newName;
  std::string name1;
  std::string name2;
  in >> newName >> name1 >> name2;
  AVLtree< int, std::string, int > newTree;
  for (AVLtree< int, std::string, int >::ConstIterator iter(data.at(name1).cbegin()); iter != data.at(name1).cend(); iter++)
  {
    newTree.insert(std::make_pair(iter->first, iter->second));
  }
  for (AVLtree< int, std::string, int >::ConstIterator iter(data.at(name2).cbegin()); iter != data.at(name2).cend(); iter++)
  {
    if (data.at(name1).find(iter->first) == data.at(name1).end())
    {
      newTree.insert(std::make_pair(iter->first, iter->second));
    }
  }
  data.insert(std::make_pair(newName, newTree));
}
