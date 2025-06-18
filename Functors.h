#pragma once

#include <cstdint>
#include <utility>

/** A functor that checks if a number is prime. */
class PrimeChecker
{
  public:
    PrimeChecker();
    bool operator()(uint64_t n) const;
};

/** A functor that checks if the first number is larger than the second. */
class GreaterChecker
{
  public:
    GreaterChecker();
    bool operator()(const std::pair<uint64_t, uint64_t>& numbers) const;
};

/** A functor that checks if numbers are visible by `n`. */
class DivisibleChecker
{
  public:
    DivisibleChecker(uint64_t n);
    bool operator()(uint64_t m) const;

  private:
    uint64_t m_n;
};

/** A functor that checks if numbers are relatively prime to `n`. */
class RelativelyPrimeChecker
{
  public:
    RelativelyPrimeChecker(uint64_t n);
    bool operator()(uint64_t m) const;

  private:
    uint64_t m_n;
};