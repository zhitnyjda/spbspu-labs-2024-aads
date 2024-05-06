#include <iostream>
#include <string>
#include <sstream>
#include "queue.hpp"
#include "mainExtension.hpp"
#include "elementOfExpression.hpp"
#include "operand.hpp"
#include "operation.hpp"

int main()
{
  using namespace anikanov;
  std::string expression;
  std::getline(std::cin, expression);

  anikanov::Queue< std::shared_ptr< ElementOfExpression > > postfix;

  try {
    postfix = toPostfix(expression);
  } catch (const std::invalid_argument &err) {
    std::cerr << err.what() << "\n";
    return 1;
  }

  while (!postfix.isEmpty()) {
    auto element = postfix.front();
    if (element->isNumber()) {
      std::cout << std::dynamic_pointer_cast< Operand >(element)->getValue();
    } else {
      std::cout << std::dynamic_pointer_cast< Operation >(element)->getValue();
    }
    std::cout << " ";
    postfix.pop();
  }
  std::cout << std::endl;

  return 0;
}
