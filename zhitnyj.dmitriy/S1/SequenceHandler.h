#ifndef SEQUENCEHANDLER_H
#define SEQUENCEHANDLER_H

#include "List.h"
#include <string>
#include <map>

class SequenceHandler
{
    std::map<std::string, List<int>> sequences;

public:
    void addSequence(const std::string& name, const List<int>& sequence);
    void printSequences();
    void rearrangeAndPrint();
};

#endif
