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
  size_t size = postfixQ.getSize();
  for(size_t i = 0; i < size; i++)
  {
    Queue< std::string > temp = postfixQ.front();
    postfixQ.pop();
    size_t sizeSmall = temp.getSize();
    for(size_t j = 0; j < sizeSmall; j++)
    {
      std::cout << temp.front() << " ";
      temp.pop();
    }
    std::cout << "\n";
  }
}
