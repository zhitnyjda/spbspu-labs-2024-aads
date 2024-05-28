#ifndef KEYSUMM_HPP
#define KEYSUMM_HPP

#include <utility>
#include <string>
#include <limits>
#include <stdexcept>

namespace sobolevsky
{
  struct Key_summ
  {
  public:
    Key_summ();
    void operator()(const std::pair< const int, std::string > &key_value);

    int getKeyResult();
    std::string getValueResult();
  private:
    int keyResult_;
    std::string valueResult_;
  };
}

sobolevsky::Key_summ::Key_summ()
{
  keyResult_ = 0;
  valueResult_ = "";
}

void sobolevsky::Key_summ::operator()(const std::pair< const int, std::string > &key_value)
{
  int limitMax = std::numeric_limits< int >::max();
  int limitMin = std::numeric_limits< int >::min();
  int valFirst = key_value.first;
  if (limitMax - keyResult_ < valFirst)
  {
    throw std::overflow_error("");
  }
  if (limitMin + keyResult_ > valFirst)
  {
    throw std::underflow_error("");
  }
  keyResult_ += valFirst;
  valueResult_ += (" " + key_value.second);
}

int sobolevsky::Key_summ::getKeyResult()
{
  return keyResult_;
}

std::string sobolevsky::Key_summ::getValueResult()
{
  return valueResult_;
}

#endif
