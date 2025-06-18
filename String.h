#pragma once

#include <ostream>
#include <stdexcept>

class StringIndexException : public std::runtime_error
{
  public:
    StringIndexException();
};

class String
{
  public:
    /** Create a string from the given null-terminated string. */
    String(const char* s);
    virtual ~String();
    String(const String& other);
    String& operator=(const String& other);

    /** Get a pointer to the first character of the string. */
    const char* get() const;
    /** Get a pointer to the first character of the string. */
    const char* c_str() const;
    /** Return the length of the string. */
    size_t length() const;

    /**
     * Return the character at the given index in the string.
     *
     * @throw StringIndexException
     */
    char operator[](size_t index) const;
    /** Return whether the string is empty. */
    bool empty() const;
    /** Return the last index of the other string in this string, or -1 if not found. */
    size_t rfind(const String& other) const;

    /**
     * Erase the string from the given index onwards.
     *
     * @throw StringIndexException
     */
    String& erase(size_t index);
    /**
     * Erase the string from the given index for a given length.
     *
     * @throw StringIndexException
     */
    String& erase(size_t index, size_t length);
    /**
     * Insert the given string before the specified index.
     *
     * @throw StringIndexException
     */
    String& insert(size_t index, const String& other);

    /** Returns the substring from the given index onwards. */
    String substr(size_t from) const;
    /** Returns the substring from the given index until the given index. */
    String substr(size_t from, size_t to) const;

    /** Concatenates two strings. */
    String operator+(const String& other) const;

    bool operator==(const String& other) const;

  private:
    String(const char* s, size_t length);

    /** Throws a StringIndexException if the index is invalid. */
    void checkIndex(size_t index) const;

    size_t m_length;
    char* m_s;
};

std::ostream& operator<<(std::ostream& os, const String& s);