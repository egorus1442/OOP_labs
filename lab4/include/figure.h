#pragma once
#include "point.h"
#include <memory>
#include <vector>

// Абстрактный базовый класс для геометрических фигур
template <Scalar T>
class Figure {
protected:
    // Вектор вершин фигуры
    std::vector<std::unique_ptr<Point<T>>> vertices;

public:
    // Конструкторы и операторы для правила пяти
    Figure() = default;
    virtual ~Figure() = default;
    Figure(const Figure& other);
    Figure(Figure&& other) noexcept;
    Figure& operator=(const Figure& other);
    Figure& operator=(Figure&& other) noexcept;

    // Чисто виртуальные методы для работы с фигурой
    virtual Point<T> getGeometricCenter() const = 0;  // Получение геометрического центра
    virtual double getArea() const = 0;               // Получение площади
    virtual size_t getVerticesCount() const = 0;      // Получение количества вершин

    friend std::ostream& operator<<(std::ostream& os, const Figure& figure) {
        return figure.print(os);
    }

    friend std::istream& operator>>(std::istream& is, Figure& figure) {
        return figure.input(is);
    }

    operator double() const {
        return getArea();
    }

    // Операторы сравнения
    bool operator==(const Figure& other) const;
    bool operator!=(const Figure& other) const;

protected:
    // Защищённые методы для ввода-вывода
    virtual std::ostream& print(std::ostream& os) const;
    virtual std::istream& input(std::istream& is);
}; 