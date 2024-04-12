#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>
#include "ForwardList.hpp"
#include "Node.hpp"
#include "Vector.hpp"

namespace zasulsky
{
  void getSequence(ForwardList < std::pair< std::string, Vector< int > > >& list, std::string str)
  {
    if (str == "")
    {
      return;
    }
    ForwardList < std::pair< std::string, Vector< int > > > dub;
    Vector< int > vec;
    std::string name;
    std::string numbers;
    if (std::string::npos != str.find_first_of(' '))
    {
      size_t num = str.find_first_of(' ');
      name = str.substr(0, num);
      numbers = str.substr(num + 1);
      for (size_t position = 0; position < numbers.size(); position += 2)
      {
        std::string n = numbers.substr(position, 1);
        int i = stoi(n);
        vec.push_back(i);
      }
    }
    else
    {
      name = str;
    }
    dub.insert_after(list.beforeBegin(), make_pair(name, vec));
    for (auto el : dub)
    {
      list.insert_after(list.beforeBegin(), el);
    }
  }

  void outputNames(ForwardList < std::pair< std::string, Vector< int > > > list, std::ostream& out)
  {
    for (auto el : list)
    {
      if (el != list.front())
      {
        out << ' ' << el.first;
      }
      else
      {
        out << el.first;
      }
    }
    out << '\n';
  }

  int getMaxSize(ForwardList < std::pair< std::string, Vector< int > > > list)
  {
    ForwardList<int> ls;
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
  Vector < int > getSizes(ForwardList < std::pair< std::string, Vector< int > > > list)
  {
    Vector<int> res;
    for (auto el : list)
    {
      res.push_back(el.second.getSize());
    }
    return res;
  }

  void outputSumes(ForwardList<int>& res, ForwardList<int>& sums, ForwardList<int>& sumsa, std::ostream& out)
  {
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
      if (iter == res.begin())
      {
        out << *iter;
      }
      else if (std::next(iter) == res.end())
      {
        out << ' ' << *iter << '\n';
      }
      else
      {
        out << ' ' << *iter;
      }
    }
  }
  void outputSequence(ForwardList < std::pair< std::string, Vector< int > > >& listo, std::ostream& out)
  {
    Vector < int > sizes = getSizes(listo);
    ForwardList < std::pair< std::string, Vector< int > > > list;
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
        break;
      }
      int ind = 0;
      int sum = 0;
      for (iterator < std::pair< std::string, Vector< int > > > it = list.begin(); it != list.end(); it++)
      {
        if (num < it->second.getSize())
        {
          if (sizes.isLeft(ind, num) && (sizes.isRight(ind, num)))
          {
            out << ' ' << it->second.data[num];
          }
          else if (!(sizes.isRight(ind, num)) && (sizes.isLeft(ind, num)))
          {
            out << ' ' << it->second.data[num] << '\n';
          }
          else if (!(sizes.isRight(ind, num)) && !(sizes.isLeft(ind, num)))
          {
            out << it->second.data[num] << '\n';
          }
          else
          {
            out << it->second.data[num];
          }
          sum += it->second.data[num];
        }
        ind++;
      }
      sumsa.insert_after(sumsa.beforeBegin(), sum);

      num++;
    }
    outputSumes(res, sums, sumsa, std::cout);
  }
}

#endif
