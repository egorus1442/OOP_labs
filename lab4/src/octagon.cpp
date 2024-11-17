#include "octagon.h"
#include <cmath>

// Метод вычисления геометрического центра восьмиугольника
template <Scalar T>
Point<T> Octagon<T>::getGeometricCenter() const {
    T sumX = 0, sumY = 0;
    // Суммируем координаты всех вершин
    for (const auto& vertex : this->vertices) {
        sumX += vertex->x;  // Суммируем x-координаты
        sumY += vertex->y;  // Суммируем y-координаты
    }
    // Возвращаем точку - центр восьмиугольника (среднее арифметическое координат)
    return Point<T>(sumX / 8, sumY / 8);
}

// Метод вычисления площади правильного восьмиугольника
template <Scalar T>
double Octagon<T>::getArea() const {
    // Вычисляем длину стороны как расстояние между первыми двумя вершинами
    T side = std::sqrt(std::pow(this->vertices[1]->x - this->vertices[0]->x, 2) + 
                      std::pow(this->vertices[1]->y - this->vertices[0]->y, 2));
    // Формула площади правильного восьмиугольника: 2a²(1 + √2), где a - длина стороны
    return 2 * std::pow(side, 2) * (1 + std::sqrt(2));
}

// Явная инстанциация шаблона для разных числовых типов
template class Octagon<int>;      // Для целочисленных координат
template class Octagon<float>;    // Для координат с плавающей точкой
template class Octagon<double>;   // Для координат с двойной точностью