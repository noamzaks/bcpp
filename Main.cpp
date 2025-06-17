#include <iostream>
#include <thread>
#include <future>

// The size of the test array for the program itself.
static constexpr int ARRAY_TEST_SIZE = 20;

// The number of threads to use for filling the array.
static constexpr int THREAD_COUNT = 4;

// The amount of consecutive numbers each thread searches for a primes within.
// This will be scaled by the amount of primes searched for.
static constexpr int SEARCH_RANGE_SIZE = 10;

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
 * Fills the array with primes in the given range.
 * 
 * @return whether enough primes were found to fill the array.
 */
bool fillPrimesInRange(int* array, int arrayLength, int start, int end) {
    int current = 0;
    for (int n = start; n < end && current < arrayLength; n++) {
        if (isPrime(n)) {
            array[current] = n;
            current++;
        }
    }
    return current == arrayLength;
}

/**
 * Threaded function to fill the array with different primes.
 *
 * Creates THREAD_COUNT thread each searching in a separate range for primes.
 *
 * @return 0 if successful or a negative number if an error occurred.
 */
int fillArrayWithPrimes(int* array, int arrayLength) {
    std::future<bool> threads[THREAD_COUNT];

    int chunkSize = arrayLength / THREAD_COUNT;
    int currentStart = 0;
    int currentEnd = chunkSize;
    int rangeStart = 2;
    int rangeEnd = 2;

    for (int i = 0; i < THREAD_COUNT; i++) {
        // Make sure last thread finishes the array.
        if (i == THREAD_COUNT - 1) {
            currentEnd = arrayLength;
        }

        rangeEnd = rangeStart + SEARCH_RANGE_SIZE * (currentEnd - currentStart);
        threads[i] = std::async(fillPrimesInRange, array + currentStart, currentEnd - currentStart,
                                 rangeStart, rangeEnd);
        rangeStart = rangeEnd;

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
void printArray(int* array, int arrayLength) {
    for (int i = 0; i < arrayLength; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int* array = new int[ARRAY_TEST_SIZE];
    
    int fillingOk = fillArrayWithPrimes(array, ARRAY_TEST_SIZE);
    if (fillingOk != 0) {
        delete[] array;
        return fillingOk;
    }
    printArray(array, ARRAY_TEST_SIZE);

    delete[] array;
}