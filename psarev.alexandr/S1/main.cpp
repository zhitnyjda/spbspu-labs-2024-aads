#include <utility>
#include <cmath>
#include "utilityFuncs.hpp"

int main()
{
  using namespace psarev;

  List< std::pair< std::string, List< int > > > lines;
  Iterator< std::pair< std::string, List< int > > > iterLine;
  std::string line = "";
  size_t maxDigits = 0;
  while (std::getline(std::cin, line))
  {
    if (line.size() != 0)
    {
      std::string ord = psarev::getOrd(line);
      lines.pushBack({ ord, {} });
      iterLine = lines.begin();
      for (size_t i = 0; i < (lines.getSize() - 1); i++)
      {
        iterLine++;
      }
      size_t cntDigits = 0;
      while (line.size() != 0)
      {
        int digit = psarev::getDigit(line);
        (*iterLine).second.pushBack(digit);
        cntDigits++;
      }
      maxDigits = fmax(maxDigits, cntDigits);
    }
  }

  outOrds(lines);
  List< int > sums = outDigits(lines, maxDigits);
  outSums<int>(sums);
  return 0;
}
