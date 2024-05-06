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
    std::cout << "Something went wrong.\n";
  }
  std::string first = allData.front();
  Queue< std::string > newQueue;
  separateElements(first, newQueue);
  size_t size = newQueue.getSize();
  for(size_t i = 0; i < size; i++)
  {
    std::cout << newQueue.front() << "\n";
    newQueue.pop();
  }
}
