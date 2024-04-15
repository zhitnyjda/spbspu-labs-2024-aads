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
      stackOfQueue res;
      stackOfQueue test = inputStatement(std::cin);
      while (!test.empty()) {
        res.push(makePostfix(test.top()));
        test.pop();
      }
      while (!res.empty()) {
        while (!res.top().empty()) {
          std::cout << res.top().front() << " ";
          res.top().pop();
        }
        std::cout << "dfdfsa" << "\n";
        res.pop();
      }
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