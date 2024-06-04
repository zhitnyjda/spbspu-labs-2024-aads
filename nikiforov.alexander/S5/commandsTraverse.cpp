#include "structSumm.hpp"
#include "commandsTraverse.hpp"

void nikiforov::lnrTraverse(AvlTree<int, std::string>& traversalTree, std::ostream& out)
{
  if (!traversalTree.is_empty())
  {
    nikiforov::Key_summ keySumStruct;
    keySumStruct = traversalTree.traverse_lnr(keySumStruct);

    out << keySumStruct.result << keySumStruct.strValues << "\n";
  }
  else
  {
    emptyMessage(out);
  }
}

void nikiforov::rnlTraverse(AvlTree<int, std::string>& traversalTree, std::ostream& out)
{
  if (!traversalTree.is_empty())
  {
    nikiforov::Key_summ keySumStruct;
    keySumStruct = traversalTree.traverse_rnl(keySumStruct);

    out << keySumStruct.result << keySumStruct.strValues << "\n";
  }
  else
  {
    emptyMessage(out);
  }
}

void nikiforov::breadthTraverse(AvlTree<int, std::string>& traversalTree, std::ostream& out)
{
  if (!traversalTree.is_empty())
  {
    nikiforov::Key_summ keySumStruct;
    keySumStruct = traversalTree.traverse_breadth(keySumStruct);

    out << keySumStruct.result << keySumStruct.strValues << "\n";
  }
  else
  {
    emptyMessage(out);
  }
}
