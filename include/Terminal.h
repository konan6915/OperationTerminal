#ifndef __TREMINAL_H_
#define __TREMINAL_H_
#include <iostream>
#include <string>
#include <cmath>
#include "OperationFactory.h"
class MatlabTerminal {
public:
    void run();

private:
    void evaluateExpression(const std::string& expression);
    double eval(const std::string& expression);
    double performOperation(double left, const std::string &operand, char lastOperator);
};

#endif