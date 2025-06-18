#include "UniquePtr.h"

#include <utility>

template <typename T>
UniquePtr<T>::UniquePtr() : m_inner(nullptr) {
    // Intentionally left empty
}

template <typename T>
UniquePtr<T>::UniquePtr(T* inner) : m_inner(inner) {
    // Intentionally left empty
}

template <typename T>
UniquePtr<T>::~UniquePtr() {
    if (m_inner) {
        m_inner->~T();
    }
}

template <typename T>
UniquePtr<T>::UniquePtr(const UniquePtr& other) : m_inner(nullptr) {
    if (other.m_inner) {
        m_inner = new T(*other.m_inner);
    }
}

template <typename T>
UniquePtr<T>& UniquePtr<T>::operator=(const UniquePtr& other) {
    this->~UniquePtr();
    m_inner = new T(*other.m_inner);
    return *this;
}

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr&& other) : m_inner(std::move(other.m_inner)) {
    // Intentionally left empty
}

template <typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr&& other) noexcept {
    this->~UniquePtr();
    m_inner = std::move(other.m_inner);
    return *this;
}

template <typename T>
T* UniquePtr<T>::get() {
    return m_inner;
}

template <typename T>
const T* UniquePtr<T>::get() const {
    return m_inner;
}

template <typename T>
T* UniquePtr<T>::operator->() {
    return m_inner;
}

template <typename T>
const T* UniquePtr<T>::operator->() const {
    return m_inner;
}

template <typename T>
UniquePtr<T>::operator bool() const {
    return m_inner != nullptr;
}

template <typename T>
UniquePtr<T>::operator T*() {
    return m_inner;
}

template <typename T, typename... Args>
UniquePtr<T> makeUnique(Args... args) {
    return UniquePtr<T>(new T(args...));
}