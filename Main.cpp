#include <future>
#include <iostream>

#include "PrimeCheck.h"

// The size of the test array for the program itself.
static constexpr int ARRAY_TEST_SIZE = 20;

// The number of threads to use for filling the array.
static constexpr int THREAD_COUNT = 4;

// The amount of consecutive numbers each thread searches for a primes within.
// This will be scaled by the amount of primes searched for.
static constexpr int SINGLE_PRIME_SEARCH_RANGE = 10;

/**
 * Fills the array with primes in the given range.
 *
 * Looks for the first `arrayLength` primes in the range from start (inclusive) to end (non-inclusive).
 *
 * @param array a pointer to store the primes in.
 * @param arrayLength the amount of primes to insert into the array.
 * @param start the start of the range to find primes in (inclusive).
 * @param end the end of the range to find primes in (non-inclusive).
 *
 * @return whether enough primes were found to fill the array.
 */
bool fillPrimesInRange(uint64_t* array, size_t arrayLength, uint64_t start, uint64_t end) {
    size_t current = 0;
    for (uint64_t n = start; n < end && current < arrayLength; n++) {
        if (isPrime(n)) {
            array[current] = n;
            current++;
        }
    }
    return current == arrayLength;
}

/**
 * Returns the `index`-th consecutive `rangeSize` start and end indices.
 *
 * @example getRangeStartAndEnd(4, 3) returns (12, 16).
 */
std::tuple<uint64_t, uint64_t> getRangeStartAndEnd(size_t index, size_t rangeSize) {
    return std::make_tuple(index * rangeSize, (index + 1) * rangeSize);
}

/**
 * Threaded function to fill the array with different primes.
 *
 * Creates THREAD_COUNT thread each searching in a separate range for primes.
 * WARNING: This (pseudo)-fast function doesn't always work, you should tune SINGLE_PRIME_SEARCH_RANGE.
 *
 * @return whether succesful.
 */
int fillArrayWithPrimes(uint64_t* array, size_t arrayLength) {
    std::future<bool> threads[THREAD_COUNT];

    uint64_t chunkSize = arrayLength / THREAD_COUNT;
    size_t currentStart = 0;
    size_t currentEnd = chunkSize;

    for (int threadIndex = 0; threadIndex < THREAD_COUNT; threadIndex++) {
        // Make sure last thread finishes the array.
        if (threadIndex == THREAD_COUNT - 1) {
            currentEnd = arrayLength;
        }

        auto [rangeStart, rangeEnd] = getRangeStartAndEnd(threadIndex, chunkSize * SINGLE_PRIME_SEARCH_RANGE);
        threads[threadIndex] =
            std::async(fillPrimesInRange, array + currentStart, currentEnd - currentStart, rangeStart, rangeEnd);

        currentStart += chunkSize;
        currentEnd += chunkSize;
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        if (!threads[i].get()) {
            std::cerr << "Search range too small! Couldn't find primes." << std::endl;
            return -1;
        }
    }

    return 0;
}

/** Prints the given array in a single line. */
void printArray(const uint64_t* array, size_t arrayLength) {
    for (size_t i = 0; i < arrayLength; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    auto array = new uint64_t[ARRAY_TEST_SIZE];

    int fillingOk = fillArrayWithPrimes(array, ARRAY_TEST_SIZE);
    if (fillingOk != 0) {
        delete[] array;
        return fillingOk;
    }
    printArray(array, ARRAY_TEST_SIZE);

    delete[] array;
}