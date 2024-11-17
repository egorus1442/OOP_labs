#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <memory_resource>
#include "dynamic_memory_resource.h"

template<typename T>
class DynamicArray {
private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;
    std::pmr::polymorphic_allocator<T> allocator_;

public:
    // Определение внутреннего класса итератора
    class Iterator {
    private:
        T* ptr_;
    
    public:
        // Определение типов для совместимости со стандартной библиотекой
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit Iterator(T* ptr) : ptr_(ptr) {}
        
        // Операторы для работы с итератором
        Iterator& operator++() { ++ptr_; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++ptr_; return tmp; }
        
        reference operator*() const { return *ptr_; }
        pointer operator->() const { return ptr_; }
        
        // Операторы сравнения
        bool operator==(const Iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const Iterator& other) const { return ptr_ != other.ptr_; }
    };

    // Публичные методы класса DynamicArray
    explicit DynamicArray(std::pmr::memory_resource* resource = nullptr);
    ~DynamicArray();
    
    void push_back(const T& value);
    void pop_back();
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;
    std::size_t size() const;
    
    // Методы для поддержки range-based for
    Iterator begin() { return Iterator(data_); }
    Iterator end() { return Iterator(data_ + size_); }
};

#endif 