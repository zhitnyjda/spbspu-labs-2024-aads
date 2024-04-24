#include <limits>
#include "list.hpp"
#include "inputPair.hpp"
#include "findSize.hpp"
#include "functions.hpp"

int main()
{
    using namespace jirkov;
    try
    {
        List<std::pair<std::string, List<size_t>>> list = listInput(std::cin);
        size_t sum = 0;
        bool overflowError = false;
        size_t maxSize = findSize(list);
        printListNames(list);
        List<size_t> sums;
        for (size_t index = 0; index < maxSize; index++)
        {
            printRowValues(list, index, sum, overflowError);
            if (!overflowError)
            {
                sums.pushBack(sum);
            }
            sum = 0;
            overflowError = false;
            std::cout << "\n";
        }
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
        return 0;
    }
    catch (std::overflow_error& e)
    {
        handleOverflowError();
        std::cerr << e.what() << "\n";
        return 1;
    }
}

