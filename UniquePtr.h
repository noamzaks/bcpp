#pragma once

template <typename T>
class UniquePtr final
{
  public:
    /** Initializes a default null pointer. */
    UniquePtr();
    /** Initializes a pointer from the given inner value, assumes ownership! */
    UniquePtr(T* inner);
    /** Destructs the pointer, if relevant. */
    ~UniquePtr();
    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr& operator=(const UniquePtr& other) = delete;
    /** Moves the other object inside. */
    UniquePtr(UniquePtr&& other);
    /** Moves the other object inside. */
    UniquePtr& operator=(UniquePtr&& other) noexcept;

    T* get();
    const T* get() const;
    T* operator->();
    const T* operator->() const;
    operator bool() const;
    operator T*();

  private:
    T* m_inner;
};

template <typename T, typename... Args>
UniquePtr<T> makeUnique(Args...);

#include "UniquePtr.inl"