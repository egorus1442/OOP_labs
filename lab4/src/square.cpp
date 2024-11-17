// Подключаем заголовочные файлы
#include "square.h"     // Для работы с классом Square
#include <cmath>        // Для математических функций

// Метод вычисления геометрического центра квадрата
template <Scalar T>
Point<T> Square<T>::getGeometricCenter() const {
    T sumX = 0, sumY = 0;
    // Суммируем координаты всех вершин
    for (const auto& vertex : this->vertices) {
        sumX += vertex->x;  // Суммируем x-координаты
        sumY += vertex->y;  // Суммируем y-координаты
    }
    // Возвращаем точку - центр квадрата (среднее арифметическое координат)
    return Point<T>(sumX / 4, sumY / 4);
}

// Метод вычисления площади квадрата
template <Scalar T>
double Square<T>::getArea() const {
    // Вычисляем длину стороны квадрата как расстояние между первыми двумя вершинами
    T side = std::sqrt(std::pow(this->vertices[1]->x - this->vertices[0]->x, 2) + 
                      std::pow(this->vertices[1]->y - this->vertices[0]->y, 2));
    // Возвращаем площадь (квадрат стороны)
    return side * side;
}

// Явная инстанциация шаблона для разных числовых типов
template class Square<int>;      // Для целочисленных координат
template class Square<float>;    // Для координат с плавающей точкой
template class Square<double>;   // Для координат с двойной точностью