#include "functions.hpp"
#include "functions.h"
#include <string>

void taskaev::createTree(std::istream& in, BSTree< std::string, BSTree< size_t, std::string > >& tres)
{
  std::string data = "";
  while (std::getline(in, data))
  {
    if (!data.empty())
    {
      std::string temps = "";
      std::string names = "";
      size_t key = 0;
      std::string val = "";
      BSTree< size_t, std::string > tree;
      bool flag = true;
      size_t i = 0;
      while (i < data.length())
      {
        if (data[i] != ' ')
        {
          temps += data[i];
        }
        else if (data[i] == ' ' && flag == true)
        {
          names = temps;
          temps = "";
          flag = false;
        }
        else
        {
          if (std::isdigit(temps[0]))
          {
            key = std::stoll(temps);
            temps = "";
          }
          else
          {
            val = temps;
            temps = "";
            tree.insert(key, val);
          }
        }
        i++;
      }
      if (key == 0)
      {
        names = temps;
      }
      if (!val.empty())
      {
        val = temps;
        tree.insert(key, val);
      }
      tres.insert(names, tree);
    }
  }
}

