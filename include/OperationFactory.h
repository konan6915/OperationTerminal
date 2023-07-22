#ifndef __OPERATIONFACTORY_H_
#define __OPERATIONFACTORY_H_

#include "Operation.h"

class OperationFactory {
public:
    static Operation* createOperation(const std::string& operatorStr) {
        if (operatorStr == "+") {
            return new Addition();
        }
        else if (operatorStr == "-")
        {
            return new Subtraction();
        }
        else if (operatorStr == "*")
        {
            return new Multiplication();
        }
        else if (operatorStr == "/")
        {
            return new Division();
        }
        else if (operatorStr == "^") {
            return new Power();
        } else if (operatorStr == "sqrt") {
            return new SquareRoot();
        }

        throw std::runtime_error("Unsupported operator");
    }
};

#endif