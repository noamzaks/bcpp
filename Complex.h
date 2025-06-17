#pragma once

class Complex
{
  public:
    /** Returns 0+0i. */
    Complex();
    Complex(double real, double imaginary);

    double getReal() const;
    double getImaginary() const;

    void setReal(double real);
    void setImaginary(double imaginary);

    bool operator==(const Complex& other) const;
    Complex& operator+=(const Complex& other);
    Complex& operator-=(const Complex& other);
    Complex& operator*=(const Complex& other);
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;

    /** Prints the complex number to standard output. */
    void print() const;

  private:
    double m_real;
    double m_imaginary;
};