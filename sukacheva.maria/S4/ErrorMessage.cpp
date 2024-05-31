#include "ErrorMessage.hpp"

namespace sukacheva
{
  void ErrorMessage(std::ostream& out)
  {
    out << "<INVALID COMMAND>\n";
  }

  void EmptyMessage(std::ostream& out)
  {
    out << "<EMPTY>\n";
  }
}
