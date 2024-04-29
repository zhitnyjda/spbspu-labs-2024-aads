#include "functions.hpp"
#include "findSize.hpp"
#include <limits>

void jirkov::printListNames(const jirkov::List<std::pair<std::string, jirkov::List<size_t>>>& list)
{
    auto iterator = list.begin();
    while (iterator.node)
    {
        if (iterator.node != list.head_)
        {
            std::cout << " ";
        }
        std::cout << iterator.node->data.first;
        iterator++;
    }
    std::cout << "\n";
}
void jirkov::printValues(const jirkov::List<std::pair<std::string,jirkov::List<size_t>>>&list,size_t maxSize,jirkov::List<size_t>&sums)
{
    size_t sum = 0;
    bool overflowError = false;

    for (size_t index = 0; index < maxSize; index++)
    {
        auto iterator = list.begin();
        while (iterator.node)
        {
            auto& secondList = iterator.node->data.second;
            if (index < secondList.getSize())
            {
                size_t value = secondList[index]->data;
                if (sum > 0)
                {
                    std::cout << " ";
                }
                std::cout << value;
                checkForOverflow(sum, value);
                sum += value;
            }
            iterator++;
        }
        std::cout << "\n";

        if (!overflowError)
        {
            sums.pushBack(sum);
        }
        sum = 0;
        overflowError = false;
    }
}
void jirkov::printSums(jirkov::List<size_t>& sums)
{
    if (sums.empty())
    {
        std::cout << "0\n";
    }
    else
    {
        auto it = sums.begin();
        while (it.node)
        {
            if (it.node != sums.head_)
            {
                std::cout << " ";
            }
            std::cout << it.node->data;
            it++;
        }
        std::cout << "\n";
    }
}
void jirkov::checkForOverflow(size_t sum, size_t value)
{
    const size_t maximum = std::numeric_limits<size_t>::max();

    if (maximum - sum < value)
    {
        std::cout << "\n";
        throw std::overflow_error("Overflow error");
    }
}
