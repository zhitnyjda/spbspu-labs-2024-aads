#include <iostream>
#include "Queue.hpp"
#include "Stack.hpp"
#include <iosfwd>
#include <string>
#include "DataProcessing.hpp"

int main(int argc, char** argv)
{
  using namespace sukacheva;
  if (argc == 1)
  {
    try {

      /*queueOfQueue test = inputQueueOfStatements(std::cin);
      while (!test.empty()) {
        if (test.front().empty()) {
          std::cout << "HELP ME SOMEBODY\n";
        }
        while (!test.front().empty()) {
          std::cout << test.front().front() << " ";
          test.front().pop();
        }
        test.pop();
      }*/

      while (std::cin)
      {
        Queue< std::string > inf = inputStatement(std::cin);
        Queue< std::string > test = makePostfix(inf);
        while (!test.empty()) {
          std::cout << test.front() << " ";
          test.pop();
        }
      }

      /*Queue< std::string > test = inputStatement(std::cin);
      while (!test.empty()) {
        std::cout << test.front() << " ";
        test.pop();
      }*/
    }
    catch (const std::exception& e) {
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  else
  {

  }
  return 0;
}