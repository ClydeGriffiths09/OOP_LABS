#include "vector.h"

namespace vector {

Vector::Vector() : size_(0), capacity_(0), array_(nullptr) {}

figure::Figure& Vector::operator[](size_t pos) {
    if (pos > size_) {
        throw exceptions::InvalidIndex("Invalid index");
    }
    return *array_[pos];
}

const figure::Figure& Vector::operator[](size_t pos) const {
    if (pos > size_) {
        throw exceptions::InvalidIndex("Invalid index");
    }
    return *array_[pos];
}

figure::Figure& Vector::Front() const {
    if (size_ == 0) {
        throw exceptions::VectorIsNull("Vector is null!");
    }
    return *array_[0];
}

bool Vector::IsEmpty() const noexcept {
    return size_ == 0;
}

figure::Figure& Vector::Back() const {
    if (size_ == 0) {
        throw exceptions::VectorIsNull("Vector is null!");
    }
    return *array_[size_ - 1];
}

figure::Figure** Vector::Data() const noexcept {
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
    figure::Figure** new_arr = new figure::Figure*[new_cap];

    for (size_t i = 0; i < size_; i++) {
        new_arr[i] = array_[i];
    }

    delete[] array_;
    array_ = new_arr;
    capacity_ = new_cap;
}

void Vector::Clear() noexcept {
    delete[] array_;
    array_ = nullptr;
    size_ = 0;
}

void Vector::Insert(size_t pos, figure::Figure* value) {
    if (capacity_ == size_) {
        Reserve(capacity_ == 0 ? DEFAULT_ALLOCATE : capacity_ * 2);
    }
    for (size_t i = size_ - 1; i > pos; --i) {
        array_[i] = array_[i - 1];
    }
    array_[pos] = value;
    ++size_;
}

void Vector::Erase(size_t begin_pos, size_t end_pos) {
    if (end_pos > size_) {
        return;
    }
    for (size_t i = end_pos; i < size_; ++i) {
        array_[i - (end_pos - begin_pos)] = array_[i];
    }
    for (size_t i = begin_pos; i < end_pos; ++i) {
        PopBack();
    }
}

void Vector::PushBack(figure::Figure* value) {
    if (capacity_ == 0) {
        Reserve(DEFAULT_ALLOCATE);
    } else if (capacity_ == size_) {
        Reserve(2 * size_);
    }
    array_[size_] = value;
    ++size_;
}

void Vector::PopBack() {
    if (size_ == 0) {
        throw exceptions::VectorIsNull("Vector is null!");
    }
    --size_;
}

double Vector::TotalAreas() {
    double res = 0.0;
    for (size_t i = 0; i < size_; ++i) {
        res += array_[i]->Area();
    }
    return res;
}

void Vector::PrintCenters() {
    for (size_t i = 0; i < size_; ++i) {
        std::cout << "Center of the figure  " << i + 1 << ": " << array_[i]->Center() << std::endl;
    }
}

void Vector::PrintAreas() {
    for (size_t i = 0; i < size_; ++i) {
        std::cout << "Area of the figure " << i + 1 << ": " << array_[i]->Area() << std::endl;
    }
}

Vector::~Vector() {
    delete[] array_;
}

void Vector::swap(Vector& other) noexcept {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(array_, other.array_);
}

inline void swap(Vector &left, Vector &right) noexcept { 
    left.swap(right); 
}
}

namespace std {
template <>
inline void swap<vector::Vector>(vector::Vector &left,
                                 vector::Vector &right) noexcept {
  vector::swap(left, right);
}
}