#pragma once
#include <memory>
#include <stdexcept>

// Шаблонный класс Array для реализации динамического массива
template <class T>
class Array {
private:
    // Умный указатель на массив данных
    std::unique_ptr<T[]> data;
    // Текущий размер массива (количество элементов)
    size_t size;
    // Текущая ёмкость массива (выделенная память)
    size_t capacity;

public:
    // Конструктор с начальным размером (по умолчанию 0)
    Array(size_t initial_size = 0);
    // Виртуальный деструктор по умолчанию
    ~Array() = default;
    // Конструктор копирования
    Array(const Array& other);
    // Конструктор перемещения
    Array(Array&& other) noexcept;
    // Оператор присваивания копированием
    Array& operator=(const Array& other);
    // Оператор присваивания перемещением
    Array& operator=(Array&& other) noexcept;

    // Добавление элемента в конец массива
    void push_back(const T& value);
    // Удаление элемента по индексу
    void remove(size_t index);
    // Оператор доступа к элементу по индексу
    T& operator[](size_t index);
    // Константный оператор доступа к элементу по индексу
    const T& operator[](size_t index) const;
    // Получение текущего размера массива
    size_t get_size() const { return size; }
    // Получение текущей ёмкости массива
    size_t get_capacity() const { return capacity; }

private:
    // Изменение размера массива
    void resize(size_t new_capacity);
}; 