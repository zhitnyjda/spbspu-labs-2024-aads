#include "calculatingData.hpp"
#include <limits>
#include <string>
#include <iostream>

namespace jirkov {
    using listOfPairs = List<std::pair<std::string, List<size_t>>>;

    void printListNames(listOfPairs& newList) {
        auto iterator = newList.begin();
        do {
            if (iterator != newList.begin()) {
                std::cout << " ";
            }
            std::cout << iterator->first;
            iterator++;
        } while (iterator != nullptr);
        std::cout << "\n";
    }
    void printValues(listOfPairs& newList, bool& overflowFlag, List<size_t>& sums) {
        auto iterator = newList.begin();
        const size_t maxSum = std::numeric_limits<size_t>::max();
        for (size_t i = 0; i < findSize(newList); i++) {
            iterator = newList.begin();
            size_t sum = 0;
            while (it != nullptr) {
                List< size_t >::Iterator argsIt = iterator->second[i];
                    if (iterator->second[i] != nullptr)
                    {
                        if (sum != 0) {
                        std::cout << " ";
                    }
                    std::cout << *argsIt;
                    if (sum > maxSum - *argsIt)
                    {
                        overflowFlag = true;
                        std::cout << "\n";
                        throw std::overflow_error("overflow error");
                    }
                    else
                    {
                        sum += *argsIt;
                    }
                }
                iterator++;
            }
            std::cout << "\n";
            sums.pushBack(sum);
        }
    }
    void getSums(List<size_t>& sums) {
        auto iterator = sums.begin();
        do {
            if (iterator != sums.begin()) {
                std::cout << " ";
            }
            std::cout << *iterator;
            iterator++;
        } while (iterator != nullptr);
        std::cout << "\n";
    }

    size_t findSize(listOfPairs& newList) {
        size_t maxSize = 0;
        for (auto iterator = newList.begin(); iterator != newList.end(); ++iterator) {
            maxSize = std::max(maxSize, iterator->second.getSize());
        }
        return maxSize;
    }

    listOfPairs inputPair(std::istream& input) {
        std::string name = "";
        List< size_t > args;
        listOfPairs resultList;
        input >> name;
        while (input) {
            resultList.pushBack({ name, args });
            while (input >> name && std::isdigit(name[0])) {
                resultList.back().second.pushBack(std::stoul(name));
            }
        }
        return resultList;
    }
}
