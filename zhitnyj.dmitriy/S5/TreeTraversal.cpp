#include <iostream>
#include "TreeTraversal.hpp"
#include "KeySum.hpp"

void traverseAscending(const BSTree< long long, std::string > &tree) {
  if (tree.empty()) {
    emptyCommandWarning(std::cout);
  }
  else {
    KeySum keySumCounter;
    KeySum keySumCounter_ = tree.traverse_lnr(keySumCounter);

    printResult(keySumCounter_, std::cout);
  }
}

void traverseDescending(const BSTree< long long, std::string > &tree) {
  if (tree.empty()) {
    emptyCommandWarning(std::cout);
  }
  else {
    KeySum keySumCounter;
    KeySum keySumCounter_ = tree.traverse_rnl(keySumCounter);

    printResult(keySumCounter_, std::cout);
  }
}

void traverseBreadth(const BSTree< long long, std::string > &tree) {
  if (tree.empty()) {
    emptyCommandWarning(std::cout);
  }
  else {
    KeySum keySumCounter;
    KeySum keySumCounter_ = tree.traverse_breadth(keySumCounter);

    printResult(keySumCounter_, std::cout);
  }
}

void printResult(KeySum &keySumCounter, std::ostream &os) {
  os << keySumCounter.result_;

  while (!keySumCounter.queue.empty()) {
    const auto &kv = keySumCounter.queue.front();
    os << " " << kv.second;
    keySumCounter.queue.pop();
  }

  os << "\n";
}

void emptyCommandWarning(std::ostream &out) {
  out << "<EMPTY>\n";
}

void invalidCommandError(std::ostream &out) {
  out << "<INVALID COMMAND>\n";
}
