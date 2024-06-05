#include "functions.hpp"
#include <string>
#include <iostream>

namespace taskaev
{
  void createTree(std::istream& in, Tree& tree)
  {
   //std::cout << "1\n";
    while (!in.eof())
    {
      std::string data = "";
      //std::cout << "2\n";
      std::getline(in, data);
      //std::cout << "3\n";
      if (!data.empty())
      {
        std::string temps = "";
        std::string names = "";
        size_t key = 0;
        std::string val = "";
        BSTree< size_t, std::string > tre;
        bool flag = true;
        size_t i = 0;
        //std::cout << "4\n";
        while (i < data.length())
        {
          //std::cout << "5\n";
          if (data[i] != ' ')
          {
            //std::cout << "6\n";
            temps += data[i];
          }
          else if (data[i] == ' ' && flag == true)
          {
            //std::cout << "7\n";
            names = temps;
            temps = "";
            flag = false;
          }
          else
          {
            //std::cout << "8\n";
            if (std::isdigit(temps[0]))
            {
              //std::cout << "9\n";
              key = std::stoll(temps);
              //std::cout << "10\n";
              temps = "";
            }
            else
            {
              //std::cout << "11\n";
              val = temps;
              temps = "";
              //std::cout << "12\n";
              tre.insert(key, val);
              //std::cout << "13\n";
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
          //std::cout << "14\n";
          tre.insert(key, val);
          //std::cout << "15\n";
          //std::cout << "16 size: " << tre.size() << "\n";
        }
        tree.insert(names, tre);
        //std::cout << "17 size: " << tree.size() << "\n";
      }
    }
  }

//  void helpPrint(SubTree& tree, Iterator it, Iterator end)
//  {
//    while (it != end)
//    {
//      std::pair< size_t, std::string > pair = *it;
//      std::cout << pair.first << " " << pair.second;
//      ++it;
//      if (it != end)
//      {
//        std::cout << " ";
//      }
//      else
//      {
//        std::cout << "\n";
//      }
//    }
//  }

  void print(Tree& tree)
  {
    std::string datas = "";
    std::cin >> datas;
    BSTree< size_t, std::string > tres = tree.at(datas); // ТУТ ОШИБКА НО ПОЧЕМУ?
    if (tres.empty())
    {
      errorEmpty(std::cout);
      return;
    }
    else
    {
      BSTree< size_t, std::string >::ConstIterator it = tres.cbegin();
      BSTree< size_t, std::string >::ConstIterator end = tres.cend();
      std::cout << datas << " ";
      //helpPrint(tres, it, end); // типо тут рекурсия вывода
      while (it != end)
      {
        std::pair< size_t, std::string > pair = *it;
        std::cout << pair.first << " " << pair.second;
        ++it;
        if (it != end)
        {
          std::cout << " ";
        }
        else
        {
          std::cout << "\n";
        }
      }
    }
  }

  void complement(Tree& tree)
  {
    std::string names, oneName, twoName;
    std::cin >> names >> oneName >> twoName;
    BSTree< size_t, std::string > tres;
    //std::cout << tree.size() << " " << tres.size() << "\n";
    //std::cout << "3c\n";
    findComplement(tree.at(oneName), tree.at(twoName), tres);
    //std::cout << "4c\n";
    findComplement(tree.at(twoName), tree.at(oneName), tres);
    tree.insert(names, tres);
  }

  void findComplement(SubTree& two, SubTree& one, SubTree& tree)
  {
   // if (two.empty())
   // {
     // for (auto it = one.begin(); it != one.end(); ++it)
     // {
       // tree.insert(*it);
     // }
    //}
   // else
   // {
      for (auto it = one.begin(); it != one.end(); ++it)
      {
        bool flag = false;
        for (auto iter = two.begin(); iter != two.end(); ++iter)
        {
          if (it->first == iter->first)
          {
            flag = true;
            break;
          }
        }
        if (!flag)
        {
          tree.insert(*it);
        }
      }
   // }
  }

  void intersect(Tree& tree)
  {
    std::string names, oneName, twoName;
    std::cin >> names >> oneName >> twoName;
    BSTree< size_t, std::string > tres;
    BSTree< size_t, std::string > oneTres = tree.at(oneName);
    BSTree< size_t, std::string > twoTres = tree.at(twoName);
    for (auto it = oneTres.begin(); it != oneTres.end(); ++it)
    {
      size_t key = it->first;
      if (twoTres.find(key) != twoTres.cend()) //проверка на элементстаким ключом во 2 дереве
      {
        tres.insert(*it);
      }
    }
    tree.insert(names, tres);
  }

  SubTree mergeTrees(SubTree& treeOne, SubTree& treeTwo)
  {
    BSTree< size_t, std::string > result = treeOne;
    for (auto it = treeTwo.begin(); it != treeTwo.end(); ++it)
    {
      size_t key = it->first;
      if (result.find(key) == result.cend())
      {
        result.insert(*it);
      }
    }
    return result;
  }

  void unions(Tree& tree)
  {
    std::string names, oneName, twoName;
    std::cin >> names >> oneName >> twoName;
    BSTree<size_t, std::string> newTree = mergeTrees(tree.at(oneName), tree.at(twoName));
    tree.insert(names, newTree);
  }

  void errorInvalid(std::ostream& out)
  {
    out << "<INVALID COMMAND>\n";
  }

  void errorEmpty(std::ostream& out)
  {
    out << "<EMPTY>\n";
  }
}
