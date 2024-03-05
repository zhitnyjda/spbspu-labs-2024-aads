#ifndef SEQUENCEHANDLER_H
#define SEQUENCEHANDLER_H

#include "List.h"
#include <string>
#include <map>
#include <sstream>

class SequenceHandler
{
    std::vector<std::pair<std::string, List<unsigned long long>>> sequences;

public:
    void addSequence(const std::string& name, const List<unsigned long long>& sequence);
    void printSequences();
    void rearrangeAndPrint();
};

#endif
