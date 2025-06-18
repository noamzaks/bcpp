#include "UniquePtr.h"

#include <cassert>
#include <iostream>
#include <memory>

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

struct CopyableDemo
{
    int value;

    CopyableDemo(int v) : value(v) {
        // Intentionally left empty
    }
    CopyableDemo(const CopyableDemo& other) {
        std::cout << "Copied!" << std::endl;
    }
    CopyableDemo& operator=(const CopyableDemo& other) {
        std::cout << "Copied!" << std::endl;
        return *this;
    }
    CopyableDemo(const CopyableDemo&& other) {
        // Intentionally left empty
    }
    CopyableDemo& operator=(const CopyableDemo&& other) {
        // Intentionally left empty
    }
};

struct CopyableDemoContainer
{
    CopyableDemoContainer(CopyableDemo& d) : d(d) {
        // Intentionally left empty
    }
    CopyableDemo& d;
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

    std::cout << "Starting Stage 2" << std::endl;
    {
        auto d = std::move(makeUnique<Demo>(5));
        std::cout << "Should destruct before and after!" << std::endl;
    }

    {
        auto d = makeUnique<Demo>(5);
        d = std::move(d);
        std::cout << d->value << std::endl;
    }

    // Should not print "Copied!"
    {
        auto demo = CopyableDemo(5);
        auto d = makeUnique<CopyableDemoContainer>(demo);
    }
}