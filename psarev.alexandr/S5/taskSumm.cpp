#include "taskSumm.hpp"
#include <limits>
#include <stdexcept>

void psarev::TaskSumm::operator()(const std::pair<const long long, std::string>& dataPair)
{
  long long llMax = std::numeric_limits< long long >::max();
  bool overCheck = (keySumm > 0) && (dataPair.first > 0) && (llMax - keySumm < dataPair.first);

  if (overCheck)
  {
    throw std::overflow_error("");
  }

  long long llMin = std::numeric_limits< long long >::min();
  bool underCheck = (result < 0) && (keyValue.first < 0) && (llMin - keySumm > dataPair.first);
  if (underCheck)
  {
    throw std::underflow_error("");
  }

  keySumm += dataPair.first;

  if (!valSumm.empty())
  {
    valSumm += " ";
  }
  valSumm += dataPair.second;
}
