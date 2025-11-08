#pragma once

#include "vector.hpp"
#include <algorithm>
#include <memory>
#include <utility>

namespace vector {

template <typename T>
Vector<T>::Vector() noexcept = default;

template <typename T>
Vector<T>::Vector(size_t count, const T& value) : array_(std::make_shared<T[]>(count)), size_(count), capacity_(count) {
    for (size_t i = 0; i != size_; ++i) {
        array_[i] = value;
    }
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> init) : size_(init.size()), capacity_(init.size()) {
    array_ = std::shared_ptr<T[]>(new T[init.size()]);

    size_t i = 0;
    for (const T &fig : init) {
    array_[i] = fig;
    ++i;
    }
}

template<class T>
Vector<T>::Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_), array_(std::make_shared<T[]>(capacity_)) {
    std::copy(other.array_.get(), other.array_.get() + size_, array_.get());
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept : array_(std::move(other.array_)), size_(other.size_), capacity_(other.capacity_) {
    other.size_ = 0;
    other.capacity_ = 0;
    other.array_.reset();
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        Vector temp(other);
        swap(temp);
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        Clear();
        array_ = std::move(other.array_);
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template <typename T>
T& Vector<T>::operator[](size_t pos) {
    if (pos >= size_) {
        throw exceptions::InvalidIndex("Invalid index");
    }
    return array_[pos];
}

template <typename T>
const T& Vector<T>::operator[](size_t pos) const {
    if (pos >= size_) {
        throw exceptions::InvalidIndex("Invalid index");
    }
    return array_[pos];
}

template <typename T>
T& Vector<T>::Front() {
    if (size_ == 0) {
        throw exceptions::VectorIsNull("Vector is empty!");
    }
    return array_[0];
}

template <typename T>
T& Vector<T>::Back() {
    if (size_ == 0) {
        throw exceptions::VectorIsNull("Vector is empty!");
    }
    return array_[size_ - 1];
}

template <typename T>
T* Vector<T>::Data() noexcept {
    return array_.get();
}

template <typename T>
bool Vector<T>::Empty() const noexcept {
    return size_ == 0;
}

template <typename T>
size_t Vector<T>::Size() const noexcept {
    return size_;
}

template <typename T>
size_t Vector<T>::Capacity() const noexcept {
    return capacity_;
}

template <typename T>
void Vector<T>::Reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
        Reallocate(new_capacity);
    }
}

template <typename T>
void Vector<T>::Reallocate(size_t new_capacity) {
    std::shared_ptr<T[]> new_data = std::shared_ptr<T[]>(new T[new_capacity], std::default_delete<T[]>());
    
    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = std::move(array_[i]);
    }
    
    array_ = std::move(new_data);
    capacity_ = new_capacity;
}

template <typename T>
void Vector<T>::Clear() noexcept {
    for (size_t i = 0; i < size_; ++i) {
        array_[i].~T();
    }
    size_ = 0;
}

template <typename T>
void Vector<T>::DestroyRange(T* first, T* last) noexcept {
    for (; first != last; ++first) {
        first->~T();
    }
}

template <typename T>
void Vector<T>::PushBack(const T& value) {
    if (size_ == capacity_) {
        Reserve(capacity_ == 0 ? DEFAULT_CAPACITY : capacity_ * 2);
    }
    array_[size_++] = value;
}

template <typename T>
void Vector<T>::PushBack(T&& value) {
    if (size_ == capacity_) {
        Reserve(capacity_ == 0 ? DEFAULT_CAPACITY : capacity_ * 2);
    }
    array_[size_++] = std::move(value);
}

template <typename T>
void Vector<T>::PopBack() {
    if (size_ > 0) {
        array_[size_].~T();
    }
    --size_;
}

template <typename T>
void Vector<T>::Insert(size_t pos, const T& value) {
    if (pos > size_) {
        throw exceptions::InvalidIndex("Invalid index for insert");
    }
    
    if (size_ == capacity_) {
        Reserve(capacity_ == 0 ? DEFAULT_CAPACITY : capacity_ * 2);
    }
    
    for (size_t i = size_; i > pos; --i) {
        array_[i] = std::move(array_[i - 1]);
    }
    
    array_[pos] = value;
    ++size_;
}

template <typename T>
void Vector<T>::Erase(size_t pos) {
    if (pos >= size_) {
        throw exceptions::InvalidIndex("Invalid index for erase");
    }
    
    array_[pos].~T();
    
    for (size_t i = pos; i < size_ - 1; ++i) {
        array_[i] = std::move(array_[i + 1]);
    }
    
    --size_;
}

template <typename T>
void Vector<T>::Erase(size_t first, size_t last) {
    if (first >= last || last > size_) {
        throw exceptions::InvalidIndex("Invalid range for erase");
    }
    
    DestroyRange(array_.get() + first, array_.get() + last);
    
    size_t shift = last - first;
    for (size_t i = first; i < size_ - shift; ++i) {
        array_[i] = std::move(array_[i + shift]);
    }
    
    size_ -= shift;
}

template <typename T>
void Vector<T>::Resize(size_t count) {
    if (count > capacity_) {
        Reserve(count);
    }
    
    if (count > size_) {
        for (size_t i = size_; i < count; ++i) {
            new (&array_[i]) T();
        }
    } else {
        DestroyRange(array_.get() + count, array_.get() + size_);
    }
    
    size_ = count;
}

template <typename T>
void Vector<T>::Resize(size_t count, const T& value) {
    if (count > capacity_) {
        Reserve(count);
    }
    
    if (count > size_) {
        for (size_t i = size_; i < count; ++i) {
            new (&array_[i]) T(value);
        }
    } else {
        DestroyRange(array_.get() + count, array_.get() + size_);
    }
    
    size_ = count;
}

template <typename T>
template <typename U>
U Vector<T>::TotalAreas() const {
    U total = 0.0;
    for (size_t i = 0; i < size_; ++i) {
        total += array_[i]->Area();
    }
    return total;
}

template <typename T>
void Vector<T>::PrintCenters() const {
    for (size_t i = 0; i < size_; ++i) {
        std::cout << "Figure " << (i + 1) << " center: " << array_[i]->Center() << std::endl;
    }
}

template <typename T>
void Vector<T>::PrintAreas() const {
    for (size_t i = 0; i < size_; ++i) {
        std::cout << "Figure " << (i + 1) << " area: " << array_[i]->Area() << std::endl;
    }
}

template <typename T>
void Vector<T>::swap(Vector& other) noexcept {
    std::swap(array_, other.array_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

template <typename T>
Vector<T>::~Vector() {
    Clear();
}

template <typename T>
void swap(Vector<T>& left, Vector<T>& right) noexcept {
    left.swap(right);
}

}