#ifndef KEYSUM_HPP
#define KEYSUM_HPP

#include <limits>
#include <stdexcept>
#include "Queue.hpp"

struct KeySum {
  void operator()(const std::pair< const long long, std::string > &key_value) {
    queue.push(key_value);
    bool isOverflow = result_ > std::numeric_limits< long long >::max() - key_value.first;
    bool isUndeflow = (key_value.first < 0) && (result_ < std::numeric_limits< long long >::min() - key_value.first);

    if (isOverflow || isUndeflow) {
      throw std::overflow_error("Key sum overflow");
    }
    result_ += key_value.first;
  }

  long long result_ = 0;
  Queue< std::pair< const long long, std::string>> queue;
};

#endif