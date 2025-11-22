#include <algorithm>
#include <iostream>

template <typename T>
bool Vector<T>::VectorIterator::operator==(const VectorIterator& other) const {
    return current_ == other.current_;
}

template <typename T>
bool Vector<T>::VectorIterator::operator!=(const VectorIterator& other) const {
    return current_ != other.current_;
}

template <typename T>
typename Vector<T>::VectorIterator::reference 
Vector<T>::VectorIterator::operator*() const {
    return *current_;
}

template <typename T>
typename Vector<T>::VectorIterator::pointer 
Vector<T>::VectorIterator::operator->() const {
    return current_;
}

template <typename T>
typename Vector<T>::VectorIterator& 
Vector<T>::VectorIterator::operator++() {
    ++current_;
    return *this;
}

template <typename T>
typename Vector<T>::VectorIterator 
Vector<T>::VectorIterator::operator++(int) {
    VectorIterator tmp = *this;
    ++current_;
    return tmp;
}


template <typename T>
Vector<T>::Vector(std::pmr::memory_resource* res) 
    : alloc_(res), data_(nullptr), size_(0), capacity_(0) {}

template <typename T>
Vector<T>::Vector(size_t size, std::pmr::memory_resource* res)
    : alloc_(res), data_(nullptr), size_(0), capacity_(0) {
    Resize(size);
}

template <typename T>
Vector<T>::Vector(size_t size, const T& value, std::pmr::memory_resource* res)
    : alloc_(res), data_(nullptr), size_(0), capacity_(0) {
    Reserve(size);
    for (size_t i = 0; i < size; ++i) {
        PushBack(value);
    }
}

template <typename T>
Vector<T>::Vector(const std::initializer_list<T>& values, std::pmr::memory_resource* res)
    : alloc_(res), data_(nullptr), size_(0), capacity_(0) {
    Reserve(values.size());
    for (const auto& value : values) {
        PushBack(value);
    }
}

template <typename T>
Vector<T>::Vector(const Vector& other)
    : alloc_(other.alloc_), data_(nullptr), size_(0), capacity_(0) {
    Reserve(other.capacity_);
    for (size_t i = 0; i < other.size_; ++i) {
        PushBack(other.data_[i]);
    }
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept
    : alloc_(std::move(other.alloc_)), data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

template <typename T>
Vector<T>::~Vector() {
    Clear();
    if (data_) {
        alloc_.deallocate(data_, capacity_);
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        
        Vector temp(other);
        
        std::swap(data_, temp.data_);
        std::swap(size_, temp.size_);
        std::swap(capacity_, temp.capacity_);
        
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        Clear();
        if (data_) {
            alloc_.deallocate(data_, capacity_);
        }
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}


template <typename T>
typename Vector<T>::VectorIterator Vector<T>::Begin() noexcept {
    return VectorIterator(data_);
}

template <typename T>
typename Vector<T>::VectorIterator Vector<T>::End() noexcept {
    return VectorIterator(data_ + size_);
}

template <typename T>
typename Vector<T>::VectorIterator Vector<T>::Begin() const noexcept {
    return VectorIterator(const_cast<T*>(data_));
}

template <typename T>
typename Vector<T>::VectorIterator Vector<T>::End() const noexcept {
    return VectorIterator(const_cast<T*>(data_ + size_));
}


template <typename T>
T& Vector<T>::operator[](size_t index) {
    return data_[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const {
    return data_[index];
}

template <typename T>
T& Vector<T>::At(size_t index) {
    if (index >= size_) {
        throw exceptions::InvalidIndex("Wrong Index");
    }
    return data_[index];
}

template <typename T>
const T& Vector<T>::At(size_t index) const {
    if (index >= size_) {
        throw exceptions::InvalidIndex("Wrong Index");
    }
    return data_[index];
}

template <typename T>
T& Vector<T>::Front() {
    if (size_ == 0) {
        throw exceptions::VectorIsNull("Vector is empty!");
    }
    return data_[0];
}

template <typename T>
const T& Vector<T>::Front() const {
    if (size_ == 0) {
        throw exceptions::VectorIsNull("Vector is empty!");
    }
    return data_[0];
}

template <typename T>
T& Vector<T>::Back() {
    if (size_ == 0) {
        throw exceptions::VectorIsNull("Vector is empty!");
    }
    return data_[size_ - 1];
}

template <typename T>
const T& Vector<T>::Back() const {
    if (size_ == 0) {
        throw exceptions::VectorIsNull("Vector is empty!");
    }
    return data_[size_ - 1];
}


template <typename T>
bool Vector<T>::IsEmpty() const noexcept {
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
void Vector<T>::PushBack(const T& value) {
    if (size_ >= capacity_) {
        Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    std::allocator_traits<std::pmr::polymorphic_allocator<T>>::construct(alloc_, data_ + size_, value);
    ++size_;
}

template <typename T>
void Vector<T>::PushBack(T&& value) {
    if (size_ >= capacity_) {
        Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    std::allocator_traits<std::pmr::polymorphic_allocator<T>>::construct(alloc_, data_ + size_, std::move(value));
    ++size_;
}

template <typename T>
void Vector<T>::PopBack() {
    if (size_ == 0) {
        throw exceptions::VectorIsNull("Vector is empty!");
    }
    --size_;
    std::allocator_traits<std::pmr::polymorphic_allocator<T>>::destroy(alloc_, data_ + size_);
}

template <typename T>
void Vector<T>::Clear() noexcept {
    for (size_t i = 0; i < size_; ++i) {
        std::allocator_traits<std::pmr::polymorphic_allocator<T>>::destroy(alloc_, data_ + i);
    }
    size_ = 0;
}

template <typename T>
void Vector<T>::Resize(size_t new_size) {
    if (new_size > capacity_) {
        Reserve(new_size);
    }
    
    if (new_size > size_) {
        
        for (size_t i = size_; i < new_size; ++i) {
            std::allocator_traits<std::pmr::polymorphic_allocator<T>>::construct(alloc_, data_ + i);
        }
    } else if (new_size < size_) {
        
        for (size_t i = new_size; i < size_; ++i) {
            std::allocator_traits<std::pmr::polymorphic_allocator<T>>::destroy(alloc_, data_ + i);
        }
    }
    size_ = new_size;
}

template <typename T>
void Vector<T>::Resize(size_t new_size, const T& value) {
    if (new_size > capacity_) {
        Reserve(new_size);
    }
    
    if (new_size > size_) {
        
        for (size_t i = size_; i < new_size; ++i) {
            std::allocator_traits<std::pmr::polymorphic_allocator<T>>::construct(alloc_, data_ + i, value);
        }
    } else if (new_size < size_) {
        
        for (size_t i = new_size; i < size_; ++i) {
            std::allocator_traits<std::pmr::polymorphic_allocator<T>>::destroy(alloc_, data_ + i);
        }
    }
    size_ = new_size;
}

template <typename T>
void Vector<T>::Reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
        Reallocate(new_capacity);
    }
}


template <typename T>
typename Vector<T>::VectorIterator Vector<T>::Find(const T& value) const {
    for (size_t i = 0; i < size_; ++i) {
        if (data_[i] == value) {
            return VectorIterator(const_cast<T*>(data_ + i));
        }
    }
    return End();
}

template <typename T>
std::pmr::memory_resource* Vector<T>::GetResource() const {
    return alloc_.resource();
}


template <typename T>
void Vector<T>::Reallocate(size_t new_capacity) {
    T* new_data = alloc_.allocate(new_capacity);
    
    for (size_t i = 0; i < size_; ++i) {
        std::allocator_traits<std::pmr::polymorphic_allocator<T>>::construct(alloc_, new_data + i, std::move(data_[i]));
        std::allocator_traits<std::pmr::polymorphic_allocator<T>>::destroy(alloc_, data_ + i);
    }
    
    if (data_) {
        alloc_.deallocate(data_, capacity_);
    }
    
    data_ = new_data;
    capacity_ = new_capacity;
}