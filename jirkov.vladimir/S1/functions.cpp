#include "functions.hpp"
#include "findSize.hpp"
#include <limits>
void jirkov::printListNames(const jirkov::List<std::pair<std::string, jirkov::List<size_t>>>& list)
{
    auto it = list.begin();
    while (it.node)
    {
        if (it.node != list.head_)
        {
            std::cout << " ";
        }
        std::cout << it.node->data.first;
        it++;
    }
    std::cout << "\n";
}

void jirkov::printRowValues(const List<std::pair<std::string, jirkov::List<size_t>>>& list, size_t index, size_t& sum, bool& overflowError)
{
    auto it = list.begin();
    size_t maximum = std::numeric_limits<size_t>::max();
    while (it.node)
    {
        if (it.node->data.second.getSize() > index)
        {
            if (sum > 0)
            {
                std::cout << " ";
            }
            size_t value = it.node->data.second[index]->data;
            std::cout << value;
            if (maximum - sum < value)
            {
                overflowError = true;
                throw std::overflow_error("Overflow error");
            }
            sum += value;
        }
        it++;
    }
}

void jirkov::handleOverflowError()
{
    std::cerr << "Overflow error occurred.\n";
}
