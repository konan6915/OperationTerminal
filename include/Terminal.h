#ifndef __TREMINAL_H_
#define __TREMINAL_H_
#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include "OperationFactory.h"
class MatlabTerminal {
public:
    void run();

private:
    void evaluateExpression(const std::string& expression);
    double eval(const std::string& expression);
    void calculate(std::stack<double> &numbers, std::stack<char> &operators);
    double parseNumber(const std::string& expression, size_t& startPos);
};

#endif