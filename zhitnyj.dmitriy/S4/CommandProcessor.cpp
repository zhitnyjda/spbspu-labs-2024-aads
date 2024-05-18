#include <fstream>
#include <iostream>
#include <stdexcept>
#include "CommandProcessor.hpp"

void processLine(const std::string &line, BinarySearchTree< std::string, BinarySearchTree< long long, std::string>> &dictionaries) {
  std::string dataset;
  BinarySearchTree< long long, std::string > tree;
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

  dictionaries.push(dataset, tree);
}

void loadTreeFromFile(const std::string &filename, BinarySearchTree< std::string, BinarySearchTree< long long, std::string>> &dictionaries) {
  std::ifstream file(filename);
  if (!file) {
    throw std::runtime_error("Unable to open file");
  }

  std::string line;
  while (std::getline(file, line)) {
    if (!line.empty()) {
      processLine(line, dictionaries);
    }
  }
  file.close();
}

void handlePrint(BinarySearchTree< std::string, BinarySearchTree< long long, std::string>> &dictionaries) {
  std::string dataset;
  std::cin >> dataset;

  auto invalidCommandWarning = std::bind(displayWarning, std::ref(std::cout), "<INVALID COMMAND>\n");
  auto emptyWarning = std::bind(displayWarning, std::ref(std::cout), "<EMPTY>\n");

  try {
    const auto &tree = dictionaries.get(dataset);
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
  } catch (const std::runtime_error &e) {
    invalidCommandWarning();
  }
}

void handleComplement(BinarySearchTree< std::string, BinarySearchTree< long long, std::string>> &dictionaries) {
  std::string newDataset, dataset1, dataset2;
  std::cin >> newDataset >> dataset1 >> dataset2;

  auto invalidCommandWarning = std::bind(displayWarning, std::ref(std::cout), "<INVALID COMMAND>\n");

  try {
    const auto &tree1 = dictionaries.get(dataset1);
    const auto &tree2 = dictionaries.get(dataset2);
    BinarySearchTree< long long, std::string > result;

    for (auto it = tree1.begin(); it != tree1.end(); ++it) {
      if (tree2.count(it->first) == 0) {
        result.push(it->first, it->second);
      }
    }

    dictionaries.push(newDataset, result);
  } catch (const std::runtime_error &) {
    invalidCommandWarning();
  }
}

void handleIntersect(BinarySearchTree< std::string, BinarySearchTree< long long, std::string>> &dictionaries) {
  std::string newDataset, dataset1, dataset2;
  std::cin >> newDataset >> dataset1 >> dataset2;

  auto invalidCommandWarning = std::bind(displayWarning, std::ref(std::cout), "<INVALID COMMAND>\n");

  try {
    const auto &tree1 = dictionaries.get(dataset1);
    const auto &tree2 = dictionaries.get(dataset2);
    BinarySearchTree< long long, std::string > result;

    for (auto it = tree1.begin(); it != tree1.end(); ++it) {
      if (tree2.count(it->first) == 1) {
        result.push(it->first, it->second);
      }
    }

    dictionaries.push(newDataset, result);
  } catch (const std::runtime_error &) {
    invalidCommandWarning();
  }
}

void handleUnion(BinarySearchTree< std::string, BinarySearchTree< long long, std::string>> &dictionaries) {
  std::string newDataset, dataset1, dataset2;
  std::cin >> newDataset >> dataset1 >> dataset2;

  auto invalidCommandWarning = std::bind(displayWarning, std::ref(std::cout), "<INVALID COMMAND>\n");

  try {
    const auto &tree1 = dictionaries.get(dataset1);
    const auto &tree2 = dictionaries.get(dataset2);
    BinarySearchTree< long long, std::string > result = tree1;

    for (auto it = tree2.begin(); it != tree2.end(); ++it) {
      result.push(it->first, it->second);
    }

    dictionaries.push(newDataset, result);
  } catch (const std::runtime_error &) {
    invalidCommandWarning();
  }
}

void displayWarning(std::ostream &out, const std::string &message) {
  out << message;
}
