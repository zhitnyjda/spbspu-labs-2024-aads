#include <iostream>

int main(int argc, char ** argv)
{
  if (argc != 3)
  {
    std::cerr << "Error: not open file!\n";
    return 1;
  }
  return 0;
}
