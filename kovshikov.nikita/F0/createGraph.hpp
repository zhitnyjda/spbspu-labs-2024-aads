#ifndef CREATEGRAPH_HPP
#define CREATEGRAPH_HP
#include "workingGraph.hpp"

namespace kovshikov
{
  //
//  template<class InputIterator, class OutputIterator>
//  OutputIterator myCopy(InputIterator first, InputIterator last, OutputIterator result);
  //
  void createGraph(Tree< std::string, Graph >& graphsList, std::istream& is);
  void createLonely(Tree< std::string, Graph >& graphsList, std::istream& is);
  void deleteGraph(Tree< std::string, Graph >& graphsList, std::istream& is);
  void workWith(Tree< std::string, Graph >& graphsList, std::istream& is);

  void outputGraphs(const Tree< std::string, Graph >& graphsList, std::ostream& out);
  void outputVertexes(const Tree< std::string, Graph >& graphsList, std::ostream& out);
}

#endif
