#include "list.hpp"

int main()
{
  int seqLen = 10;
  std::string input = "";
  size_t count = -1;
  size_t maxSeqLen = 0;
  size_t currSeqLen = 0;
  bool flag = 0;
  while (std::cin)
  {
    std::cin >> input;
    if (!std::cin)
    {
      if (currSeqLen > maxSeqLen)
      {
        maxSeqLen = currSeqLen;
      }
      continue;
    }
  }
  if (!flag)
  {
    std::cout << 0;
  }
}
