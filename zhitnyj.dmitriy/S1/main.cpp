#include "SequenceHandler.h"
#include <iostream>
#include <sstream>

int main()
{
  try
  {
    SequenceHandler handler;
    std::string line;

    while (std::getline(std::cin, line))
    {
      std::istringstream iss(line);
      std::string name;
      iss >> name;

      List<unsigned long long> sequence;
      std::string num;
      unsigned long long number;

      while (iss >> num)
      {
        handler.parseNum(num, number);
        sequence.push_back(number);
      }

      handler.addSequence(name, sequence);
    }

    handler.printSequences();
    handler.rearrangeAndPrint();
  }
  catch (const std::overflow_error& err)
  {
    std::cout << err.what() << std::endl;

    return 1;
  }
  catch (const std::exception& err)
  {
    std::cout << err.what() << std::endl;

    return 1;
  }

  return 0;
}
