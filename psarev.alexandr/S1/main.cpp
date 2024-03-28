#include <utility>
#include <cmath>
#include "divideFuncs.hpp"
#include "outFuncs.hpp"

int main()
{
  using depot_t = psarev::List< std::pair< std::string, psarev::List< unsigned long long > > >;

  depot_t lines;
  depot_t::Iterator iterLine;
  std::string line = "";
  size_t maxDigits = 0;
  while (std::getline(std::cin, line))
  {
    if (line.size() != 0)
    {
      std::string ord = psarev::getOrd(line);
      std::pair< std::string, psarev::List< unsigned long long > > pair = { ord, {} };
      lines.pushBack(pair);
      iterLine = lines.begin();
      for (size_t i = 0; i < (lines.getSize() - 1); i++)
      {
        iterLine++;
      }
      size_t cntDigits = 0;
      while (line.size() != 0)
      {
        unsigned long long digit = psarev::getDigit(line);
        (*iterLine).second.pushBack(digit);
        cntDigits++;
      }
      maxDigits = fmax(maxDigits, cntDigits);
    }
  }

  psarev::outOrds< unsigned long long >(lines);
  bool isOverflow = false;
  psarev::List< unsigned long long > sums = psarev::outDigits < unsigned long long >(lines, maxDigits, isOverflow);
  if (isOverflow)
  {
    std::cerr << "Error: Value overflow during counting the sum!\n";
    return 1;
  }
  psarev::outSums< unsigned long long >(sums);
  return 0;
}
