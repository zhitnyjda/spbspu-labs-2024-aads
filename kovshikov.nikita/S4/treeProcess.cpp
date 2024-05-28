#include "treeProcess.hpp"

bool kovshikov::isDigit(std::string str)
{
  size_t size = str.length();
  for(size_t i = 0; i < size; i++)
  {
    if(!std::isdigit(str[i]))
    {
      return false;
    }
  }
  return true;
}

void kovshikov::readData(std::istream& in, Tree< std::string, Tree< long long, std::string > >& allTree)
{
  while(!in.eof())
  {
    std::string dictionary = "";
    std::getline(in, dictionary);
    if(!dictionary.empty())
    {
      createTree(allTree, dictionary);
    }
  }
}

void kovshikov::createTree(Tree< std::string, Tree< long long, std::string > >& allTree, std::string dictionary)
{
  std::string temp = "";
  std::string name = "";
  long long key;
  std::string value = "";
  Tree< long long, std::string > tree;
  bool isName = true;
  for(size_t i = 0; i < dictionary.length(); i++)
  {
    if(dictionary[i] != ' ')
    {
      temp += dictionary[i];
    }
    else if(dictionary[i] == ' ' && isName == true)
    {
      name = temp;
      temp = "";
      isName = false;
    }
    else
    {
      if(isDigit(temp) == true)
      {
        key = std::stoll(temp);
        temp = "";
      }
      else
      {
        value = temp;
        temp = "";
        tree.insert(key, value);
      }
    }
  }
  value = temp;
  tree.insert(key, value);
  allTree.insert(name, tree); //вот тут вылетает жесткая ошибка;
}

void kovshikov::print(Tree< std::string, Tree< long long, std::string > >& allTree)
{
  std::cout << allTree.getSize() << "\n";
  std::cout << "print\n";
}
