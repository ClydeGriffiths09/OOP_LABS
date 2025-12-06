#include "vector.h"
#include <exceptions.h>

namespace vector {
Vector::Vector() : size_(0), capacity_(0), array_(nullptr) {
}

Vector::Vector(size_t count, unsigned char value) : array_(nullptr), size_(0), capacity_(0) {
    for (size_t i = 0; i < count; ++i) {
        PushBack(value);
    }
}

Vector::Vector(const Vector& other) : array_(nullptr), size_(0), capacity_(0) {
    for (size_t i = 0; i < other.size_; ++i) {
        PushBack(other.array_[i]);
    }
}

Vector::Vector(Vector&& other) noexcept : array_(other.array_), size_(other.size_), capacity_(other.capacity_) {
    other.array_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

Vector::Vector(std::initializer_list<unsigned char> init) : array_(nullptr), size_(0), capacity_(0) {
    for (const auto& x : init) {
        PushBack(x);
    }
}

Vector& Vector::Copy(const Vector& other) {
    if (&other == this) {
        return *this;
    }
    Vector temp = other;
    Swap(temp);
    return *this;
}

unsigned char& Vector::Get(size_t pos) {
    return array_[pos];
}

unsigned char Vector::Get(size_t pos) const {
    return array_[pos];
}

unsigned char& Vector::operator[](size_t pos) {
    return array_[pos];
}

const unsigned char& Vector::operator[](size_t pos) const {
    return array_[pos];
}

unsigned char& Vector::Front() const noexcept {
    return array_[0];
}

bool Vector::IsEmpty() const noexcept {
    return size_ == 0;
}

unsigned char& Vector::Back() const noexcept {
    return array_[size_ - 1];
}

unsigned char* Vector::Data() const noexcept {
    return array_;
}

size_t Vector::Size() const noexcept {
    return size_;
}

size_t Vector::Capacity() const noexcept {
    return capacity_;
}

void Vector::Reserve(size_t new_cap) {
    if (new_cap <= capacity_) {
        return;
    }
    unsigned char* new_arr = reinterpret_cast<unsigned char*>(new int8_t[new_cap]);
    for (size_t i = 0; i < size_; i++) {
        new (new_arr + i) unsigned char(std::move(array_[i]));
    }
    delete[] reinterpret_cast<int8_t*>(array_);
    array_ = new_arr;
    capacity_ = new_cap;
}

void Vector::Clear() noexcept {
    delete[] reinterpret_cast<int8_t*>(array_);
    array_ = nullptr;
    size_ = 0;
}

void Vector::Insert(size_t pos, unsigned char value) {
    if (pos > size_) {
        throw exceptions::VectorIsEmptyException("Invalid index");
    }
    if (size_ >= capacity_) {
        Reserve(capacity_ == 0 ? DEFAULT_ALLOCATE : capacity_ * 2);
    }

    for (size_t i = size_; i > pos; --i) {
        array_[i] = std::move(array_[i - 1]);
    }
    new (array_ + pos) unsigned char(std::move(value));
    ++size_;
}

void Vector::Erase(size_t begin_pos, size_t end_pos) {
    if (begin_pos >= end_pos || end_pos > size_) {
        return;
    }
    for (size_t i = end_pos; i < size_; ++i) {
        new (array_ + begin_pos + i - end_pos) unsigned char(std::move(array_[i]));
    }
    size_ -= (end_pos - begin_pos);
}

void Vector::PushBack(unsigned char value) {
    if (size_ >= capacity_) {
        Reserve(capacity_ == 0 ? DEFAULT_ALLOCATE : capacity_ * 2);
    }
    new (array_ + size_++) unsigned char(std::move(value));
}

void Vector::PopBack() {
    --size_;
}

void Vector::Resize(size_t count, unsigned char value) {
    if (count > capacity_) {
        Reserve(count);
    }

    if (count > size_) {
        for (size_t i = size_; i < count; ++i) {
            new (array_ + i) unsigned char(value);
        }
    } else {
        for (size_t i = count; i < size_; ++i) {
            ClearElement(array_ + i);
        }
    }
    size_ = count;
}

Vector::~Vector() {
    delete[] reinterpret_cast<int8_t*>(array_);
}
}