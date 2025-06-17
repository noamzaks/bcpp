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

class Calculator
{
  public:
    double add(double x, double y);
    double subtract(double x, double y);
    double multiply(double x, double y);
    double divide(double x, double y);
    double calculate(double x, char operation, double y);
};