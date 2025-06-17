#pragma once

#include <memory>
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
    HashTable();
    HashTable(const HashTable<T>& other);
    HashTable& operator=(const HashTable<T>& other);

    T& operator[](const std::string& key);
    void insert(const std::string& key, const T& value);
    void pop(const std::string& key);

    size_t size() const;
    const std::string& find(const T& item) const;
    bool has(const std::string& key) const;

  private:
    void initializeFrom(const HashTable<T>& other);

    std::unique_ptr<std::pair<std::string, T>>& get(const std::string& key);
    const std::unique_ptr<std::pair<std::string, T>>& get(const std::string& key) const;

    std::unique_ptr<std::pair<std::string, T>> m_items[HASH_TABLE_SIZE];
};

#include "HashTable.inl"