#ifndef IOFMTGUARD_HPP
#define IOFMTGUARD_HPP

#include <ios>

class iofmtguard {
public:
  iofmtguard(std::basic_ios< char > &s);
  ~iofmtguard();
private:
  std::basic_ios< char > &s_;
  std::streamsize precision_;
  std::ios_base::fmtflags fmt_;
};

#endif