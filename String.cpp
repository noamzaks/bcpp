#include "String.h"
#include <cstring>

String::String(const char* s) : m_length(strlen(s)), m_s(new char[m_length + 1]) {
    memcpy(m_s, s, m_length + 1);
}

String::~String() {
    delete[] m_s;
}

String::String(const String& other) : m_length(other.m_length), m_s(new char[m_length + 1]) {
    memcpy(m_s, other.get(), m_length + 1);
}

String& String::operator=(const String& other) {
    size_t length = other.m_length;
    char* s = new char[length + 1];
    memcpy(s, other.m_s, length + 1);
    this->~String();
    m_s = s;
    m_length = length;
    return *this;
}

String String::operator+(const String& other) const {
    size_t firstSize = m_length, secondSize = other.m_length;
    size_t length = firstSize + secondSize;
    char* s = new char[length + 1];
    memcpy(s, get(), firstSize);
    memcpy(s + firstSize, other.get(), secondSize + 1);
    String result(s);
    delete[] s;
    return result;
}

const char* String::get() const {
    return m_s;
}

size_t String::length() const {
    return m_length;
}

std::ostream& operator<<(std::ostream& os, const String& s) {
    os << s.get();
    return os;
}