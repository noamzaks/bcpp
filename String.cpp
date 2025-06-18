#include "String.h"
#include <cstring>

StringIndexException::StringIndexException() : std::runtime_error("Invalid index for string!") {
}

String::String(const char* s) : String(s, strlen(s)) {
}

String::String(const char* s, size_t length) : m_length(length), m_s(new char[length + 1]) {
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
    delete[] m_s;
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

const char* String::c_str() const {
    return get();
}

size_t String::length() const {
    return m_length;
}

char String::operator[](size_t index) const {
    checkIndex(index);
    return m_s[index];
}

bool String::empty() const {
    return m_length == 0;
}

size_t String::rfind(const String& other) const {
    if (m_length < other.m_length) {
        return -1;
    }

    size_t start = m_length - 1 - other.m_length;
    if (m_length == other.m_length) {
        start = 0;
    }

    for (size_t index = start;; index--) {
        if (memcmp(m_s + index, other.m_s, other.m_length) == 0) {
            return index;
        }

        if (index == 0) {
            break;
        }
    }

    return -1;
}

String& String::erase(size_t index) {
    checkIndex(index);
    m_s[index] = '\0';
    *this = String(m_s);

    return *this;
}

String& String::erase(size_t index, size_t length) {
    checkIndex(index);
    size_t end = index + length;

    if (end >= m_length) {
        return erase(index);
    }

    m_s[index] = '\0';
    *this = String(m_s) + String(m_s + end);

    return *this;
}

String& String::insert(size_t index, const String& other) {
    // We allow m_length for this function specifically.
    if (index != m_length) {
        checkIndex(index);
    }

    char current = m_s[index];
    m_s[index] = '\0';
    String result = String(m_s) + other;
    m_s[index] = current;
    result = result + String(m_s + index);

    *this = result;

    return *this;
}

String String::substr(size_t from) const {
    checkIndex(from);
    return String(m_s + from);
}

String String::substr(size_t from, size_t to) const {
    checkIndex(from);
    if (to >= m_length) {
        return substr(from);
    }

    String modified(m_s);
    modified.m_s[to] = '\0';
    return String(modified.m_s + from);
}

bool String::operator==(const String& other) const {
    return m_length == other.m_length && memcmp(m_s, other.m_s, m_length) == 0;
}

void String::checkIndex(size_t index) const {
    if (0 > index || index >= m_length) {
        throw StringIndexException();
    }
}

std::ostream& operator<<(std::ostream& os, const String& s) {
    os << s.get();
    return os;
}