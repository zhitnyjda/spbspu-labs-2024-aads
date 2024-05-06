#include <iostream>
#include <string>
#include <sstream>
#include "queue.hpp"
#include "stack.hpp"
#include "mainExtension.hpp"
#include "elementOfExpression.hpp"

int main()
{
  using namespace anikanov;
  std::string expression;
  anikanov::Queue< std::shared_ptr< ElementOfExpression > > postfix;
  anikanov::Stack< long long > answers;

  while (std::getline(std::cin, expression)) {
    if (expression.empty()) {
      expression.clear();
      continue;
    }

    try {
      postfix = toPostfix(expression);
      answers.push(calculate(postfix));
    } catch (const std::invalid_argument &err) {
      std::cerr << err.what() << "\n";
      return 1;
    } catch (const std::out_of_range &err) {
      std::cerr << err.what() << "\n";
      return 1;
    } catch (const std::overflow_error &err) {
      std::cerr << err.what() << "\n";
      return 2;
    } catch (const std::underflow_error &err) {
      std::cerr << err.what() << "\n";
      return 2;
    }

    expression.clear();
  }
  while (!answers.isEmpty()) {
    std::cout << answers.top();
    answers.pop();
    if (!answers.isEmpty()) {
      std::cout << " ";
    }
  }

  std::cout << "\n";

  return 0;
}
