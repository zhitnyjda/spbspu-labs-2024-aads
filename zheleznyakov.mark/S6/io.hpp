#ifndef IO_HPP
#define IO_HPP
#include <istream>

namespace zheleznyakov
{
  template< typename Container >
  void iterOut(Container & c, std::ostream & out)
  {
    auto iter(c.begin());
    while (iter != c.end())
    {
      out << (*iter);
      out << (++iter == c.end() ? '\n' : ' ');
    }
  }
}
#endif
