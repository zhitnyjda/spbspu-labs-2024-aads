#include <iostream>
#include <cstring>
#include <memory>
#include <limits>
#include "list.hpp"


int main()
{
  using namespace anikanov;

  std::unique_ptr< List< std::pair< char[51], List< int > > > > lists(new List< std::pair< char[51], List< int > > >);
  char input_name[51];
  int number;
  bool bad_input = false;

  while (true) {

    if (!(std::cin >> input_name)) {
      break;
    }

    List< int > numbers;
    while (std::cin.peek() != '\n') {
      if (std::cin >> number) {
        numbers.push_back(number);
      } else {
        bad_input = true;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        break;
      }
    }

    std::pair< char[51], List< int > > list_pair;
    std::strcpy(list_pair.first, input_name);
    list_pair.second = numbers;
    lists->push_back(list_pair);

    if (std::cin.eof()) { break; }
  }


  for (auto it = lists->begin(); it != lists->end();) {
    std::cout << it->first;
    if (++it != lists->end()) {
      std::cout << " ";
    }
  }
  std::cout << "\n";

  if (bad_input) {
    std::cerr << "overflow\n";
    return 1;
  }

  if (lists->empty()) {
    std::cout << "0\n";
    return 0;
  }

  bool finished = false;
  bool start_print = false;
  size_t idx = 0;
  List< int > sums;
  while (!finished) {
    finished = true;
    start_print = true;
    sums.push_back(0);
    for (auto list_it = lists->begin(); list_it != lists->end(); ++list_it) {
      const auto &list = *list_it;
      if (idx < list.second.size()) {
        auto num_it = list.second.begin();
        for (size_t i = 0; i < idx; ++i) {
          num_it++;
        }
        if (start_print) {
          std::cout << *num_it;
          start_print = false;
        } else {
          std::cout << " " << *num_it;
        }
        *sums.back() += *num_it;
        finished = false;
      }
    }
    std::cout << (finished ? "" : "\n");
    idx++;
  }

  for (auto sum_it = sums.begin(); sum_it != sums.end();) {
    if (sum_it != sums.back()) {
      std::cout << *sum_it;
    }
    if (++sum_it != --sums.end()) {
      std::cout << " ";
    }
  }

  std::cout << "\n";
  return 0;
}
