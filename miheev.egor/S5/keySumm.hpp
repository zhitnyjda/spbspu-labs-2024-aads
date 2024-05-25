#ifndef KEY_SUMM_HPP
#define KEY_SUMM_HPP

#include <utility>
#include <string>

namespace miheev
{
  struct KeySumm
  {
  public:
    KeySumm();
    ~KeySumm() = default;
    void operator()(const std::pair< const int, std::string >& keyValue);
    std::string getResults();
  private:
    int result = 0;
    std::string values;
  };
}

#endif