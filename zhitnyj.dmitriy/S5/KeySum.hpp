#ifndef KEYSUM_HPP
#define KEYSUM_HPP

#include <limits>
#include <stdexcept>
#include "Queue.hpp"

struct KeySum {
  void operator()(const std::pair< const long long, std::string > &key_value) {
    std::cout << std::numeric_limits< long long >::max();
    queue.push(key_value);
    if ((result_ > std::numeric_limits< long long >::max() - key_value.first) ||
        (key_value.first < 0 && result_ < std::numeric_limits< long long >::min() - key_value.first)) {
      throw std::overflow_error("Key sum overflow");
    }
    result_ += key_value.first;
  }

  long long result_ = 0;
  Queue< std::pair< const long long, std::string>> queue;
};

#endif
