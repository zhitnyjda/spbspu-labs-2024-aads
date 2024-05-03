#include <iostream>
#include <fstream>
#include <istream>
#include "queue.hpp"
#include "inputProcessing.hpp"

int main()
{
  std::string testLine = "( 1 + 2 ) * 3";
  miheev::calcLine(testLine);
}
