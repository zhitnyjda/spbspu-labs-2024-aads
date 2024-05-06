#ifndef TYPES_HPP
#define TYPES_HPP
#include "stack.hpp"

namespace mihalchenko
{
    struct CalcRez
    {
        CalcRez() = default;
        CalcRez(long long value);
        // CalcRez operator+(const CalcRez & rhs);
        CalcRez operator+(CalcRez &rhs);
        // CalcRez operator-(const CalcRez & rhs);
        // CalcRez operator*(const CalcRez & rhs);
        // CalcRez operator/(const CalcRez & rhs);
        // CalcRez operator%(const CalcRez & rhs);
        long long resultCalc;
    };
}

mihalchenko::CalcRez::CalcRez(long long value)
{
    resultCalc = value;
}

// mihalchenko::CalcRez mihalchenko::CalcRez::operator+(const CalcRez & rhs)
mihalchenko::CalcRez mihalchenko::CalcRez::operator+(CalcRez &rhs)
{
    CalcRez result;
    resultCalc = 5;
    rhs.resultCalc = 7;
    result.resultCalc = resultCalc + rhs.resultCalc;
    return result;
}

#endif
