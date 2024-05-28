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
  if (key_value.first > 0 && limitMax - keyResult_ < key_value.first)
  {
    throw std::overflow_error("");
  }
  else if (key_value.first < 0 && keyResult_ < 0 && limitMin - keyResult_ > key_value.first)
  {
    throw std::underflow_error("");
  }
  keyResult_ += key_value.first;
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
