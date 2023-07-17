#include "Terminal.h"

void MatlabTerminal::run() {
    std::string expression;
    std::cout << "Welcome to my computing terminal!" << std::endl;
    while (true) {
        
        std::cout << ">> ";
        // 从输入流中读取一行文本的函数
        getline(std::cin, expression);
        if (expression == "q") {
            break;
        }
        evaluateExpression(expression);
    }
}

void MatlabTerminal::evaluateExpression(const std::string& expression) {
    try {
        double result = eval(expression);
        std::cout << result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

double MatlabTerminal::eval(const std::string& expression) {
    double result = 0;
    size_t startPos = 0;
    char lastOperator = '+';

    while (startPos < expression.length())
    {
        size_t operatorPos = expression.find_first_of("+-*/", startPos);
        if (operatorPos == std::string::npos)
        {
            std::string operand = expression.substr(startPos);
            result = performOperation(result, operand, lastOperator);
            break;
        }

        std::string operand = expression.substr(startPos, operatorPos - startPos);
        result = performOperation(result, operand, lastOperator);

        char operatorChar = expression[operatorPos];
        lastOperator = operatorChar;

        startPos = operatorPos + 1;
    }

    return result;
}

double MatlabTerminal::performOperation(double left, const std::string &operand, char lastOperator)
{
    Operation *operation = OperationFactory::createOperation(std::string(1, lastOperator));
    double value = stod(operand);
    double result = operation->evaluate(left, value);

    delete operation;

    return result;
}