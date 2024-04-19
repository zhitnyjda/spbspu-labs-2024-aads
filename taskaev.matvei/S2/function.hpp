#ifndef FUNCTION_H
#define FUNCTION_H
#include "Queue.h"
#include "Stack.h"
#include <string>
#include "IdentifierMath.hpp"

namespace taskaev
{
  void inputMathValue(Queue< IdentifierMath >& queue, std::string mathValue);
}

#endif
