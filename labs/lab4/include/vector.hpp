#pragma once

#include "exceptions.hpp"
#include "figure.hpp"

#include <cstddef>
#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

namespace vector {

const size_t DEFAULT_CAPACITY = 10;

template <typename T> 
class Vector {
public:
    Vector();
    
    Vector(std::initializer_list<T> init);
    
    explicit Vector(size_t count, const T& value = T());
    
    Vector(const Vector& other);
    
    Vector(Vector&& other) noexcept;
    
    Vector& operator=(const Vector& other);
    
    Vector& operator=(Vector&& other) noexcept;
    
    T& operator[](size_t pos);
    
    const T& operator[](size_t pos) const;
    
    T& Front();
    
    T& Back();
    
    T* Data() noexcept;
    
    bool Empty() const noexcept;
    
    size_t Size() const noexcept;
    
    size_t Capacity() const noexcept;
    
    void Reserve(size_t new_capacity);
    
    void Clear() noexcept;
    
    void Insert(size_t pos, const T& value);
    
    void Erase(size_t pos);
    
    void Erase(size_t first, size_t last);
    
    void PushBack(const T& value);
    
    void PushBack(T&& value);
    
    void PopBack();
    
    void Resize(size_t count);
    
    void Resize(size_t count, const T& value);
    
    template <typename U>
    U TotalAreas() const;
    
    void PrintCenters() const;
    
    void PrintAreas() const;
    
    void swap(Vector& other) noexcept;
    
    ~Vector();

private:
    void Reallocate(size_t new_capacity);
    void DestroyRange(T* first, T* last) noexcept;
    
    std::shared_ptr<T[]> array_;
    size_t size_ = 0;
    size_t capacity_ = 0;
};

template <typename T>
void swap(Vector<T>& left, Vector<T>& right) noexcept;

}

#include "vector.ipp"