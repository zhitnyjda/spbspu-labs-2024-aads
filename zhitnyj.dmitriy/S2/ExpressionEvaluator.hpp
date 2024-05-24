#ifndef EXPRESSION_EVALUATOR_HPP
#define EXPRESSION_EVALUATOR_HPP

#include <string>
#include <Queue.hpp>
#include <Stack.hpp>
#include "ExpressionItem.hpp"
#include "Operand.hpp"
#include "Operator.hpp"

class ExpressionEvaluator
{
public:
    ExpressionEvaluator() = default;
    ~ExpressionEvaluator() = default;

    static void parseExpression(Queue< std::shared_ptr< ExpressionItem > >& queue, const std::string& expression);
    static Queue< std::shared_ptr< ExpressionItem > > toPostfix(Queue< std::shared_ptr< ExpressionItem > >& infixQueue);
    static long long evaluateExpression(Queue< std::shared_ptr< ExpressionItem > >& postfixQueue);
};

#endif
