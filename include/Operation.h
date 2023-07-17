#ifndef __OPERATION_H_
#define __OPERATION_H_
#include <iostream>
#include <string>
class Operation {
public:
    virtual double evaluate(double left, double right) const = 0;
};

class Addition : public Operation {
public:
    double evaluate(double left, double right) const override {
        return left + right;
    }
};
class Subtraction : public Operation {
public:
    double evaluate(double left, double right) const override {
        return left - right;
    }
};
class Multiplication : public Operation {
public:
    double evaluate(double left, double right) const override {
        return left * right;
    }
};

class Division : public Operation {
public:
    double evaluate(double left, double right) const override {
        if (right == 0) {
            throw std::runtime_error("Division by zero");
        }
        return left / right;
    }
};

#endif