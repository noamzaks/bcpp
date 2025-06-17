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

void AllocationInformation::updateGlobalListOnCreation() {
    if (head == nullptr) {
        head = this;
        tail = this;
    }
    else {
        tail->setNext(this);
        tail = this;
    }
}

void AllocationInformation::updateGlobalListOnDeletion() {
    if (head == this) {
        head = getNext();
    }
    if (tail == this) {
        tail = getPrevious();
    }
}

void AllocationInformation::updateNeighborsOnDeletion() const {
    if (this->getPrevious() != nullptr) {
        this->getPrevious()->setNext(this->getNext());
    }
    if (this->getNext() != nullptr) {
        this->getNext()->setPrevious(this->getPrevious());
    }
}

void AllocationInformation::printAllInformation() {
    AllocationInformation* current = head;
    while (current != nullptr) {
        std::cout << current->size() << " bytes at " << current->getAddress() << std::endl;
        current = current->getNext();
    }
    std::cout << std::endl;
}

/** Allocates space for allocation information and stores it before returning the pointer. */
void* operator new(size_t n) {
    void* base = malloc(n + sizeof(AllocationInformation));

    if (base == NULL) {
        throw std::bad_alloc();
    }

    AllocationInformation* info = (AllocationInformation*)base;
    *info = AllocationInformation(n, tail);
    info->updateGlobalListOnCreation();

    return info->getAddress();
}

/** Frees the given data and updates the allocation information linked list. */
void operator delete(void* p) noexcept {
    AllocationInformation* info = AllocationInformation::getInformation(p);
    info->updateNeighborsOnDeletion();
    info->updateGlobalListOnDeletion();
    free(info);
}