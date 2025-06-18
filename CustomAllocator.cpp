#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <new>

#include "CustomAllocator.h"

AllocationInformation* AllocationInformation::s_head = nullptr;
AllocationInformation* AllocationInformation::s_tail = nullptr;

AllocationInformation::AllocationInformation(size_t size) : AllocationInformation(size, s_tail, nullptr) {
}

AllocationInformation::AllocationInformation(size_t size, AllocationInformation* previous, AllocationInformation* next)
    : m_size(size), m_previous(previous), m_next(next) {
    // Update the global head & tail about this new allocation information.
    if (s_head == nullptr) {
        s_head = this;
        s_tail = this;
    }
    else {
        s_tail->setNext(this);
        s_tail = this;
    }
}

AllocationInformation::~AllocationInformation() {
    updateNeighborsOnDeletion();
    updateGlobalListOnDeletion();
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

AllocationInformation* AllocationInformation::getInformation(void* p) {
    return (AllocationInformation*)((char*)p - sizeof(AllocationInformation));
}

void AllocationInformation::updateGlobalListOnDeletion() {
    if (s_head == this) {
        s_head = getNext();
    }
    if (s_tail == this) {
        s_tail = getPrevious();
    }
}

void AllocationInformation::updateNeighborsOnDeletion() {
    if (this->getPrevious() != nullptr) {
        this->getPrevious()->setNext(this->getNext());
    }
    if (this->getNext() != nullptr) {
        this->getNext()->setPrevious(this->getPrevious());
    }
}

void AllocationInformation::printAllInformation() {
    AllocationInformation* current = s_head;
    while (current != nullptr) {
        std::cout << current->size() << " bytes at " << current->getAddress() << std::endl;
        current = current->getNext();
    }
    std::cout << std::endl;
}

/** Allocates space for allocation information and stores it before returning the pointer. */
void* operator new(size_t n) {
    void* base = malloc(n + sizeof(AllocationInformation));

    if (base == nullptr) {
        throw std::bad_alloc();
    }

    AllocationInformation* info = new (base) AllocationInformation(n);

    return info->getAddress();
}

/** Frees the given data and updates the allocation information linked list. */
void operator delete(void* p) noexcept {
    AllocationInformation* info = AllocationInformation::getInformation(p);
    info->~AllocationInformation();
    free(info);
}