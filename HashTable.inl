#include "HashTable.h"
#include <algorithm>

HashTableKeyNotFoundException::HashTableKeyNotFoundException(const std::string& key)
    : std::runtime_error("HashTable: Key not found: " + key) {
}

template <typename T>
HashTableValueNotFoundException<T>::HashTableValueNotFoundException(const T& v)
    : std::runtime_error("HashTable: Value not found"), value(v) {
}

template <typename T>
void HashTable<T>::initializeFrom(const HashTable<T>& other) {
    std::copy(other.m_items, other.m_items + HASH_TABLE_SIZE, m_items);
}

template <typename T>
HashTable<T>::HashTable(const HashTable<T>& other) {
    initializeFrom(other);
}

template <typename T>
HashTable<T>& HashTable<T>::operator=(const HashTable<T>& other) {
    initializeFrom(other);
    return *this;
}

template <typename T>
T& HashTable<T>::operator[](const std::string& key) {
    auto& item = get(key);
    if (item == nullptr) {
        throw HashTableKeyNotFoundException(key);
    }
    return item->second;
}

template <typename T>
const T& HashTable<T>::operator[](const std::string& key) const {
    return const_cast<HashTable<T>*>(this)[key];
}

template <typename T>
void HashTable<T>::insert(const std::string& key, const T& value) {
    auto& item = get(key);
    item = std::make_unique<std::pair<std::string, T>>(std::make_pair(key, value));
}

template <typename T>
void HashTable<T>::pop(const std::string& key) {
    auto& item = get(key);
    item = nullptr;
}

template <typename T>
size_t HashTable<T>::size() const {
    size_t result = 0;
    for (size_t i = 0; i < HASH_TABLE_SIZE; i++) {
        if (m_items[i] != nullptr) {
            result++;
        }
    }
    return result;
}

template <typename T>
const std::string& HashTable<T>::find(const T& item) const {
    for (size_t i = 0; i < HASH_TABLE_SIZE; i++) {
        if (m_items[i] != nullptr && m_items[i]->second == item) {
            return m_items[i]->first;
        }
    }
    throw HashTableValueNotFoundException<T>(item);
}

template <typename T>
bool HashTable<T>::has(const std::string& key) const {
    auto& item = get(key);
    return item != nullptr;
}

template <typename T>
std::unique_ptr<std::pair<std::string, T>>& HashTable<T>::get(const std::string& key) {
    return m_items[std::hash<std::string>{}(key) % HASH_TABLE_SIZE];
}

template <typename T>
const std::unique_ptr<std::pair<std::string, T>>& HashTable<T>::get(const std::string& key) const {
    return const_cast<HashTable<T>*>(this)->get(key);
}