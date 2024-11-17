// Защита от повторного включения заголовочного файла
#ifndef DYNAMIC_MEMORY_RESOURCE_H
#define DYNAMIC_MEMORY_RESOURCE_H

// Подключение необходимых заголовочных файлов
#include <memory_resource>
#include <vector>
#include <cstddef>

// Класс для управления динамической памятью
class DynamicMemoryResource : public std::pmr::memory_resource {
private:
    // Структура для хранения информации о блоке памяти
    struct MemoryBlock {
        void* ptr;          // Указатель на блок памяти
        std::size_t size;   // Размер блока
        bool in_use;        // Флаг использования блока
    };
    
    // Вектор для хранения всех выделенных блоков памяти
    std::vector<MemoryBlock> allocated_blocks_;

protected:
    // Переопределенные виртуальные методы базового класса
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;      // Выделение памяти
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override; // Освобождение памяти
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override; // Сравнение ресурсов

public:
    ~DynamicMemoryResource(); // Деструктор для очистки всей выделенной памяти
};

#endif