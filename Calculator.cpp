#include "Calculator.h"

CalculatorException::CalculatorException(const std::string& message) : std::runtime_error(message) {
}

CalculatorDivisionByZeroException::CalculatorDivisionByZeroException(const std::string& message)
    : CalculatorException(message) {
}

CalculatorUnknownOperationException::CalculatorUnknownOperationException(const std::string& message)
    : CalculatorException(message) {
}

double Calculator::add(double x, double y) {
    return x + y;
}

double Calculator::subtract(double x, double y) {
    return x - y;
}

double Calculator::multiply(double x, double y) {
    return x * y;
}

double Calculator::divide(double x, double y) {
    if (y == 0) {
        throw CalculatorDivisionByZeroException("Division by zero!");
    }
    return x / y;
}

double Calculator::calculate(double x, char operation, double y) {
    switch (operation) {
    case '+':
        return add(x, y);
    case '-':
        return subtract(x, y);
    case '*':
        return multiply(x, y);
    case '/':
        return divide(x, y);
    default:
        throw CalculatorUnknownOperationException(std::string("Unknown operation '") + operation + "'");
    }
}