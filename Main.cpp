#include <iostream>

/**
 * @return true if the number is a prime
 */
bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

/**
 * Simple program to input a number and print its square root.
 *
 * @return 0 if succesful, negative number for error
 */
int userCheckPrime() {
    int userInput = -1;

    std::cout << "Please enter a number" << std::endl;

    std::cin >> userInput;
    if (std::cin.fail()) {
        std::cerr << "Invalid input received!" << std::endl;
        return -1;
    }

    if (isPrime(userInput)) {
        std::cout << "That's a prime!" << std::endl;
    }
    else {
        std::cout << "That's not a prime!" << std::endl; 
    }

    return 0;
}

int main() {
    return userCheckPrime();
}