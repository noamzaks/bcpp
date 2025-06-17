#include <iostream>

#include "Calculator.h"

// Check out the calculator.
int main() {
    std::cout << Calculator::add(2, 3) << std::endl;
    std::cout << Calculator::subtract(2, 3) << std::endl;
    std::cout << Calculator::multiply(2, 3) << std::endl;
    std::cout << Calculator::divide(2, 3) << std::endl;
    std::cout << Calculator::calculate(2, '+', 3) << std::endl;
    std::cout << Calculator::calculate(2, '-', 3) << std::endl;
    std::cout << Calculator::calculate(2, '*', 3) << std::endl;
    std::cout << Calculator::calculate(2, '/', 3) << std::endl;

    // Should raise an exception.
    try {
        std::cout << Calculator::calculate(2, 'x', 3) << std::endl;
    }
    catch (CalculatorUnknownOperationException& e) {
        std::cout << "Correct exception thrown!" << std::endl;
    }

    return 0;
}