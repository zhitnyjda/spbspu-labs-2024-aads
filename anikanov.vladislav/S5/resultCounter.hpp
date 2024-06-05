#ifndef RESULTCOUNTER_HPP
#define RESULTCOUNTER_HPP

#include <map>
#include <string>
#include <Queue.hpp>

namespace anikanov {
  class ResultCounter {
  public:
    ResultCounter();
    ~ResultCounter() = default;
    void operator()(const std::pair< int, std::string > &key_value);
    int getResult() const;
    std::string getValues() const;
  private:
    long long result;
    Queue < std::string > values;
  };
}

#endif
