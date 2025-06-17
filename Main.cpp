#include <iostream>

constexpr uint64_t SMALL_PRIMES[] = {2, 3, 5, 7}; 

/**
 * @return true if the number is a prime
 */
bool isPrime(uint64_t n) {
    if (n <= 1) {
        return false;
    }

    // Check small primes initially.
    for (uint64_t i : SMALL_PRIMES) {
        if (n == i) {
            return true;
        }
        if (n % i == 0) {
            return false;
        }
    }

    // Can skip even numbers now, since we already checked 2.
    for (uint64_t i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

int userCheckPrime() {
    uint64_t userInput = -1;

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