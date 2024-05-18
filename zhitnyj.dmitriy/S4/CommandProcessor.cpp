#include <fstream>
#include <iostream>
#include <stdexcept>
#include "CommandProcessor.hpp"

void parseLineToTree(const std::string &line, bsTree< std::string, bsTree< long long, std::string>> &dicts) {
  if (line.empty()) {
    return;
  }

  size_t pos = 0;
  size_t spacePos = line.find(' ');
  std::string dataset = line.substr(0, spacePos);
  bsTree< long long, std::string > tree;

  if (spacePos != std::string::npos) {
    pos = spacePos + 1;
    std::string lastKey;

    while (pos < line.length()) {
      size_t nextSpace = line.find(' ', pos);

      if (nextSpace == std::string::npos) {
        if (lastKey.empty()) {
          lastKey = line.substr(pos);
        }
        else {
          long long key = std::stoll(lastKey);
          std::string value = line.substr(pos);
          tree.push(key, value);
        }
        break;
      }
      else {
        if (lastKey.empty()) {
          lastKey = line.substr(pos, nextSpace - pos);
        }
        else {
          long long key = std::stoll(lastKey);
          std::string value = line.substr(pos, nextSpace - pos);
          tree.push(key, value);
          lastKey.clear();
        }
        pos = nextSpace + 1;
      }
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
    parseLineToTree(line, dicts);
  }
  file.close();
}

void handleIntersect(bsTree< std::string, bsTree< long long, std::string > > &dicts) {
  std::string newDataset, dataset1, dataset2;
  std::cin >> newDataset >> dataset1 >> dataset2;

  auto invalidCommandWarning = std::bind(displayWarning, std::placeholders::_1, "<INVALID COMMAND>\n");

  auto it1 = dicts.find(dataset1);
  auto it2 = dicts.find(dataset2);
  if (it1 == dicts.end() || it2 == dicts.end()) {
    invalidCommandWarning(std::cout);
  }
  else {
    const auto &tree1 = it1->second;
    const auto &tree2 = it2->second;
    bsTree< long long, std::string > result;

    for (auto it = tree1.begin(); it != tree1.end(); ++it) {
      if (tree2.count(it->first) == 1) {
        result.push(it->first, it->second);
      }
    }

    dicts.push(newDataset, result);
  }
}

void handleComplement(bsTree< std::string, bsTree< long long, std::string > > &dicts) {
  std::string newDataset, dataset1, dataset2;
  std::cin >> newDataset >> dataset1 >> dataset2;

  auto invalidCommandWarning = std::bind(displayWarning, std::placeholders::_1, "<INVALID COMMAND>\n");

  auto it1 = dicts.find(dataset1);
  auto it2 = dicts.find(dataset2);
  if (it1 == dicts.end() || it2 == dicts.end()) {
    invalidCommandWarning(std::cout);
  }
  else {
    const auto &tree1 = it1->second;
    const auto &tree2 = it2->second;
    bsTree< long long, std::string > result;

    for (auto it = tree1.begin(); it != tree1.end(); ++it) {
      if (tree2.count(it->first) == 0) {
        result.push(it->first, it->second);
      }
    }

    dicts.push(newDataset, result);
  }
}

void handleUnion(bsTree< std::string, bsTree< long long, std::string > > &dicts) {
  std::string newDataset, dataset1, dataset2;
  std::cin >> newDataset >> dataset1 >> dataset2;

  auto invalidCommandWarning = std::bind(displayWarning, std::placeholders::_1, "<INVALID COMMAND>\n");

  auto it1 = dicts.find(dataset1);
  auto it2 = dicts.find(dataset2);
  if (it1 == dicts.end() || it2 == dicts.end()) {
    invalidCommandWarning(std::cout);
  }
  else {
    const auto &tree1 = it1->second;
    const auto &tree2 = it2->second;
    bsTree< long long, std::string > result = tree1;

    for (auto it = tree2.begin(); it != tree2.end(); ++it) {
      result.push(it->first, it->second);
    }

    dicts.push(newDataset, result);
  }
}

void handlePrint(bsTree< std::string, bsTree< long long, std::string > > &dicts) {
  std::string dataset;
  std::cin >> dataset;

  auto emptyCommandWarning = std::bind(displayWarning, std::placeholders::_1, "<EMPTY>\n");

  auto it = dicts.find(dataset);
  const auto &tree = it->second;
  if (tree.empty()) {
    emptyCommandWarning(std::cout);
  }
  else {
    std::cout << dataset;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
      std::cout << " " << it->first << " " << it->second;
    }
    std::cout << "\n";
  }
}

void displayWarning(std::ostream &out, const std::string &message) {
  out << message;
}
