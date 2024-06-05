#include <iostream>
#include <string>
#include "functions.hpp"

namespace taskaev
{
  void createTree(std::istream& in, BSTree< int, std::string >& tree)
  {
    while (!in.eof())
    {
      std::string data = "";
      std::getline(in, data);
      if (!data.empty())
      {
        std::string temps = "";
        std::string names = "";
        size_t key = 0;
        std::string val = "";
        BSTree< size_t, std::string > tre;
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
              tre.insert(key, val);
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
          tre.insert(key, val);
        }
        tree.insert(names, tre);
      }
    }
  }
}
