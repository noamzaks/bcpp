#include <cassert>
#include <iostream>

#include "String.h"

int main() {
    String hi("Hello");
    std::cout << hi << std::endl;
    hi = hi;
    hi = hi + String(" world!");
    std::cout << hi << std::endl;

    assert(!hi.empty());
    assert(String("").empty());

    assert(String("hello").rfind("r") == -1);
    assert(String("hello").rfind("l") == 3);

    try {
        String("Hello").erase(-1);
    }
    catch (StringIndexException& e) {
        std::cout << "Exception correctly thrown!" << std::endl;
    }
    try {
        String("Hello").erase(5);
    }
    catch (StringIndexException& e) {
        std::cout << "Exception correctly thrown!" << std::endl;
    }
    assert(String("Hello").erase(3) == String("Hel"));
    assert(String("Hellolo").erase(3, 2) == String("Hello"));
    assert(String("Hellolo").erase(3, 5) == String("Hel"));

    assert(String("Hello").insert(5, " world!") == "Hello world!");
    assert(String("Hello").insert(0, "Hello ") == "Hello Hello");
    assert(String("AA").insert(1, "BB") == "ABBA");

    assert(String("Hola").substr(2) == "la");
    assert(String("Hola").substr(2, 6) == "la");
    assert(String("Hola").substr(2, 3) == "l");
    assert(String("hi").rfind("HELLO WORLD THIS SHOULD NOT SEGFAULT EVER") == -1);
}