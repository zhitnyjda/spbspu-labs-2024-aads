#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include "list.hpp"

int main() {
    jirkov::List<std::pair<std::string, std::vector<int>>> sequences;

    std::string name;
    while (std::cin >> name) {
        std::string input;
        std::getline(std::cin, input);

        std::vector<int> sequence;
        std::istringstream iss(input);
        int num;
        while (iss >> num) {
            sequence.push_back(num);
        }
        sequences.push_back({name, sequence});
    }
    std::cout << "\n";
    for (const auto& pair : sequences) {
        std::cout << pair.first << " ";
    }
    std::cout << std::endl;

    std::vector<std::vector<int>> mergedSequences;
    for (const auto& pair : sequences) {
        const auto& sequence = pair.second;
        for (size_t i = 0; i < sequence.size(); i++) {
            if (i >= mergedSequences.size()) {
                mergedSequences.resize(i+1);
            }
            mergedSequences[i].push_back(sequence[i]);
        }
    }
    for (const auto& seq : mergedSequences) {
        for (const auto& num : seq) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
    for (const auto& seq: sequences) {
        if (!seq.second.empty()) {
            int sum = 0;
            for (int num: seq.second) {
                sum += num;
            }
            std::cout << sum << " ";
        }
    }
    return 0;
}
