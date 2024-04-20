#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>
#include "ForwardList.hpp"
#include "Node.hpp"
#include "Vector.hpp"
#include "parser.hpp"

namespace zasulsky
{
  using fList = ForwardList < std::pair < std::string, Vector < std::string > > >;

  void getSequence(fList& list, std::string str)
  {
    if (str == "")
    {
      return;
    }

    Vector< std::string > vec;
    std::string name;
    std::string numbers;
    if (std::string::npos != str.find_first_of(' '))
    {
      size_t num = str.find_first_of(' ');
      name = str.substr(0, num);
      numbers = str.substr(num + 1);
      Parser pars(numbers);
      for (auto i = pars(); !i.empty(); i = pars())
      {
        vec.push(i);
      }
    }
    else
    {
      name = str;
    }
    fList dub;
    dub.insert_after(list.beforeBegin(), make_pair(name, vec));
    for (auto el : dub)
    {
      list.insert_after(list.beforeBegin(), el);
    }
  }

  void outputNames(fList list, std::ostream& out)
  {
    for (auto el : list)
    {
      if (el != list.front() && el != list.back())
      {
        out << ' ' << el.first;
      }
      else if (el == list.back() && el == list.front())
      {
        out << el.first << '\n';
      }
      else if (el == list.back())
      {
        out << ' ' << el.first << '\n';
      }
      else if (el == list.front())
      {
        out << el.first;
      }
    }
  }

  int getMaxSize(fList list)
  {
    ForwardList< int > ls;
    for (auto el : list)
    {
      ls.pushFront(el.second.getSize());
    }
    int max = 0;
    int current = 0;
    for (auto el : list)
    {
      current = el.second.getSize();
      if (current > max)
      {
        max = current;
      }
    }
    return max;
  }
  Vector < int > getSizes(fList list)
  {
    Vector<int> res;
    for (auto el : list)
    {
      res.push_back(el.second.getSize());
    }
    return res;
  }

  void outputSumes(ForwardList< int >& res, ForwardList< int >& sums, ForwardList< int >& sumsa, std::ostream& out, bool isOver)
  {
    if (isOver)
    {
      throw std::overflow_error("overflow");
    }
    for (auto el : sumsa)
    {
      sums.insert_after(sums.beforeBegin(), el);
    }
    for (auto el : sumsa)
    {
      res.insert_after(res.beforeBegin(), el);
    }
    for (iterator<int> iter = res.begin(); iter != res.end(); iter++)
    {
      if (iter == res.begin() && std::next(iter) != res.end())
      {
        out << *iter;
      }
      else if (iter != res.begin() && std::next(iter) == res.end())
      {
        out << ' ' << *iter << '\n';
      }
      else if (iter == res.begin() && std::next(iter) == res.end())
      {
        out << *iter << '\n';
      }
      else
      {
        out << ' ' << *iter;
      }
    }
  }
  void outputSequence(fList& listo, std::ostream& out, bool isOver)
  {
    Vector < int > sizes = getSizes(listo);
    fList list;
    for (auto el : listo)
    {
      list.pushFront(el);
    }
    int max = getMaxSize(list);
    ForwardList<int> res;
    ForwardList<int> sumsa;
    ForwardList<int> sums;
    int num = 0;
    for (int i = 0; i <= max; i++)
    {
      if (num > max - 1)
      {
        if (num == 0)
        {
          sumsa.insert_after(sumsa.beforeBegin(), 0);
        }
        break;
      }
      int ind = 0;
      int sum = 0;
      for (iterator < std::pair< std::string, Vector< std::string > > > it = list.begin(); it != list.end(); it++)
      {
        if (num < it->second.getSize())
        {
          if (sizes.isLeft(ind, num) && (sizes.isRight(ind, num)))
          {
            out << ' ' << it->second.getData[num];
          }
          else if (!(sizes.isRight(ind, num)) && (sizes.isLeft(ind, num)))
          {
            out << ' ' << it->second.getData[num] << '\n';
          }
          else if (!(sizes.isRight(ind, num)) && !(sizes.isLeft(ind, num)))
          {
            out << it->second.getData[num] << '\n';
          }
          else
          {
            out << it->second.getData[num];
          }
          try
          {
            sum += stoi(it->second.getData[num]);
          }
          catch (...)
          {
            isOver = true;
          }
        }
        ind++;
      }
      sumsa.insert_after(sumsa.beforeBegin(), sum);

      num++;
    }
    outputSumes(res, sums, sumsa, std::cout, isOver);
  }
}

#endif
