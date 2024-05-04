#include <iostream>
#include "stack.hpp"
#include "queue.hpp"

int main()
{
  zheleznyakov::Stack< unsigned long long > stack;
  for (size_t i = 0; i <= 4; i++)
  {
    stack.push(i);
  }
  for (size_t i = stack.size(); i > 1; i--)
  {
    std::cout << stack.top() << '\n';
    stack.pop();
  }
  std::cout << '\n';
  zheleznyakov::Queue< unsigned long long > queue;
  for (size_t i = 0; i <= 4; i++)
  {
    queue.push(i);
  }
  for (size_t i = queue.size(); i > 1; i--)
  {
    std::cout << queue.back() << '\n';
    queue.pop();
  }
  return 0;
}
