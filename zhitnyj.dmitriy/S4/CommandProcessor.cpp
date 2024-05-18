#include <fstream>
#include <iostream>
#include <stdexcept>
#include "CommandProcessor.hpp"

void processLine(const std::string &line, bsTree< std::string, bsTree< long long, std::string>> &dicts) {
  std::string dataset;
  bsTree< long long, std::string > tree;
  bool isFirstToken = true;
  std::string lastKey;

  size_t start = 0;
  size_t end = line.find(' ');

  while (end != std::string::npos) {
    std::string token = line.substr(start, end - start);
    if (isFirstToken) {
      dataset = token;
      isFirstToken = false;
    }
    else if (lastKey.empty()) {
      lastKey = token;
    }
    else {
      long long key = std::stoll(lastKey);
      tree.push(key, token);
      lastKey.clear();
    }
    start = end + 1;
    end = line.find(' ', start);
  }

  if (start < line.size()) {
    std::string token = line.substr(start);
    if (!lastKey.empty()) {
      long long key = std::stoll(lastKey);
      tree.push(key, token);
    }
  }

  dicts.push(dataset, tree);
}

void loadTreeFromFile(const std::string &filename, bsTree< std::string, bsTree< long long, std::string>> &dicts) {
  std::ifstream file(filename);
  if (!file) {
    throw std::runtime_error("Unable to open file");
  }

  std::string line;
  while (std::getline(file, line)) {
    if (!line.empty()) {
      processLine(line, dicts);
    }
  }
  file.close();
}

void handlePrint(bsTree< std::string, bsTree< long long, std::string>> &dicts) {
  std::string dataset;
  std::cin >> dataset;

  auto emptyWarning = std::bind(displayWarning, std::ref(std::cout), "<EMPTY>\n");

  const auto &tree = dicts.get(dataset);
  if (tree.empty()) {
    emptyWarning();
  }
  else {
    std::cout << dataset;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
      std::cout << " " << it->first << " " << it->second;
    }
    std::cout << "\n";
  }
}

void handleComplement(bsTree< std::string, bsTree< long long, std::string>> &dicts) {
  std::string newDataset, dataset1, dataset2;
  std::cin >> newDataset >> dataset1 >> dataset2;

  auto invalidCommandWarning = std::bind(displayWarning, std::ref(std::cout), "<INVALID COMMAND>\n");

  const auto &tree1 = dicts.get(dataset1);
  const auto &tree2 = dicts.get(dataset2);
  if (tree1.empty() || tree2.empty()) {
    invalidCommandWarning();
  }
  bsTree< long long, std::string > result;

  for (auto it = tree1.begin(); it != tree1.end(); ++it) {
    if (tree2.count(it->first) == 0) {
      result.push(it->first, it->second);
    }
  }

  dicts.push(newDataset, result);
}

void handleIntersect(bsTree< std::string, bsTree< long long, std::string > > &dicts) {
  std::string newDataset, dataset1, dataset2;
  std::cin >> newDataset >> dataset1 >> dataset2;

  const auto &tree1 = dicts.get(dataset1);
  const auto &tree2 = dicts.get(dataset2);
  bsTree< long long, std::string > result;

  for (auto it = tree1.begin(); it != tree1.end(); ++it) {
    if (tree2.count(it->first) == 1) {
      result.push(it->first, it->second);
    }
  }

  dicts.push(newDataset, result);
}

void handleUnion(bsTree< std::string, bsTree< long long, std::string>> &dicts) {
  std::string newDataset, dataset1, dataset2;
  std::cin >> newDataset >> dataset1 >> dataset2;

  const auto &tree1 = dicts.get(dataset1);
  const auto &tree2 = dicts.get(dataset2);
  bsTree< long long, std::string > result;

  for (auto it = tree1.begin(); it != tree1.end(); ++it) {
    result.push(it->first, it->second);
  }

  for (auto it = tree2.begin(); it != tree2.end(); ++it) {
    if (result.count(it->first) == 0) {
      result.push(it->first, it->second);
    }
  }

  dicts.push(newDataset, result);
}

void displayWarning(std::ostream &out, const std::string &message) {
  out << message;
}
