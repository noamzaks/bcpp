#include <iostream>
#include <string>
#include <iomanip>

static constexpr int TABLE_SIZE = 11;

/**
 * Simple program to print the multiplication table of the given size.
 */
void printMultiplicationTable(int row_count, int column_count) {
    int cellWidth = (int)std::to_string(row_count * column_count).length();

    for (int row = 1; row <= row_count; row++) {
        for (int column = 1; column <= column_count; column++) {
            std::cout << std::setw(cellWidth) << std::left << (row * column) << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    printMultiplicationTable(TABLE_SIZE, TABLE_SIZE);

    return 0;
}