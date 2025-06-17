#include "String.h"
#include <cstring>

String::String(const char* s) : m_s(nullptr), m_length(0) {
    initializeFrom(s, strlen(s));
}

void String::initializeFrom(const char* s, size_t length) {
    // Make sure to free the memory if initialized twice
    if (m_s != nullptr) {
        delete[] m_s;
    }

    m_s = new char[length + 1];
    memcpy(m_s, s, length + 1);
}

String::~String() {
    delete[] m_s;
}

String::String(const String& other) : m_s(nullptr), m_length(0) {
    initializeFrom(other.get(), other.length());
}

String& String::operator=(const String& other) {
    initializeFrom(other.get(), other.length());
    return *this;
}

String::String(const char* first, const char* second) : m_s(nullptr), m_length(0) {
    size_t firstSize = strlen(first), secondSize = strlen(second);
    m_length = firstSize + secondSize;
    m_s = new char[m_length + 1];
    memcpy(m_s, first, firstSize);
    memcpy(m_s + firstSize, second, secondSize + 1);
}

String String::operator+(const String& other) {
    return String(get(), other.get());
}

const char* String::get() const {
    return m_s;
}

const size_t String::length() const {
    return m_length;
}

std::ostream& operator<<(std::ostream& os, const String& s) {
    os << s.get();
    return os;
}