// Подключаем заголовочные файлы
#include "triangle.h"    // Для работы с классом Triangle
#include <cmath>        // Для математических функций

// Метод вычисления геометрического центра треугольника
template <Scalar T>
Point<T> Triangle<T>::getGeometricCenter() const {
    T sumX = 0, sumY = 0;
    // Суммируем координаты всех вершин
    for (const auto& vertex : this->vertices) {
        sumX += vertex->x;  // Суммируем x-координаты
        sumY += vertex->y;  // Суммируем y-координаты
    }
    // Возвращаем точку - центр тяжести (среднее арифметическое координат)
    return Point<T>(sumX / 3, sumY / 3);
}

// Метод вычисления площади треугольника по формуле Герона
template <Scalar T>
double Triangle<T>::getArea() const {
    // Вычисляем длины сторон треугольника по координатам вершин
    // Длина стороны a (между вершинами 0 и 1)
    T a = std::sqrt(std::pow(this->vertices[1]->x - this->vertices[0]->x, 2) + 
                    std::pow(this->vertices[1]->y - this->vertices[0]->y, 2));
    // Длина стороны b (между вершинами 1 и 2)
    T b = std::sqrt(std::pow(this->vertices[2]->x - this->vertices[1]->x, 2) + 
                    std::pow(this->vertices[2]->y - this->vertices[1]->y, 2));
    // Длина стороны c (между вершинами 2 и 0)
    T c = std::sqrt(std::pow(this->vertices[0]->x - this->vertices[2]->x, 2) + 
                    std::pow(this->vertices[0]->y - this->vertices[2]->y, 2));
    
    // Вычисляем полупериметр
    T s = (a + b + c) / 2;
    
    // Возвращаем площадь по формуле Герона
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

// Явная инстанциация шаблона для разных числовых типов
template class Triangle<int>;      // Для целочисленных координат
template class Triangle<float>;    // Для координат с плавающей точкой
template class Triangle<double>;   // Для координат с двойной точностью