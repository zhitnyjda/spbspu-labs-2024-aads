#ifndef COMMANDSTRAVERSE_HPP
#define COMMANDSTRAVERSE_HPP
#include <commands.hpp>

namespace nikiforov
{
  void lnrTraverse(AvlTree< int, std::string >& traversalTree, std::ostream& out);

  void rnlTraverse(AvlTree<int, std::string>& traversalTree, std::ostream& out);

  void breadthTraverse(AvlTree<int, std::string>& traversalTree, std::ostream& out);
}
#endif
