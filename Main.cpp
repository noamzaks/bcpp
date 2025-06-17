#include <iostream>

#include "Calculator.h"

// Check out the calculator.
int main() {
    Calculator calculator;
    std::cout << calculator.add(2, 3) << std::endl;
    std::cout << calculator.subtract(2, 3) << std::endl;
    std::cout << calculator.multiply(2, 3) << std::endl;
    std::cout << calculator.divide(2, 3) << std::endl;
    std::cout << calculator.calculate(2, '+', 3) << std::endl;
    std::cout << calculator.calculate(2, '-', 3) << std::endl;
    std::cout << calculator.calculate(2, '*', 3) << std::endl;
    std::cout << calculator.calculate(2, '/', 3) << std::endl;

    // Should raise an exception.
    std::cout << calculator.calculate(2, 'x', 3) << std::endl;

    return 0;
}