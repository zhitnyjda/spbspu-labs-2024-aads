#include "process.hpp"

bool kovshikov::isDigit(std::string str)
{
  size_t size = str.length();
  bool isNegative = false;
  if(str[0] == '-' && size > 1)
  {
    isNegative = true;
  }
  for(size_t i = 0; i < size; i++)
  {
    if(isNegative == true)
    {
      if(i > 0 && !std::isdigit(str[i]))
      {
        return false;
      }
    }
    else
    {
      if(!std::isdigit(str[i]))
      {
        return false;
      }
    }
  }
  return true;
}

void kovshikov::readData(std::istream& in, Tree< int, std::string >& tree)
{
  std::cout << "start readData\n"; //
  std::string dictionary = "";
  std::cout << "before getline\n"; //
  std::getline(in, dictionary);
  std::cout << "after getline\n"; //
  if(!dictionary.empty())
  {
    std::cout << "if\n"; ///
    try
    {
      createTree(tree, dictionary);
    }
    catch(const std::exception& error)
    {
      throw;
    }
  }
}

void kovshikov::createTree(Tree< int, std::string >& tree, std::string dictionary)
{
  std::cout << "start createTree\n"; //
  std::string temp = "";
  int key = 0;
  std::string value = "";
  std::cout << dictionary.length() << "\n"; ///
  for(size_t i = 0; i < dictionary.length(); i++)
  {
    std::cout << "for\n"; ///
    if(dictionary[i] != ' ')
    {
      std::cout << dictionary[i]; ////
      temp += dictionary[i];
    }
    else
    {
      if(isDigit(temp) == true)
      {
        std::cout << "isDigit\n"; //
        try
        {
          key = std::stoi(temp);
        }
        catch(const std::out_of_range& error)
        {
          throw std::out_of_range("<OVER OR UNDER>");
        }
        temp = "";
      }
      else
      {
        std::cout << "isValue\n"; //
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
    TreeTraversal operation;
   // try
   // {
    TreeTraversal result = tree.traverse_lnr(operation);
    outTraversal(result);
   // }
   // catch(const std::exception& error)
   // {
     // throw;
   // }
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
    TreeTraversal operation;
   // try
   // {
    TreeTraversal result = tree.traverse_rnl(operation);
    outTraversal(result);
   // }
   // catch(const std::exception& error)
   // {
     // throw;
   // }
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
    TreeTraversal operation;
   // try
   // {
    TreeTraversal result = tree.traverse_breadth(operation);
    outTraversal(result);
   // }
   // catch(const std::exception& error)
   // {
     // throw;
   // }
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
