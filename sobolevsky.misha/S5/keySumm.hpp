#ifndef KEYSUMM_HPP
#define KEYSUMM_HPP

#include <utility>
#include <string>

namespace sobolevsky
{
  struct Key_summ
  {
  public:
    Key_summ();
    void operator()(std::pair< int, std::string > &key_value);

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

void sobolevsky::Key_summ::operator()(std::pair< int, std::string > &key_value)
{
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
