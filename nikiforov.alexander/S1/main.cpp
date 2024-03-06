#include "functions.hpp"

int main()
{
  using namespace nikiforov;

  List< std::pair< std::string, List< int > > > seqsPair;
  Funcs< int > func;

  func.input_(std::cin, seqsPair);
  func.outputName_(seqsPair);
  func.outputSeqs_(seqsPair);

  return 0;
}
