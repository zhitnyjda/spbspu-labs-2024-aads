#include "function.h"
#include "Queue.h"
#include "Stack.h"
#include <string>
#include "IdentifierMath.hpp"

namespace taskaev
{
  void inputMathValue(Queue< IdentifierMath >& queue, std::string mathValue)
  {
    std::string item;
    size_t i = 0;
    while( i < mathValue.length()) {
      if (mathValue[i] != ' ') {
        item += mathValue[i];
      }
      else {
        queue.push((IdentifierMath(item)));
        item = "";
      }
      i++;
    }
    queue.push(IdentifierMath(item));
  }
}
