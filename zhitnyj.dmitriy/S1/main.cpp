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
      unsigned long long number;

      while (iss >> number)
      {
        sequence.push_front(number);
      }
      if (iss.fail() && errno == 34)
      {
        throw std::overflow_error("Entered number was to big!");
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
