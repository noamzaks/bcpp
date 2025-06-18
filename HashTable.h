#pragma once

#include <array>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>

constexpr size_t HASH_TABLE_SIZE = 100;

class HashTableKeyNotFoundException : public std::runtime_error
{
  public:
    HashTableKeyNotFoundException(const std::string& key);
};

template <typename T>
class HashTableValueNotFoundException : public std::runtime_error
{
  public:
    HashTableValueNotFoundException(const T& value);
    T value;
};

template <typename T>
class HashTable
{
  public:
    HashTable() = default;
    ~HashTable() = default;
    HashTable(const HashTable<T>& other);
    HashTable& operator=(const HashTable<T>& other);

    T& operator[](const std::string& key);
    const T& operator[](const std::string& key) const;
    void insert(const std::string& key, const T& value);
    void pop(const std::string& key);

    size_t size() const;
    const std::string& find(const T& item) const;
    bool has(const std::string& key) const;

  private:
    void initializeFrom(const HashTable<T>& other);

    std::optional<std::pair<std::string, T>>& get(const std::string& key);
    const std::optional<std::pair<std::string, T>>& get(const std::string& key) const;

    std::array<std::optional<std::pair<std::string, T>>, HASH_TABLE_SIZE> m_items;
};

#include "HashTable.inl"