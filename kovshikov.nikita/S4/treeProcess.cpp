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
  long long key = 0;
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
  if(key == 0)
  {
    name = temp;
  }
  if(!value.empty())
  {
    tree.insert(key, value);
  }
 // std::cout << name << "\n"; ///
  allTree.insert(name, tree);
 /* if(key == 0)
  {
    std::cout << "empty\n"; ////
    allTree[name] = tree;
    std::cout << allTree.count(name) << "\n"; ///
  }
  else if(!value.empty())
  {
    tree.insert(key, value);
    allTree.insert(name, tree);
  }
  else
  {
    allTree.insert(name, tree); //вот тут вылетает жесткая ошибка;
  }
  */
}

void kovshikov::print(Tree< std::string, Tree< long long, std::string > >& allTree)
{
  std::string dictionary;
  std::cin >> dictionary;
  Tree< long long, std::string > tree = allTree.at(dictionary);
  if(tree.isEmpty())
  {
    std::cout << "<EMPTY>" << "\n";
  }
  else
  {
    Tree< long long, std::string >::Iterator iterator = tree.begin();
    Tree< long long, std::string >::Iterator end = tree.end();
    std::cout << dictionary << " ";
    while(iterator != end)
    {
      std::pair< long long, std::string > pair = *iterator;
      if(++iterator == end)
      {
        std::cout << pair.first << " " << pair.second << "\n";
      }
      else
      {
        std::cout << pair.first << " " << pair.second << " ";
      }
    }
  }
}

void kovshikov::getComplement(Tree< std::string, Tree< long long, std::string > >& allTree)
{
  std::string name;
  std::string  nameFirst;
  std::string  nameSecond;
  std:: cin >> name >> nameFirst >> nameSecond;
  Tree< long long, std::string > newTree;
  Tree< long long, std::string > firstDictionary = allTree.at(nameFirst);
  Tree< long long, std::string > secondDictionary = allTree.at(nameSecond);
  Tree< long long, std::string >::Iterator iteratorFirst = firstDictionary.begin();
  Tree< long long, std::string >::Iterator endFirst = firstDictionary.end();
  Tree< long long, std::string >::Iterator iteratorSecond = secondDictionary.begin();
  Tree< long long, std::string >::Iterator endSecond = secondDictionary.end();
  while(iteratorFirst != endFirst)
  {
    std::pair< long long, std::string > pair = *iteratorFirst;
    if(secondDictionary.find(pair.first) == endSecond)
    {
      newTree.insert(pair);
    }
    iteratorFirst++;
  }
  while(iteratorSecond != endSecond)
  {
    std::pair< long long, std::string > pair = *iteratorSecond;
    if(firstDictionary.find(pair.first) == endFirst)
    {
      newTree.insert(pair);
    }
    iteratorSecond++;
  }
/*  if(allTree.find(name) != allTree.end())
  {
    allTree.erase(name);
  }
*/
  allTree.insert(name, newTree);
}

void kovshikov::getIntersect(Tree< std::string, Tree< long long, std::string > >& allTree)
{
  std::string name;
  std::string  nameFirst;
  std::string  nameSecond;
  std:: cin >> name >> nameFirst >> nameSecond;
  Tree< long long, std::string > newTree;
  Tree< long long, std::string > firstDictionary = allTree.at(nameFirst);
  Tree< long long, std::string > secondDictionary = allTree.at(nameSecond);
  Tree< long long, std::string >::Iterator iteratorFirst = firstDictionary.begin();
  Tree< long long, std::string >::Iterator endFirst = firstDictionary.end();
  Tree< long long, std::string >::Iterator endSecond = secondDictionary.end();
  while(iteratorFirst != endFirst)
  {
    std::pair< long long, std::string > pair = *iteratorFirst;
    if(secondDictionary.find(pair.first) != endSecond)
    {
      newTree.insert(pair);
    }
    iteratorFirst++;
  }
  allTree.insert(name, newTree);
}

void kovshikov::getUnion(Tree< std::string, Tree< long long, std::string > >& allTree)
{
  std::string name;
  std::string  nameFirst;
  std::string  nameSecond;
  std:: cin >> name >> nameFirst >> nameSecond;
  Tree< long long, std::string > newTree;
  Tree< long long, std::string > firstDictionary = allTree.at(nameFirst);
  Tree< long long, std::string > secondDictionary = allTree.at(nameSecond);
  Tree< long long, std::string >::Iterator iteratorFirst = firstDictionary.begin();
  Tree< long long, std::string >::Iterator endFirst = firstDictionary.end();
  Tree< long long, std::string >::Iterator iteratorSecond = secondDictionary.begin();
  Tree< long long, std::string >::Iterator endSecond = secondDictionary.end();
  while(iteratorFirst != endFirst)
  {
    std::pair< long long, std::string > pair = *iteratorFirst;
    newTree.insert(pair);
    iteratorFirst++;
  }
  while(iteratorSecond != endSecond)
  {
    std::pair< long long, std::string > pair = *iteratorSecond;
    if(firstDictionary.find(pair.first) == endFirst)
    {
      newTree.insert(pair);
    }
    iteratorSecond++;
  }
  allTree.insert(name, newTree);

}
