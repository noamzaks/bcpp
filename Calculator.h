#pragma once

#include <exception>
#include <stdexcept>
#include <string>

class CalculatorException : public std::runtime_error
{
  public:
    CalculatorException(const std::string& message);
};

class CalculatorDivisionByZeroException : public CalculatorException
{
  public:
    CalculatorDivisionByZeroException(const std::string& message);
};

class CalculatorUnknownOperationException : public CalculatorException
{
  public:
    CalculatorUnknownOperationException(const std::string& message);
};

class Calculator final
{
  public:
    static double add(double x, double y);
    static double subtract(double x, double y);
    static double multiply(double x, double y);
    static double divide(double x, double y);
    static double calculate(double x, char operation, double y);
};