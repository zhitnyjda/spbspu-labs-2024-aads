#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "list.hpp"

int main() {
    using namespace jirkov;
    List<std::pair<std::string, List<size_t>>> sequences;
    std::string name;
    while (std::cin >> name) {
        std::string input;
        std::getline(std::cin, input);

        List<size_t> sequence;
        std::istringstream iss(input);
        size_t num;
        while (iss >> num) {
            sequence.push_back(num);
        }
        sequences.push_back({name, sequence});
    }

    return 0;
}
