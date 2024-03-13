#include <iostream>
#include <string>
#include <memory>
#include <limits>
#include "list.hpp"


int main()
{
  using namespace anikanov;

  std::unique_ptr< List< std::pair< std::string, List< unsigned long long > > > > lists(new List< std::pair< std::string, List< unsigned long long > > >);
  std::string input_name;
  unsigned long long number;

  while (true) {

    if (!(std::cin >> input_name)) {
      break;
    }

    List< unsigned long long > numbers;
    while (std::cin.peek() != '\n') {
      if (std::cin >> number) {
        numbers.push_back(number);
      } else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        break;
      }
    }

    std::pair< std::string, List< unsigned long long > > list_pair;
    list_pair.first = input_name;
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

  if (lists->empty()) {
    std::cout << "0\n";
    return 0;
  } else {
    std::cout << "\n";
  }

  bool finished = false;
  bool start_print = false;
  size_t idx = 0;
  List< unsigned long long > sums;
  bool bad_sum = false;

  while (!finished) {
    finished = true;
    start_print = true;
    for (auto list_it = lists->begin(); list_it != lists->end(); ++list_it) {
      const auto &list = *list_it;
      if (idx < list.second.size()) {
        if (finished){
          sums.push_back(0);
          finished = false;
        }
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
        if (*sums.back() + *num_it < std::max(*sums.back(), *num_it)) {
          std::cerr << "overflow\n";
          bad_sum = true;
        }
        *sums.back() += *num_it;
      }
    }
    std::cout << (finished ? "" : "\n");
    idx++;
  }

  if (bad_sum) {
    std::cerr << "overflow\n";
    return 1;
  }

  for (auto sum_it = sums.begin(); sum_it != sums.end();) {
    std::cout << *sum_it;
    if (++sum_it != sums.end()) {
      std::cout << " ";
    }
  }

  if (sums.empty()){
    std::cout << "0";
  }

  std::cout << "\n";
  return 0;
}
