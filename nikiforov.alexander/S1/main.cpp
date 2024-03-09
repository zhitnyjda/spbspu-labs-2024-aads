#include "functions.hpp"

int main()
{
  using namespace nikiforov;

  List< std::pair< std::string, List< unsigned long long > > > seqsPair;
  List< unsigned long long > listSumm;
  Funcs< unsigned long long > func;
  try
  {
    func.input_(std::cin, seqsPair);
    func.outputName_(seqsPair);
    func.outputSeqs_(seqsPair, listSumm);
    func.outputSumm_(listSumm);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}
