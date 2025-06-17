#include <cassert>
#include <iostream>

#include "HashTable.h"

int main() {
    HashTable<int> table;
    table.insert("x", 5);
    assert(table["x"] == 5);

    table.pop("x");
    try {
        std::cout << table["x"] << std::endl;
    }
    catch (HashTableKeyNotFoundException& e) {
        std::cout << "Exception correctly thrown!" << std::endl;
    }

    table.insert("y", 1574);
    assert(table.find(1574) == "y");

    try {
        std::cout << table.find(1577) << std::endl;
    }
    catch (HashTableValueNotFoundException<int>& e) {
        std::cout << "Indeed couldn't find " << e.value << std::endl;
    }

    assert(table.size() == 1);
    table.insert("a", 0);
    assert(table.size() == 2);
    assert(table.has("a"));

    auto other(table);
    assert(other.size() == 2);
    assert(other.has("a"));
    assert(other["a"] == 0);

    other = table;
    assert(other.size() == 2);
    assert(other.has("a"));
    assert(other["a"] == 0);
}