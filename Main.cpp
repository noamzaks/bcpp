#include "CustomAllocator.h"

int main() {
    char* first;
    char* second;

    AllocationInformation::printAllInformation();

    first = new char[1574];
    AllocationInformation::printAllInformation();

    second = new char[10];
    AllocationInformation::printAllInformation();

    delete[] first;
    AllocationInformation::printAllInformation();

    delete[] second;
    AllocationInformation::printAllInformation();

    first = new char[20];
    AllocationInformation::printAllInformation();
}