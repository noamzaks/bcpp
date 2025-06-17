#pragma once

#include <memory>
#include <ostream>

class String
{
  public:
    explicit String(const char* s);
    ~String();
    String(const String& other);
    String& operator=(const String& other);

    /** Creates a string from concatenating the strings. */
    String(const char* first, const char* second);
    String operator+(const String& other);

    const char* get() const;
    const size_t length() const;

  private:
    void initializeFrom(const char* s, size_t length);

    char* m_s;
    size_t m_length;
};

std::ostream& operator<<(std::ostream& os, const String& s);