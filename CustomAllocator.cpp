#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <new>

#include "CustomAllocator.h"

static AllocationInformation* head = nullptr;
static AllocationInformation* tail = nullptr;

AllocationInformation::AllocationInformation(size_t size, AllocationInformation* previous, AllocationInformation* next)
    : m_size(size), m_next(next) {
    m_previous = previous;
    m_next = next;

    // Update the allocator head and tail.
    if (head == nullptr) {
        head = this;
    }
    else {
        tail->setNext(this);
        tail = this;
    }
}

size_t AllocationInformation::size() const {
    return m_size;
}

AllocationInformation* AllocationInformation::getNext() const {
    return m_next;
}

AllocationInformation* AllocationInformation::getPrevious() const {
    return m_previous;
}

void AllocationInformation::setPrevious(AllocationInformation* previous) {
    m_previous = previous;
}

void AllocationInformation::setNext(AllocationInformation* next) {
    m_next = next;
}

void* AllocationInformation::getAddress() const {
    return (void*)((char*)this + sizeof(AllocationInformation));
}

/** Allocates space for allocation information and stores it before returning the pointer. */
void* operator new(size_t n) {
    void* base = malloc(n + sizeof(AllocationInformation));

    if (base == NULL) {
        throw std::bad_alloc();
    }

    AllocationInformation* info = (AllocationInformation*)base;
    *info = AllocationInformation(n, tail);

    return (void*)((char*)base + sizeof(AllocationInformation));
}

void operator delete(void* p) noexcept {
    AllocationInformation* info = (AllocationInformation*)((char*)p - sizeof(AllocationInformation));
}