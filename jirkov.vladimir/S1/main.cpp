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

        std::vector<size_t> sequence;
        std::istringstream iss(input);
        size_t num;
        while (iss >> num) {
            sequence.push_back(num);
        }
        sequences.push_back({name, sequence});
    }
    bool first =true;
    for (const auto& pair : sequences) {
        if (first) {
            first = false;
        }
        else {
            std::cout << ' ';
        }
        std::cout << pair.first;
    }
    if (sequences.empty()) {
        std::cout << 0 << '\n';
        return 0;
    }
    std::cout << std::endl;
    size_t maxlen = 0;
    for (const auto& pair : sequences) {
        maxlen = std::max(maxlen, static_cast<size_t>(pair.second.size()));
    }
    for (size_t i = 0; i < maxlen; ++i)
    {
        bool first = true;
        for (const auto & pair: sequences)
        {
            const auto & list = pair.second;
            auto it = list.begin();
            for (size_t j = 0; j < i && it != list.end(); ++j)
            {
                ++it;
            }
            if (it != list.end())
            {
                if (first)
                {
                    first = false;
                }
                else
                {
                    std::cout << ' ';
                }
                std::cout << *it;
            }
        }
        std::cout << '\n';
        if (sequences.empty())
        {
            std::cout << 0;
        }
    }
    std::vector<size_t> sums;
    try
    {
        for (size_t i = 0; i < maxlen; i++)
        {
            for (const auto & pair : sequences)
            {
                if (i < static_cast<size_t>(pair.second.size())) {
                    const auto & list = pair.second;
                    auto it = list.begin();
                    for (size_t j = 0; j < i && it != list.end(); ++j)
                    {
                        ++it;
                    }
                    if (static_cast<size_t>(i) >= static_cast<size_t>(sums.size())) {
                        sums.push_back(pair.second[i]);
                    } else {
                        sums[static_cast<size_t>(i)] += pair.second[i];
                    }
                }
            }
        }
    }
    catch (const std::overflow_error & e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    for (size_t i = 0; static_cast<size_t>(i) < static_cast<size_t>(sums.size()); i++) {
        std::cout << sums[i];
        if (static_cast<size_t>(i) != static_cast<size_t>(sums.size()) - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;

    return 0;
}
