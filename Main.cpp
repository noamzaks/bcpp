#include <iostream>

#include "String.h"

int main() {
    String hi("Hello");
    std::cout << hi << std::endl;
    hi = hi + String(" world!");
    std::cout << hi << std::endl;
}