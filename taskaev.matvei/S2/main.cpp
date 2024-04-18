#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  std::string mathValue;
  if(argc == 1)
  {
    while(!std::cin.eof())
    {
      std::getline(std::cin, mathValue);
      try
      {
        //function 
      }
      catch(...)
      {
        std::cerr << e.what() << "\n";
        return 1;
      }
    }
  }
  else if(argc == 2)
  {
    // не помню наверно стоит посмотреть как работали в P4 
  }
  else
  {
    std::cerr << "Error arguments, don't be greedy add more!\n";
    return 1;
  }
  return 0;
}
