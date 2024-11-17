#include "dynamic_memory_resource.h"
#include <algorithm>

// Реализация метода выделения памяти
void* DynamicMemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    // Поиск подходящего свободного блока
    auto it = std::find_if(allocated_blocks_.begin(), allocated_blocks_.end(),
        [bytes](const MemoryBlock& block) {
            return !block.in_use && block.size >= bytes;
        });
    
    // Если найден подходящий блок, используем его
    if (it != allocated_blocks_.end()) {
        it->in_use = true;
        return it->ptr;
    }
    
    // Если подходящий блок не найден, выделяем новый
    void* ptr = ::operator new(bytes, std::align_val_t{alignment});
    allocated_blocks_.push_back({ptr, bytes, true});
    return ptr;
}

// Реализация метода освобождения памяти
void DynamicMemoryResource::do_deallocate(void* p, std::size_t bytes, std::size_t) {
    // Поиск блока по указателю
    auto it = std::find_if(allocated_blocks_.begin(), allocated_blocks_.end(),
        [p](const MemoryBlock& block) {
            return block.ptr == p;
        });
    
    // Помечаем блок как свободный
    if (it != allocated_blocks_.end()) {
        it->in_use = false;
    }
}

// Реализация метода сравнения ресурсов памяти
bool DynamicMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}

// Реализация деструктора
DynamicMemoryResource::~DynamicMemoryResource() {
    // Освобождение всех выделенных блоков памяти
    for (const auto& block : allocated_blocks_) {
        ::operator delete(block.ptr);
    }
} 