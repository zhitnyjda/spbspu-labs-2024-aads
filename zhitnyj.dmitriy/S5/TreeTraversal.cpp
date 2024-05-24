#include <iostream>
#include "TreeTraversal.hpp"

void traverseAndPrintAscending(const BSTree< long long, std::string > &tree) {
  if (tree.empty()) {
    std::cout << "<EMPTY>\n";
    return;
  }

  long long keySum = 0;

  auto f = [&](const std::pair< const long long, std::string > &kv) {
    keySum += kv.first;
  };

  tree.traverse_lnr(f);

  std::cout << keySum;
  bool first = true;

  auto print = [&](const std::pair< const long long, std::string > &kv) {
    if (first) {
      std::cout << " " << kv.second;
      first = false;
    }
    else {
      std::cout << " " << kv.second;
    }
  };

  tree.traverse_lnr(print);
  std::cout << "\n";
}

void traverseAndPrintDescending(const BSTree< long long, std::string > &tree) {
  if (tree.empty()) {
    std::cout << "<EMPTY>\n";
    return;
  }

  long long keySum = 0;

  auto f = [&](const std::pair< const long long, std::string > &kv) {
    keySum += kv.first;
  };

  tree.traverse_rnl(f);

  std::cout << keySum;
  bool first = true;

  auto print = [&](const std::pair< const long long, std::string > &kv) {
    if (first) {
      std::cout << " " << kv.second;
      first = false;
    }
    else {
      std::cout << " " << kv.second;
    }
  };

  tree.traverse_rnl(print);
  std::cout << "\n";
}

void traverseAndPrintBreadth(const BSTree< long long, std::string > &tree) {
  if (tree.empty()) {
    std::cout << "<EMPTY>\n";
    return;
  }

  long long keySum = 0;

  auto f = [&](const std::pair< const long long, std::string > &kv) {
    keySum += kv.first;
  };

  tree.traverse_breadth(f);

  std::cout << keySum;
  bool first = true;

  auto print = [&](const std::pair< const long long, std::string > &kv) {
    if (first) {
      std::cout << " " << kv.second;
      first = false;
    }
    else {
      std::cout << " " << kv.second;
    }
  };

  tree.traverse_breadth(print);
  std::cout << "\n";
}

void emptyCommandWarning(std::ostream &out) {
  out << "<EMPTY>\n";
}

void invalidCommandWarning(std::ostream &out) {
  out << "<INVALID COMMAND>\n";
}
