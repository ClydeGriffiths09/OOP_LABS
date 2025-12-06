#pragma once

#include <initializer_list>
#include <utility>
#include <cstdlib>

namespace vector {

class Vector {
public:
    Vector();

    Vector(size_t count, unsigned char value);

    Vector(const Vector& other);

    Vector(Vector&& other) noexcept;

    Vector(std::initializer_list<unsigned char> init);

    Vector& Copy(const Vector& other);

    unsigned char& Get(size_t pos);

    unsigned char Get(size_t pos) const;

    size_t Size() const noexcept;

    size_t Capacity() const noexcept;

    unsigned char& operator[](size_t pos);

    const unsigned char& operator[](size_t pos) const;

    unsigned char& Front() const noexcept;

    unsigned char& Back() const noexcept;

    unsigned char* Data() const noexcept;

    bool IsEmpty() const noexcept;

    void Reserve(size_t new_cap);

    void Clear() noexcept;

    void Insert(size_t pos, unsigned char value);

    void Erase(size_t begin_pos, size_t end_pos);

    void PushBack(unsigned char value);

    void PopBack();

    void Resize(size_t count, unsigned char value);

    ~Vector();

private:
    size_t size_;
    size_t capacity_;
    unsigned char* array_;
    const int8_t DEFAULT_ALLOCATE = 10;

    void Swap(Vector& v) {
        std::swap(v.array_, array_);
        std::swap(v.size_, size_);
        std::swap(v.capacity_, capacity_);
    }

    void ClearElement(unsigned char* element) {
        free(element);
    }
};
}
