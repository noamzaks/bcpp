#pragma once

#include <memory>
#include <ostream>

class String
{
  public:
    explicit String(const char* s);
    virtual ~String();
    String(const String& other);
    String& operator=(const String& other);

    String operator+(const String& other) const;

    const char* get() const;
    size_t length() const;

  private:
    void initializeFrom(const char* s, size_t length);

    size_t m_length;
    char* m_s;
};

std::ostream& operator<<(std::ostream& os, const String& s);