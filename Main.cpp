#include "Functors.h"
#include <iostream>

int main() {
    // 1
    PrimeChecker primeChecker;
    std::cout << primeChecker(1) << " " << primeChecker(5) << " " << primeChecker(9) << std::endl;

    // 2
    GreaterChecker greaterChecker;
    std::cout << greaterChecker({2, 1}) << " " << greaterChecker({2, 2}) << " " << greaterChecker({2, 3}) << std::endl;

    // 3
    DivisibleChecker divisibleChecker(3);
    std::cout << divisibleChecker(9) << " " << divisibleChecker(4) << std::endl;

    // 4
    RelativelyPrimeChecker relativePrimeChecker(6);
    std::cout << relativePrimeChecker(2) << " " << relativePrimeChecker(3) << " " << relativePrimeChecker(35) << " "
              << relativePrimeChecker(16) << " " << relativePrimeChecker(7) << std::endl;
}