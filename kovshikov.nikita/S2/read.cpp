#include "read.hpp"
#include <cstring>
#include <iostream>

void kovshikov::readTerminal(std::istream& in, Queue< std::string >& allData) // allData очередь очередей для хранения постфиксных форм
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













 /* while(std::cin.eof())
  {
    Stack< std::string > stack; // стэк для временного хранения данных
    Queue< std::string > finishQueue; // конечная очередь в постфиксной форме
    Queue< std::string > startQueue // начальная очередь которая хранит в себе арифметическое выражение

 }*/
