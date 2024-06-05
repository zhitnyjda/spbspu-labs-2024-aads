#ifndef FUNC_OBJ_HPP
#define FUNC_OBJ_HPP

#include <string>

namespace ponomarev
{
  struct Key_summ
  {
    void operator()(const std::pair< int, std::string > & value);

    int sum = 0;
    std::string valueRes;
  };
}

#endif
