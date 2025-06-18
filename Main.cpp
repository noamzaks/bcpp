#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>

/** XOR each character of the string with the given value. */
void xor_each(std::string& s, char value) {
    std::transform(s.cbegin(), s.cend(), s.begin(), std::bind(std::bit_xor<char>(), std::placeholders::_1, value));
}

/** Return the string flipped. */
std::string flip(const std::string& s) {
    return std::accumulate(s.crbegin(), s.crend(), std::string(), std::plus<>());
}

/** Return whether all of the characters in all of the words are uppercase. */
bool only_uppercase(const std::vector<std::string>& words) {
    return std::all_of(words.begin(), words.end(),
                       [](const std::string& word) { return std::all_of(word.cbegin(), word.cend(), isupper); });
}

/** Return the values flattened into a one-dimensional array. */
template <typename T>
std::vector<T> flatten(std::vector<std::vector<T>> matrix) {
    return std::accumulate(matrix.cbegin(), matrix.cend(), std::vector<T>(),
                           [](std::vector<T>& flat, std::vector<T> current) {
                               return flat.insert(flat.end(), current.begin(), current.end()).base() ? flat : flat;
                           });
}

int main() {
    // 1
    std::string test("hello");
    xor_each(test, 0x20); // Toggle lowercase and uppercase
    std::cout << test << std::endl;

    // 2
    std::cout << flip("hello") << std::endl;

    // 3
    std::cout << only_uppercase({"HELLO", "THERE"}) << std::endl;
    std::cout << only_uppercase({"HELLO", "THeRE"}) << std::endl;

    // 4
    for (int i : flatten<int>({{1, 2}, {3, 4}})) {
        std::cout << i << std::endl;
    }
}