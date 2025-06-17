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
bool fillPrimesInRange(int* array, int array_length, int start, int end) {
    int current = 0;
    for (int n = start; n < end && current < array_length; n++) {
        if (isPrime(n)) {
            array[current] = n;
            current++;
        }
    }
    return current == array_length;
}

/**
 * Threaded function to fill the array with different primes.
 *
 * Creates THREAD_COUNT thread each searching in a separate range for primes.
 *
 * @return 0 if successful or a negative number if an error occurred.
 */
int fillArrayWithPrimes(int* array, int array_length) {
    std::future<bool> threads[THREAD_COUNT];

    int chunk_size = array_length / THREAD_COUNT;
    int current_start = 0;
    int current_end = chunk_size;
    int range_start = 2;
    int range_end = 2;

    for (int i = 0; i < THREAD_COUNT; i++) {
        // Make sure last thread finishes the array.
        if (i == THREAD_COUNT - 1) {
            current_end = array_length;
        }

        range_end = range_start + SEARCH_RANGE_SIZE * (current_end - current_start);
        threads[i] = std::async(fillPrimesInRange, array + current_start, current_end - current_start,
                                 range_start, range_end);
        range_start = range_end;

        current_start += chunk_size;
        current_end += chunk_size;
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
void printArray(int* array, int array_length) {
    for (int i = 0; i < array_length; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int* array = new int[ARRAY_TEST_SIZE];
    
    int filling_ok = fillArrayWithPrimes(array, ARRAY_TEST_SIZE);
    if (filling_ok != 0) {
        delete[] array;
        return filling_ok;
    }
    printArray(array, ARRAY_TEST_SIZE);

    delete[] array;
}