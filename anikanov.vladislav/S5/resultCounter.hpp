#ifndef RESULTCOUNTER_HPP
#define RESULTCOUNTER_HPP

#include <map>
#include <string>

namespace anikanov {
  class ResultCounter {
  public:
    ResultCounter();
    ~ResultCounter() = default;
    void operator()(const std::pair< int, std::string > &key_value);
    int getResult() const;
    std::string getValues() const;
  private:
    int result;
    std::string values;
  };
}

#endif
