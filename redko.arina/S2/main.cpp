#include <iostream>
#include <fstream>
#include <string>
#include "queue.hpp"
#include "stack.hpp"
#include "inputFunctions.hpp"

bool isNumeric(const std::string & str);
void processExpressions(std::istream & input, redko::Stack< unsigned long long > & res);

int main(int argc, char ** argv)
{
  redko::Stack< unsigned long long > results{};
  try
  {
    if (argc == 2)
    {
      std::ifstream input(argv[1]);
      if (!input)
      {
        std::cerr << "Error: unable to open the file\n";
        return 2;
      }
      processExpressions(input, results);
    }
    else
    {
      processExpressions(std::cin, results);
    }
  }
  catch (const std::invalid_argument & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch (const std::logic_error & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  while (!results.empty())
  {
    std::cout << results.top();
    results.pop();
    std::cout << (results.empty() ? '\n' : ' ');
  }
  return 0;
}

bool isNumeric(const std::string & str)
{
  return str.find_first_not_of("0123456789") == std::string::npos && str.size() != 0;
}

void processExpressions(std::istream & input, redko::Stack< unsigned long long > & res)
{
  std::string expression = "";
  std::string value = "";
  while (!input.eof())
  {
    redko::Queue< std::string > postfix{};
    redko::Stack< std::string > stack{};
    std::getline(input, expression);
    while (!expression.empty())
    {
      value = redko::cutName(expression);
      if (isNumeric(value))
      {
        postfix.push(value);
      }
      else
      {
        if (value == "(")
        {
          stack.push(value);
        }
        else if (value == "+" || value == "-")
        {
          while (!stack.empty() && (stack.top() == "+" || stack.top() == "-" || stack.top() == "%" || stack.top() == "*" || stack.top() == "/"))
          {
            postfix.push(stack.top());
            stack.pop();
          }
          stack.push(value);
        }
        else if (value == "%" || value == "*" || value == "/")
        {
          while (!stack.empty() && (stack.top() == "%" || stack.top() == "*" || stack.top() == "/"))
          {
            postfix.push(stack.top());
            stack.pop();
          }
          stack.push(value);
        }
        else if (value == ")")
        {
          while (!stack.empty() && stack.top() != "(")
          {
            postfix.push(stack.top());
            stack.pop();
          }
          stack.pop();
        }
        else
        {
          throw std::invalid_argument("Error: wrong expression");
        }
      }
    }
    while (!stack.empty())
    {
      postfix.push(stack.top());
      stack.pop();
    }
    if (!postfix.empty())
    {
      redko::Stack< long long > calc{};
      unsigned long long first = 0;
      unsigned long long second = 0;

      while (!postfix.empty())
      {
        if (isNumeric(postfix.front()))
        {
          calc.push(stoll(postfix.front()));
        }
        else
        {
          first = calc.top();
          calc.pop();
          second = calc.top();
          calc.pop();
          if (postfix.front() == "+")
          {
            calc.push(second + first);
          }
          else if (postfix.front() == "-")
          {
            calc.push(second - first);
          }
          else if (postfix.front() == "*")
          {
            calc.push(second * first);
          }
          else if (postfix.front() == "/")
          {
            if (first != 0)
            {
              calc.push(second / first);
            }
            else
            {
              throw std::logic_error("Error: division by 0");
            }
          }
          else
          {
            if (first != 0)
            {
              calc.push(second % first);
            }
            else
            {
              throw std::logic_error("Error: mod by 0");
            }
          }
        }
        postfix.pop();
      }
      res.push(calc.top());
    }
  }
}

