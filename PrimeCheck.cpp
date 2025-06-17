#include "PrimeCheck.h"

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