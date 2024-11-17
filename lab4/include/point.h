#pragma once
#include <iostream>
#include <type_traits>

// Концепт для проверки, является ли тип числовым (целым или с плавающей точкой)
template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

// Шаблонный класс для представления точки на плоскости
template <Scalar T>
class Point {
public:
    T x, y;  // Координаты точки

    // Конструктор с параметрами по умолчанию
    Point(T x = 0, T y = 0) : x(x), y(y) {}

    // Оператор вывода точки в поток
    // Формат вывода: (x, y)
    friend std::ostream& operator<<(std::ostream& os, const Point<T>& point) {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    }

    // Оператор ввода точки из потока
    // Ожидаемый формат ввода: x y
    friend std::istream& operator>>(std::istream& is, Point<T>& point) {
        is >> point.x >> point.y;
        return is;
    }
};