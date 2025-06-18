#include <cstdint>

#include "Functors.h"

PrimeChecker::PrimeChecker() {
    // Intentionally left empty
}
bool PrimeChecker::operator()(uint64_t n) const {
    if (n <= 1) {
        return false;
    }

    for (uint64_t i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

GreaterChecker::GreaterChecker() {
    // Intentionally left empty
}
bool GreaterChecker::operator()(const std::pair<uint64_t, uint64_t>& numbers) const {
    return numbers.first > numbers.second;
}

DivisibleChecker::DivisibleChecker(uint64_t n) : m_n(n) {
    // Intentionally left empty
}
bool DivisibleChecker::operator()(uint64_t m) const {
    return m % m_n == 0;
}

RelativelyPrimeChecker::RelativelyPrimeChecker(uint64_t n) : m_n(n) {
    // Intentionally left empty
}
bool RelativelyPrimeChecker::operator()(uint64_t m) const {
    // C++17
    // return std::gcd(m_n, m) == 1;

    for (int i = 2; i * i <= m && i * i <= m_n; i++) {
        if (m % i == 0 && m_n % i == 0) {
            return false;
        }
    }

    if (m % m_n == 0 || m_n % m == 0) {
        return false;
    }

    return true;
}