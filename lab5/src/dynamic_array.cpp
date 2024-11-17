// Подключение необходимых заголовочных файлов
#include "dynamic_array.h"
#include "test_structs.h"

// Реализация конструктора
template<typename T>
DynamicArray<T>::DynamicArray(std::pmr::memory_resource* resource)
    : data_(nullptr)        // Инициализация указателя на данные
    , size_(0)             // Начальный размер
    , capacity_(0)         // Начальная ёмкость
    , allocator_(resource) // Инициализация аллокатора
{
}

// Реализация деструктора
template<typename T>
DynamicArray<T>::~DynamicArray() {
    if (data_) {
        // Вызов деструкторов для всех элементов
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }
        // Освобождение памяти
        allocator_.deallocate(data_, capacity_);
    }
}

// Реализация метода push_back
template<typename T>
void DynamicArray<T>::push_back(const T& value) {
    // Проверка необходимости расширения массива
    if (size_ == capacity_) {
        // Вычисление новой ёмкости
        std::size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
        // Выделение новой памяти
        T* new_data = allocator_.allocate(new_capacity);
        
        // Перемещение существующих элементов
        for (std::size_t i = 0; i < size_; ++i) {
            allocator_.construct(&new_data[i], std::move(data_[i]));
            data_[i].~T();
        }
        
        // Освобождение старой памяти
        if (data_) {
            allocator_.deallocate(data_, capacity_);
        }
        
        // Обновление указателей и ёмкости
        data_ = new_data;
        capacity_ = new_capacity;
    }
    
    // Конструирование нового элемента
    allocator_.construct(&data_[size_], value);
    ++size_;
}

// Реализация метода pop_back для удаления последнего элемента массива
template<typename T>
void DynamicArray<T>::pop_back() {
    // Проверяем, что массив не пустой
    if (size_ > 0) {
        // Уменьшаем размер массива на 1
        --size_;
        // Вызываем деструктор для удаляемого элемента
        data_[size_].~T();
    }
}

template<typename T>
T& DynamicArray<T>::operator[](std::size_t index) {
    return data_[index];
}

template<typename T>
const T& DynamicArray<T>::operator[](std::size_t index) const {
    return data_[index];
}

template<typename T>
std::size_t DynamicArray<T>::size() const {
    return size_;
}

// Явная инстанциация шаблонов для используемых типов
struct Complex {
    int x;
    double y;
    std::string str;
    
    Complex(int x = 0, double y = 0.0, std::string str = "")
        : x(x), y(y), str(str) {}
};

template class DynamicArray<int>;
template class DynamicArray<Complex>;
template class DynamicArray<TestStruct>;