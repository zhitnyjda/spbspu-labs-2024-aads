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
        List<size_t> sums;
        if (list.empty())
        {
            std::cout << "0\n";
            return 0;
        }
        size_t maxSize = findSize(list);
        printListNames(list);
        printValues(list, maxSize, sums);
        printSums(sums);
        return 0;
    }
    catch (std::overflow_error& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
}
