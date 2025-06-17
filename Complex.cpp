#include <iostream>

#include "Complex.h"

Complex::Complex() : m_real(0), m_imaginary(0) {
}

Complex::Complex(double real, double imaginary) : m_real(real), m_imaginary(imaginary) {
}

double Complex::getReal() {
    return m_real;
}
double Complex::getImaginary() {
    return m_imaginary;
}

void Complex::setReal(double real) {
    m_real = real;
}

void Complex::setImaginary(double imaginary) {
    m_imaginary = imaginary;
}

bool Complex::operator==(const Complex& other) {
    return m_real == other.m_real && m_imaginary == other.m_imaginary;
}

Complex& Complex::operator+=(const Complex& other) {
    m_real += other.m_real;
    m_imaginary += other.m_imaginary;
    return *this;
}

Complex& Complex::operator-=(const Complex& other) {
    m_real -= other.m_real;
    m_imaginary -= other.m_imaginary;
    return *this;
}

Complex& Complex::operator*=(const Complex& other) {
    double real = m_real * other.m_real - m_imaginary * other.m_imaginary;
    double imaginary = m_real * other.m_imaginary + m_imaginary * other.m_real;
    m_real = real;
    m_imaginary = imaginary;
    return *this;
}

void Complex::print() {
    std::cout << m_real;
    if (m_imaginary >= 0) {
        std::cout << '+';
    }
    std::cout << m_imaginary << 'i' << std::endl;
}