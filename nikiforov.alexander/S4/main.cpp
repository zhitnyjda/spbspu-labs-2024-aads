#include "commands.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: Wrong parameters amount!\n";
    return 2;
  }

  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Error: unable to open the file\n";
    return 2;
  }

  using data_t = nikiforov::AvlTree< int, std::string >;
  using dictionariesTree = nikiforov::AvlTree< std::string, data_t >;

  dictionariesTree dictionaries;
  data_t dict;
  std::string strVocab;
  std::string nameVocab;

  try
  {
    while (!input.eof())
    {
      std::getline(input, strVocab);
      nameVocab = nikiforov::cutElem(strVocab);
      nikiforov::createDictionary(strVocab, dict);
      if (!input.eof())
      {
        dictionaries.emplace(nameVocab, dict);
      }
      dict.clear();
    }

    using namespace std::placeholders;
    nikiforov::AvlTree< std::string, std::function < void(dictionariesTree&, std::istream&, std::ostream&) > > cmds;
    {
      cmds.emplace("print", nikiforov::print);
    }

    std::string cmd = "";

    while (std::cin >> cmd)
    {
      cmds.at(cmd)(dictionaries, std::cin, std::cout);
    }
  }
  catch (const std::exception&)
  {

  }

  strVocab = "";
  return 0;
}
