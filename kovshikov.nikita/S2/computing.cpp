#include "computing.hpp"
#include <cstring>

void kovshikov::readData(std::istream& in, Queue< std::string >& allData)
{
  while(!in.eof())
  {
    std::string expression = "";
    std::getline(in, expression);
    if(!expression.empty())
    {
      allData.push(expression);
    }
  }
}

void kovshikov::separateElements(std::string str, Queue< std::string >& queue)
{
  std::string temp = "";
  size_t sizeStr = str.length();
  for(size_t i = 0; i < sizeStr; i++)
  {
    if(str[i] != ' ')
    {
      temp += str[i];
    }
    else
    {
      queue.push(temp);
      temp = "";
    }
  }
  queue.push(temp)
}

 /* while(std::cin.eof())
  {
    Stack< std::string > stack; // стэк для временного хранения данных
    Queue< std::string > finishQueue; // конечная очередь в постфиксной форме
    Queue< std::string > startQueue // начальная очередь которая хранит в себе арифметическое выражение

 }*/
