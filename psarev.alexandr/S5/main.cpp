#include <fstream>
#include "taskSumm.hpp"
#include "traverseCmds.hpp"

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cerr << "Error: Wrong parameters amount!\n";
    return 2;
  }

  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cerr << "Error: Can't open a file!\n";
    return 2;
  }

  using base_t = psarev::avlTree< long long, std::string >;
  base_t data;

  psarev::fillTree(input, data);

  psarev::avlTree< std::string, std::function< void(std::ostream&, const base_t&) > > travCmds;
  taskCmds.insert({ "ascending", psarev::ascending });
  taskCmds.insert({ "descnding", psarev::descnding });
  taskCmds.insert({ "breadth", psarev::breadth });

  std::string direct = argv[1];
  
  try
  {
    auto cmdIter = travCmds.find(direct);
    if (cmdIter != travCmds.end() && !direct.empty())
    {
      (*cmdIter).second(data);
    }
    else if (!direct.empty())
    {
      psarev::outInvCommand(std::cout);
      return 1;
    }
  }
  catch (const std::overflow_error& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  return 0;
}