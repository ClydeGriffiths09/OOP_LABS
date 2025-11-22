#pragma once

#include <memory_resource>
#include <vector>
#include <cstddef>

class DynamicMemoryResource : public std::pmr::memory_resource {
private:
    struct Block {
        void* ptr;
        std::size_t size;
        std::size_t alignment;
    };

    std::vector<Block> allocated_;
    std::vector<Block> free_;

    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

public:
    DynamicMemoryResource() = default;
    ~DynamicMemoryResource() override;

    DynamicMemoryResource(const DynamicMemoryResource&) = delete;
    DynamicMemoryResource& operator=(const DynamicMemoryResource&) = delete;
    DynamicMemoryResource(DynamicMemoryResource&&) = delete;
    DynamicMemoryResource& operator=(DynamicMemoryResource&&) = delete;

    std::size_t get_allocated_blocks_count() const;
    std::size_t get_free_blocks_count() const;
    std::size_t get_total_blocks() const;
};