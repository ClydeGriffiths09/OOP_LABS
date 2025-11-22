#include <new>
#include <iostream>

#include "memory_resource.hpp"

void* DynamicMemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    if (bytes == 0) {
        return nullptr;
    }

    for (auto it = free_.begin(); it != free_.end(); ++it) {
        if (it->size >= bytes) {
            Block b = *it;
            free_.erase(it);
            allocated_.push_back(b);
            return b.ptr;
        }
    }

    try {
        void* ptr = ::operator new(bytes, std::align_val_t(alignment));
        allocated_.push_back({ptr, bytes, alignment});
        std::cout << "Allocated " << bytes << std::endl;
        std::cout << "Total blocks: " << get_total_blocks() << std::endl;
        return ptr;
    } catch (const std::bad_alloc&) {
        throw std::bad_alloc();
    }
}

void DynamicMemoryResource::do_deallocate(void* p, std::size_t bytes, std::size_t alignment) {
    if (p == nullptr) {
        return;
    }

    for (auto it = allocated_.begin(); it != allocated_.end(); ++it) {
        if (it->ptr == p) {
            free_.push_back(*it);
            allocated_.erase(it);
            return;
        }
    }

    throw std::runtime_error("Attempt to deallocate unallocated memory");
}

bool DynamicMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}

DynamicMemoryResource::~DynamicMemoryResource() {
    std::size_t total_bytes = 0;

    auto deallocate_all = [&total_bytes](std::vector<Block>& list) {
        for (auto& block : list) {
            ::operator delete(block.ptr, block.size, std::align_val_t(block.alignment));
            total_bytes += block.size;
        }
        list.clear();
    };

    deallocate_all(allocated_);
    deallocate_all(free_);

    std::cout << "DynamicMemoryResource destroyed. Total memory cleaned: "<< total_bytes << " bytes.\n";
}

std::size_t DynamicMemoryResource::get_allocated_blocks_count() const { 
    return allocated_.size(); 
}

std::size_t DynamicMemoryResource::get_free_blocks_count() const { 
    return free_.size(); 
}

std::size_t DynamicMemoryResource::get_total_blocks() const { 
    return allocated_.size() + free_.size(); 
}