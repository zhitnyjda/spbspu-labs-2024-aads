#include "commands.hpp"
#include <iostream>
#include "funcObj.hpp"

using tree_t = ponomarev::BSTree< int, std::string, int >;

void ponomarev::makeInput(std::istream & in, tree_t & data)
{
  while (!in.eof())
  {
    if (in.fail())
    {
      in.clear();
    }

    int key = 0;
    std::string value = "";

    if (in >> key >> value)
    {
      data.insert(std::make_pair(key, value));
    }
  }
}

void ponomarev::makeAscending(std::ostream & out, tree_t & data)
{
  ponomarev::Key_summ sum;
  sum = data.traverseLR< Key_summ >(sum);

  out << sum.sum_ << sum.valueRes_ << "\n";
}

void ponomarev::makeDescending(std::ostream & out, tree_t & data)
{
  ponomarev::Key_summ sum;
  sum = data.traverseRL< Key_summ >(sum);

  out << sum.sum_ << sum.valueRes_ << "\n";
}

void ponomarev::makeBreadth(std::ostream & out, tree_t & data)
{
  ponomarev::Key_summ sum;
  sum = data.traverseBreadth< Key_summ >(sum);

  out << sum.sum_ << sum.valueRes_ << "\n";
}
