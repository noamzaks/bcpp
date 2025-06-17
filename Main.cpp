#include <iostream>
#include <cmath>

/**
 * Simple program to input a number and print its square root.
 *
 * @return 0 if succesful, negative number for error
 */
int userCalculateSqrt() {
    float userInput = -1;

    std::cout << "Please enter a number" << std::endl;
    
    std::cin >> userInput;
    while (std::cin.good() && userInput < 0) {
        std::cout << "Invalid input! Please enter a non-negative number" << std::endl;
        std::cin >> userInput;
    }

    if (std::cin.fail()) {
        std::cerr << "Invalid input received!" << std::endl;
        return -1;
    }

    std::cout << std::sqrt(userInput) << std::endl;
    
    return 0;
}

int main() {
    return userCalculateSqrt();
}