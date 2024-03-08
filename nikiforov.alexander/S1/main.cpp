#include "functions.hpp"

int main()
{
  using namespace nikiforov;

  List< std::pair< std::string, List< unsigned long long > > > seqsPair;
  Funcs< unsigned long long > func;
  try
  {
    func.input_(std::cin, seqsPair);
    func.outputName_(seqsPair);
    List< unsigned long long > listSumm = func.outputSeqs_(seqsPair);
    func.overflow_();
    func.outputSumms(listSumm);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}
