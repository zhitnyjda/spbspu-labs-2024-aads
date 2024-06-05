#include <iostream>
#include <string>
#include "functions.hpp"

namespace taskaev
{
  void createTree(std::istream& in, BSTree< int, std::string >& tree)
  {
    std::string data = "";
    std::getline(in, data);
    if (!data.empty())
    {
      std::string temps = "";
      std::string names = "";
      size_t i = 0;
      int key = 0;
      while (i < data.length())
      {
        if (data[i] != ' ')
        {
          temps += data[i];
        }
        else
        {
          bool flag = true;
          bool flagTwo = false;
          if (temps[0] == '-' && temps.length())
          {
            flagTwo = false;
          }
          size_t i = 0;
          while (i < temps.length())
          {
            if (flagTwo == true)
            {
              if (i > 0 && !std::isDigit(temps[i]))
              {
                flag == false;
                break;
              }
            }
            else
            {
              if (!std::isDigit(temps[i]))
              {
                flag == false;
                break;
              }
            }
            i++;
          }
          if (flag == true)
          {
            key = std::stoi(temps);
            temps = "";
          }
          else
          {
            names = temps;
            temps = "";
            tree.insert(key, names);
          }
        }
        i++;
      }
      if (!names.empty())
      {
        names = temps;
        tree.insert(key, names);
      }
    }
  }



}
