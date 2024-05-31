#include "process.hpp"

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

void kovshikov::readData(std::istream& in, Tree< int, std::string >& tree)
{
  while(!in.eof())
  {
    std::string dictionary = "";
    std::getline(in, dictionary);
    if(!dictionary.empty())
    {
      createTree(tree, dictionary);
    }
  }
}

void kovshikov::createTree(Tree< int, std::string >& tree, std::string dictionary)
{
  std::string temp = "";
  size_t key = 0;
  std::string value = "";
  for(size_t i = 0; i < dictionary.length(); i++)
  {
    if(dictionary[i] != ' ')
    {
      temp += dictionary[i];
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
  if(!value.empty())
  {
    value = temp;
    tree.insert(key, value);
  }
}

void kovshikov::getAscending(Tree< int, std::string >& tree)
{
  auto outEmpty = std::bind(outText, std::placeholders::_1, "<EMPTY>");
  if(tree.isEmpty())
  {
    outEmpty(std::cout);
  }
  else
  {
    TreeTraversal operation{};
    try
    {
      TreeTraversal result = tree.traverse_lnr(operation);
      outTraversal(result);
    }
    catch(const std::exception& error)
    {
      throw;
    }
  }
}

void kovshikov::getDescending(Tree< int, std::string >& tree)
{
  auto outEmpty = std::bind(outText, std::placeholders::_1, "<EMPTY>");
  if(tree.isEmpty())
  {
    outEmpty(std::cout);
  }
  else
  {
    TreeTraversal operation{};
    try
    {
      TreeTraversal result = tree.traverse_rnl(operation);
      outTraversal(result);
    }
    catch(const std::exception& error)
    {
      throw;
    }
  }
}

void kovshikov::getBreadth(Tree< int, std::string >& tree)
{
  auto outEmpty = std::bind(outText, std::placeholders::_1, "<EMPTY>");
  if(tree.isEmpty())
  {
    outEmpty(std::cout);
  }
  else
  {
    TreeTraversal operation{};
    try
    {
      TreeTraversal result = tree.traverse_breadth(operation);
      outTraversal(result);
    }
    catch(const std::exception& error)
    {
      throw;
    }
  }
}

void kovshikov::outTraversal(TreeTraversal& result)
{
  std::cout << result.result << " ";
  while(!result.allValue.isEmpty())
  {
    std::cout << result.allValue.front();
    result.allValue.pop();
    if(!result.allValue.isEmpty())
    {
      std::cout << " ";
    }
    else
    {
      std::cout << "\n";
    }
  }
}

void kovshikov::outText(std::ostream& out, std::string string)
{
  out << string << "\n";
}
