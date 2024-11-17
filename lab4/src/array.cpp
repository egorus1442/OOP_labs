// Подключение необходимых заголовочных файлов
#include "array.h"      // Заголовочный файл с объявлением класса Array
#include "figure.h"     // Заголовочный файл с базовым классом Figure
#include "octagon.h"    // Заголовочный файл для класса Octagon
#include "triangle.h"   // Заголовочный файл для класса Triangle
#include "square.h"     // Заголовочный файл для класса Square

// Объявление шаблонного класса
template <class T>
// Конструктор с параметром начального размера
Array<T>::Array(size_t initial_size) : size(initial_size), capacity(initial_size) {
    // Если требуется выделить память (capacity > 0)
    if (capacity > 0) {
        // Создаем динамический массив с помощью умного указателя
        data = std::make_unique<T[]>(capacity);
    }
}

// Конструктор копирования
template <class T>
Array<T>::Array(const Array& other) : size(other.size), capacity(other.capacity) {
    // Если есть что копировать
    if (capacity > 0) {
        // Выделяем новую память
        data = std::make_unique<T[]>(capacity);
        // Копируем все элементы
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
}

// Конструктор перемещения
template <class T>
Array<T>::Array(Array&& other) noexcept
    : data(std::move(other.data)), size(other.size), capacity(other.capacity) {
    // Обнуляем размеры в исходном объекте
    other.size = 0;
    other.capacity = 0;
}

// Оператор присваивания копированием
template <class T>
Array<T>& Array<T>::operator=(const Array& other) {
    // Проверка на самоприсваивание
    if (this != &other) {
        if (other.capacity > 0) {
            // Создаем новый массив
            auto new_data = std::make_unique<T[]>(other.capacity);
            // Копируем элементы
            for (size_t i = 0; i < other.size; ++i) {
                new_data[i] = other.data[i];
            }
            // Перемещаем указатель
            data = std::move(new_data);
        } else {
            // Если другой массив пустой, освобождаем память
            data.reset();
        }
        // Копируем размеры
        size = other.size;
        capacity = other.capacity;
    }
    return *this;
}

// Оператор присваивания перемещением
template <class T>
Array<T>& Array<T>::operator=(Array&& other) noexcept {
    // Проверка на самоприсваивание
    if (this != &other) {
        // Перемещаем данные
        data = std::move(other.data);
        size = other.size;
        capacity = other.capacity;
        // Обнуляем размеры в исходном объекте
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}

// Метод добавления элемента в конец массива
template <class T>
void Array<T>::push_back(const T& value) {
    // Если нужно увеличить емкость
    if (size == capacity) {
        // Вычисляем новую емкость
        size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
        // Изменяем размер массива
        resize(new_capacity);
    }
    // Добавляем элемент и увеличиваем размер
    data[size++] = value;
}

// Метод удаления элемента по индексу
template <class T>
void Array<T>::remove(size_t index) {
    // Проверка корректности индекса
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    // Сдвигаем элементы влево
    for (size_t i = index; i < size - 1; ++i) {
        data[i] = std::move(data[i + 1]);
    }
    // Уменьшаем размер
    --size;
}

// Оператор доступа к элементу по индексу
template <class T>
T& Array<T>::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Константный оператор доступа к элементу
template <class T>
const T& Array<T>::operator[](size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Метод изменения размера массива
template <class T>
void Array<T>::resize(size_t new_capacity) {
    // Создаем новый массив
    auto new_data = std::make_unique<T[]>(new_capacity);
    // Перемещаем существующие элементы
    for (size_t i = 0; i < size; ++i) {
        new_data[i] = std::move(data[i]);
    }
    // Обновляем указатель и емкость
    data = std::move(new_data);
    capacity = new_capacity;
}

// Явная инстанциация шаблонов для различных типов
template class Array<std::shared_ptr<Figure<int>>>;    // Для целочисленных фигур
template class Array<std::shared_ptr<Figure<float>>>;  // Для фигур с плавающей точкой
template class Array<std::shared_ptr<Figure<double>>>; // Для фигур с двойной точностью
template class Array<Octagon<int>>;                    // Для восьмиугольников
template class Array<Triangle<int>>;                   // Для треугольников
template class Array<Square<int>>;                     // Для квадратов
template class Array<int>;                             // Для целых чисел