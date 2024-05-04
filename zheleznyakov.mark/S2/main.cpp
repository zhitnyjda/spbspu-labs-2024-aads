#include <iostream>
#include "stack.hpp"

int main()
{
  zheleznyakov::Stack< unsigned long long > s;
  for (size_t i = 0; i <= 4; i++)
  {
    s.push(i);
  }
  for (size_t i = s.size(); i > 1; i--)
  {
    std::cout << s.top() << '\n';
    s.pop();
  }
  return 0;
}
