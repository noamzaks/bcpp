#include <iostream>

#include "Complex.h"

Complex::Complex() : m_real(0), m_imaginary(0) {
    // Left blank intentionally
}

Complex::Complex(double real, double imaginary) : m_real(real), m_imaginary(imaginary) {
    // Left blank intentionally
}

double Complex::getReal() const {
    return m_real;
}
double Complex::getImaginary() const {
    return m_imaginary;
}

void Complex::setReal(double real) {
    m_real = real;
}

void Complex::setImaginary(double imaginary) {
    m_imaginary = imaginary;
}

bool Complex::operator==(const Complex& other) const {
    return m_real == other.m_real && m_imaginary == other.m_imaginary;
}

Complex& Complex::operator+=(const Complex& other) {
    *this = *this + other;
    return *this;
}

Complex& Complex::operator-=(const Complex& other) {
    *this = *this - other;
    return *this;
}

Complex& Complex::operator*=(const Complex& other) {
    *this = *this * other;
    return *this;
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(m_real + other.m_real, m_imaginary + other.m_imaginary);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(m_real - other.m_real, m_imaginary - other.m_imaginary);
}

Complex Complex::operator*(const Complex& other) const {
    return Complex(m_real * other.m_real - m_imaginary * other.m_imaginary,
                   m_real * other.m_imaginary + m_imaginary * other.m_real);
}

void Complex::print() const {
    std::cout << m_real;
    if (m_imaginary >= 0) {
        std::cout << '+';
    }
    std::cout << m_imaginary << 'i' << std::endl;
}