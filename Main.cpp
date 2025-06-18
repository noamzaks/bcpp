#include "UniquePtr.h"

#include <cassert>
#include <iostream>

struct Demo
{
    int value;

    Demo(int value) : value(value) {
        // Intentionally left empty
    }

    ~Demo() {
        std::cout << "Destructed!" << std::endl;
    }
};

int main() {
    // Nothing should be printed.
    {
        UniquePtr<Demo> d;
        assert(!d);
    }

    // Should be called once.
    {
        auto d = makeUnique<Demo>(5);
        assert(d);
        assert(d->value == 5);
    }

    std::cout << "Starting Stage 1" << std::endl;
    // Should be called once.
    {
        auto d = makeUnique<Demo>(5);
        auto other(d);
        other->value = 2;
        other = d;
        other->value = 2;
        assert(other->value == 2);
        assert(d->value == 5);
        d = makeUnique<Demo>(2);
        std::cout << "Should have been destructed by now!" << std::endl;
    }

    std::cout << "Starting Stage 2" << std::endl;
    {
        auto d = std::move(makeUnique<Demo>(5));
        std::cout << "Should destruct before and after!" << std::endl;
    }
}