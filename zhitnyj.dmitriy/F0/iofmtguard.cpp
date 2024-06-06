#include "iofmtguard.hpp"

iofmtguard::iofmtguard(std::basic_ios< char > &s) :
  s_(s),
  precision_(s.precision()),
  fmt_(s.flags())
  {}

iofmtguard::~iofmtguard() {
  s_.precision(precision_);
  s_.flags(fmt_);
}
