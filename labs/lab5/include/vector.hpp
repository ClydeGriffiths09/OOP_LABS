#pragma once

#include <cstdlib>
#include <memory_resource>
#include <utility>
#include <memory>

#include "exceptions.hpp"

template <typename T>
class Vector {
private:
    std::pmr::polymorphic_allocator<T> alloc_;
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;

public:
    class VectorIterator {
    private:
        T* current_;
        
    public:
        using value_type = T;
        using reference = value_type&;
        using pointer = value_type*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        VectorIterator() = default;
        explicit VectorIterator(T* ptr) : current_(ptr) {}
        
        bool operator==(const VectorIterator& other) const;
        bool operator!=(const VectorIterator& other) const;
        reference operator*() const;
        pointer operator->() const;
        VectorIterator& operator++();
        VectorIterator operator++(int);
    };

    Vector(std::pmr::memory_resource* res = std::pmr::get_default_resource());
    explicit Vector(size_t size, std::pmr::memory_resource* res = std::pmr::get_default_resource());
    Vector(size_t size, const T& value, std::pmr::memory_resource* res = std::pmr::get_default_resource());
    Vector(const std::initializer_list<T>& values, std::pmr::memory_resource* res = std::pmr::get_default_resource());
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    ~Vector();

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    VectorIterator Begin() noexcept;
    VectorIterator End() noexcept;
    VectorIterator Begin() const noexcept;
    VectorIterator End() const noexcept;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    T& At(size_t index);
    const T& At(size_t index) const;
    T& Front();
    const T& Front() const;
    T& Back();
    const T& Back() const;

    bool IsEmpty() const noexcept;
    size_t Size() const noexcept;
    size_t Capacity() const noexcept;

    void PushBack(const T& value);
    void PushBack(T&& value);
    void PopBack();
    void Clear() noexcept;
    void Resize(size_t new_size);
    void Resize(size_t new_size, const T& value);
    void Reserve(size_t new_capacity);
    
    VectorIterator Find(const T& value) const;

    std::pmr::memory_resource* GetResource() const;

private:
    void Reallocate(size_t new_capacity);
};

#include "vector.ipp"