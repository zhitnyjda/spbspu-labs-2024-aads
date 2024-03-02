#include <iostream>
#include "list.hpp"

int main() {
    List<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    std::cout << "List size: " << '\n';

    std::cout << "List elements:" << '\n';
    return 0;
}
