#include "commands.hpp"
#include <iostream>

void ponomarev::makePrint(std::istream & in, std::ostream & out, tree_t & data)
{
  std::string datasetName = "";
  in >> datasetName;
  data_t dataset(data.at(datasetName));

  if (dataset.getSize() == 0)
  {
    printEmptyDataset(out);
    return;
  }

  out << datasetName << " ";
  for (data_t::ConstIterator iter(dataset.cbegin()); iter != dataset.cend();)
  {
    out << iter->first << " " << iter->second;
    iter++;
    out << (iter != dataset.cend() ? " " : "\n");
  }
}

