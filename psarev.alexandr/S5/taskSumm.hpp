#ifndef TASK_SUMM_HPP
#define TASK_SUMM_HPP
#include <string>
#include "../common/avlTree.hpp"

namespace psarev
{
  using base_t = psarev::avlTree< long long, std::string >;
  struct TaskSumm
  {
  public:
    TaskSumm() :
      keySumm(0),
      valSumm("")
    {};
    ~TaskSumm() = default;

    void operator()(const std::pair< const long long, std::string >& dataPair);

    long long getKeySumm();
    std::string getValSumm();

  private:
    long long keySumm;
    std::string valSumm;
  };
}

#endif
