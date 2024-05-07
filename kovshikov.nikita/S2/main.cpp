#include <cstring>
#include <fstream>
#include "queue.hpp"
#include "stack.hpp"
#include "computing.hpp"

int main(int argc, char ** argv)
{
  using namespace kovshikov;
  Queue< std::string > allData;
  if(argc == 1)
  {
    readData(std::cin, allData);
  }
  else if(argc == 2)
  {
    std::ifstream file(argv[1]);
    readData(file, allData);
  }
  else
  {
    std::cout << "Something went wrong." << "\n";
  }
  doubleQ separateData;
  separateElements(allData, separateData);
  doubleQ postfixQ;
  getPostfix(separateData, postfixQ);
  Stack< long long > result;
  getComputing(postfixQ, result);
  output(std::cout, result);
}
