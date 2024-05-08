#include "traverseFuncs.hpp"
#include <iostream>
#include "functionalObject.hpp"

void khoroshkin::ascendingTraverse(const Tree< int, std::string > & data, std::ostream & out)
{
  Traverse functor{};
  Traverse result = data.traverse_lnr(functor);
  out << result.result << " ";
  while (!result.bypass.isEmpty())
  {
    out << result.bypass.front();
    out << ((result.bypass.front() == result.bypass.back()) ? "\n" : " ");
    result.bypass.pop();
  }
}

void khoroshkin::descendingTraverse(const Tree< int, std::string > & data, std::ostream & out)
{
  Traverse functor{};
  Traverse result = data.traverse_rnl(functor);
  out << result.result << " ";
  while (!result.bypass.isEmpty())
  {
    out << result.bypass.front();
    out << ((result.bypass.front() == result.bypass.back()) ? "\n" : " ");
    result.bypass.pop();
  }
}

void khoroshkin::breadthTraverse(const Tree< int, std::string > & data, std::ostream & out)
{
  Traverse functor{};
  Traverse result = data.traverse_breadth(functor);
  out << result.result << " ";
  while (!result.bypass.isEmpty())
  {
    out << result.bypass.front();
    out << ((result.bypass.front() == result.bypass.back()) ? "\n" : " ");
    result.bypass.pop();
  }
}
