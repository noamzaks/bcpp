#include <iostream>
#include <string>
#include <iomanip>

// The table width and height to print in the program.
static constexpr int TABLE_SIZE = 11;

void printMultiplicationTable(uint64_t rowCount, uint64_t columnCount) {
    size_t cellWidth = std::to_string(rowCount * columnCount).length();

    for (uint64_t row = 1; row <= rowCount; row++) {
        for (uint64_t column = 1; column <= columnCount; column++) {
            std::cout << std::setw(cellWidth) << std::left << (row * column) << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    printMultiplicationTable(TABLE_SIZE, TABLE_SIZE);

    return 0;
}