#include <iostream>
#include <vector>
#include <cstring>


/*
first 1 1 1
second 2 2 2 2
third
fourth 4 4
*/


int main()
{
  std::vector< std::pair< char[51], std::vector< int > > > lists;
  char input_name[51];
  int number;

  while (true) {

    if (!(std::cin >> input_name)) {
      break;
    }

    std::vector< int > numbers;
    while (std::cin.peek() != '\n' && std::cin >> number) {
      numbers.push_back(number);
    }

    std::pair< char[51], std::vector< int>> list_pair;
    std::strcpy(list_pair.first, input_name);
    list_pair.second = numbers;
    lists.push_back(list_pair);

    if (std::cin.eof()) { break; }
  }

  for (const auto &list: lists) {
    std::cout << list.first << " ";
  }
  std::cout << "\n";

  if (lists.empty()) {
    std::cout << "0\n";
    return 1;
  }

  bool finished = false;
  size_t idx = 0;
  std::vector<int> sums;
  while (!finished) {
    finished = true;
    sums.push_back(0);
    for (const auto &list: lists) {
      if (idx < list.second.size()) {
        std::cout << list.second[idx] << " ";
        sums[idx] += list.second[idx];
        finished = false;
      }
    }
    if (!finished) {
      std::cout << "\n";
    }
    idx++;
  }

  for (int i = 0; i < sums.size() - 1; i++) {
    std::cout << sums[i] << " ";
  }

  std::cout << "\n";
  return 0;
}
