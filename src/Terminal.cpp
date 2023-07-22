#include "Terminal.h"
#include <stack>
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

double MatlabTerminal::eval(const std::string &expression)
{
    std::stack<double> numbers;
    std::stack<char> operators;
    size_t startPos = 0;
    while (startPos < expression.length())
    {
        if (isdigit(expression[startPos]))
        {
            size_t endPos = startPos;
            while (endPos < expression.length() && (isdigit(expression[endPos]) || expression[endPos] == '.'))
            {
                endPos++;
            }
            std::string numberStr = expression.substr(startPos, endPos - startPos);
            double number = stod(numberStr);
            numbers.push(number);
            startPos = endPos;
        }
        else if (expression[startPos] == '+' || expression[startPos] == '-')
        {
            while (!operators.empty() && (operators.top() == '+' || operators.top() == '-' || operators.top() == '*' || operators.top() == '/'))
            {
                calculate(numbers, operators);
            }
            operators.push(expression[startPos]);
            startPos++;
        }
        else if (expression[startPos] == '*' || expression[startPos] == '/')
        {
            while (!operators.empty() && (operators.top() == '*' || operators.top() == '/'))
            {
                calculate(numbers, operators);
            }
            operators.push(expression[startPos]);
            startPos++;
        }
        else if (expression[startPos] == '(')
        {
            operators.push(expression[startPos]);
            startPos++;
        }
        else if (expression[startPos] == ')')
        {
            while (operators.top() != '(')
            {
                calculate(numbers, operators);
            }
            operators.pop();
            startPos++;
        }
        else if (expression[startPos] == '^')
        {
            // 处理乘方运算符 "^"
            startPos++; // 跳过 "^"
            double exponent = parseNumber(expression, startPos);
            double base = numbers.top();
            numbers.pop();
            double result = pow(base, exponent);
            numbers.push(result);
        }
        else if (expression[startPos] == 's' && expression.substr(startPos, 4) == "sqrt")
        {
            // 处理开方运算符 "sqrt"
            startPos += 4; // 跳过 "sqrt"
            if (expression[startPos] != '(')
            {
                throw std::runtime_error("Expected '(' after 'sqrt'");
            }
            startPos++; // 跳过 '('
            double value = parseNumber(expression, startPos);
            if (expression[startPos] != ')')
            {
                throw std::runtime_error("Expected ')' after number in 'sqrt'");
            }
            startPos++; // 跳过 ')'
            if (value < 0)
            {
                throw std::runtime_error("Square root of negative number");
            }
            double result = sqrt(value);
            numbers.push(result);
        }
        else
        {
            startPos++;
        }
    }

    while (!operators.empty())
    {
        calculate(numbers, operators);
    }

    return numbers.top();
}

void MatlabTerminal::calculate(std::stack<double> &numbers, std::stack<char> &operators)
{
    char op = operators.top();
    operators.pop();

    double right = numbers.top();
    numbers.pop();
    double left = numbers.top();
    numbers.pop();

    Operation *operation = OperationFactory::createOperation(std::string(1, op));
    double result = operation->evaluate(left, right);
    delete operation;

    numbers.push(result);
}

double MatlabTerminal::parseNumber(const std::string& expression, size_t& startPos)
{
    size_t endPos = startPos;
    while (endPos < expression.length() && (isdigit(expression[endPos]) || expression[endPos] == '.')) {
        endPos++;
    }
    std::string numberStr = expression.substr(startPos, endPos - startPos);
    double number = std::stod(numberStr);
    startPos = endPos;
    return number;
}