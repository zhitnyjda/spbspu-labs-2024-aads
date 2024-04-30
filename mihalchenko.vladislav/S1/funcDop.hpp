#ifndef FUNCDOP_HPP
#define FUNCDOP_HPP

#include "list.hpp"

namespace mihalchenko
{
  typedef struct
  {
    size_t summa;
    bool flgNewStr;
    bool resultFunc;
  } t_ret;

  using mainList = mihalchenko::List<std::pair<std::string, mihalchenko::List<size_t>>>;
  using integerList = mihalchenko::List<size_t>;
  size_t printName(mainList &mixedList, size_t mixedListSize, size_t maxLenOfSecondList);
  size_t printSumDigit(integerList &tempIntList, size_t tempIntListSize);
  t_ret printMixedList(mainList &mixedList, size_t mixedListSize, size_t numericView, bool flgNewStr);
}

#endif
