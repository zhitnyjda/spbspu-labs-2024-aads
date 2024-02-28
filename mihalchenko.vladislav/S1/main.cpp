#include <iostream>
#include <string>
#include "list.hpp"

using namespace mihalchenko;

int main()
{
    std::cout << "Hello World" << std::endl;
    List<int> lst;
    lst.pushBack(5);
    lst.pushBack(10);
    lst.pushBack(22);
    std::cout << lst[1] << std::endl;

    return 0;
}
