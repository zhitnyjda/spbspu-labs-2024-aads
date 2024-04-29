#include "calculatingData.hpp"
#include <limits>
#include <string>
#include <iostream>

namespace jirkov {
    using listOfPairs = List<std::pair<std::string, List<size_t>>>;

    // Prints names from the list of pairs
    void printListNames(listOfPairs& newList) {
        auto iterator = newList.begin();
        if (iterator != newList.end()) {
            std::cout << iterator->first;
            ++iterator;
        }
        while (iterator != newList.end()) {
            std::cout << " " << iterator->first;
            ++iterator;
        }
        std::cout << "\n";
    }

    // Prints and calculates sum of values in list
    void printValues(listOfPairs& newList, List<size_t>& sums) {
        auto iterator = newList.begin();
        bool overflowError = false;
        const size_t maxSum = std::numeric_limits<size_t>::max();

        while (iterator != newList.end()) {
            size_t sum = 0;
            for (auto secondListIt = iterator->second.begin(); secondListIt != iterator->second.end(); ++secondListIt) {
                if (sum > maxSum - *secondListIt) {
                    std::cout << "\n";
                    throw std::overflow_error("Overflow error!");
                }
                sum += *secondListIt;
                std::cout << *secondListIt << " ";
            }
            std::cout << "\n";
            sums.pushBack(sum);
            ++iterator;
        }
    }

    // Outputs the sums stored in the list
    void getSums(List<size_t>& sums) {
        auto iterator = sums.begin();
        if (iterator != sums.end()) {
            std::cout << *iterator;
            ++iterator;
        }
        while (iterator != sums.end()) {
            std::cout << " " << *iterator;
            ++iterator;
        }
        std::cout << "\n";
    }

    // Determines the maximum size among the second elements in the pairs
    size_t findSize(listOfPairs& newList) {
        size_t maxSize = 0;
        for (auto iterator = newList.begin(); iterator != newList.end(); ++iterator) {
            maxSize = std::max(maxSize, iterator->second.getSize());
        }
        return maxSize;
    }

    // Parse input into list of pairs
    listOfPairs inputPair(std::istream& input) {
        listOfPairs inputList;
        std::string token;
        while (input >> token) {
            if (std::isalpha(token[0])) {
                inputList.pushBack({token, List<size_t>()});
            } else {
                size_t number = std::stoull(token);
                if (number > std::numeric_limits<size_t>::max()) {
                    throw std::overflow_error("Number exceeds maximum size_t value");
                }
                inputList.back().second.pushBack(number);
            }
        }
        return inputList;
    }
}
