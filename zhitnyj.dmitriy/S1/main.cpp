#include "SequenceHandler.h"
#include <iostream>
#include <sstream>

int main()
{
  SequenceHandler handler;
  std::string line;

  while (std::getline(std::cin, line))
  {
    std::istringstream iss(line);
    std::string name;
    iss >> name;

    List<int> sequence;
    int number;
    while (iss >> number)
    {
      sequence.push_front(number);
    }

    handler.addSequence(name, sequence);
  }

  handler.printSequences();
  handler.rearrangeAndPrint();

  return 0;
}
