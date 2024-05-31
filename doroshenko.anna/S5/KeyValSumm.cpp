#include "KeyValSumm.hpp"

doroshenko::KeyValSumm::KeyValSumm() :
  keySum_(0),
  valSum_("")
{};

void doroshenko::KeyValSumm::operator()(const std::pair< const int, std::string >& keyval)
{
  keySum_ += keyval.first;
  if (!valSum_.empty())
  {
    valSum_ += " ";
  }
  valSum_ += keyval.second;
}
