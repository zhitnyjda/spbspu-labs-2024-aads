#include "functions.hpp"

int main()
{
  using namespace nikiforov;

  List< std::pair< std::string, List< unsigned long > > > seqsPair;
  Funcs< unsigned long > func;
  try
  {
    func.input_(std::cin, seqsPair);
    func.outputName_(seqsPair);
    func.overflow_();
    func.outputSeqs_(seqsPair);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}
