#ifndef RESULTCOUNTER_HPP
#define RESULTCOUNTER_HPP

#include <map>
#include <string>
#include <queue.hpp>

namespace anikanov {
  class ResultCounter {
  public:
    ResultCounter();
    ResultCounter(ResultCounter &lhs);
    ~ResultCounter() = default;
    ResultCounter operator=(const ResultCounter &rhs) noexcept;
    void operator()(const std::pair< int, std::string > &key_value);
    long long getResult() const;
    std::string getValues() const;
    Queue<std::string> values;
  private:
    long long result;
  };
}

#endif
