#ifndef RANDOM_HPP
#define RANDOM_HPP
#include <cstdlib>
#include <ctime>

namespace zheleznyakov
{
  namespace anarchy
  {
    int randomInt()
    {
      srand(time(0));
      return (rand() - rand()) % 1000;
    }

    double randomFloat()
    {
      srand(time(0));
      return (rand() - rand()) % 10 + (double(rand()) / rand());
    }
  }
}
#endif
