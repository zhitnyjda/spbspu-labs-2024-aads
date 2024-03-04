#include <iostream>
#include <utility>
#include "list.hpp"
#include "divideFuncs.hpp"

int main()
{
  using namespace psarev;
  List< std::pair< std::string, List< int > > > seqs;

  seqs.pushBack({ "lol", {} });
  Iterator< std::pair< std::string, List< int > > > iterSeqs = seqs.begin();
  (*iterSeqs).second.pushBack(14);
  Iterator< int > iter = (*iterSeqs).second.begin();

  std::cout << *iter << '\n';
//testing ^
//-------------------------------------------
//variant
  List< std::pair< std::string, List< int > > > lines;
  Iterator< std::pair< std::string, List< int > > > iterLine = seqs.begin();
  iterLine--;
  std::string line = "";
  while (std::cin >> line)
  {
    if (line.size() != 0)
    {
      std::string ord = psarev::getOrd(line);
      lines.pushBack({ ord, {} });
      iterLine++;

      while (line.size() != 0)
      {
        int digit = psarev::getDigit(line);
        (*iterLine).second.pushBack(digit);
      }
    }

  }

  return 0;
}
