// Подключение всех необходимых заголовочных файлов
#include "array.h"      // Для работы с динамическим массивом
#include "octagon.h"    // Для работы с восьмиугольником
#include "triangle.h"   // Для работы с треугольником
#include "square.h"     // Для работы с квадратом
#include <iostream>     // Для ввода-вывода
#include <memory>       // Для работы с умными указателями

// Шаблонная функция для вывода информации о фигуре
template <Scalar T>
void printFigureInfo(const Figure<T>& figure) {
    std::cout << "Geometric center: " << figure.getGeometricCenter() << std::endl;  // Вывод геометрического центра
    std::cout << "Vertices:\n" << figure << std::endl;  // Вывод вершин
    std::cout << "Area: " << figure.getArea() << std::endl;  // Вывод площади
}

// Шаблонная функция для подсчета общей площади всех фигур
template <Scalar T>
double getTotalArea(const Array<std::shared_ptr<Figure<T>>>& figures) {
    double total_area = 0;
    // Суммируем площади всех фигур
    for (size_t i = 0; i < figures.get_size(); ++i) {
        total_area += figures[i]->getArea();
    }
    return total_area;
}

int main() {
    // Создаем массив указателей на фигуры с типом double
    Array<std::shared_ptr<Figure<double>>> figures;

    // Добавляем по одной фигуре каждого типа
    figures.push_back(std::make_shared<Octagon<double>>());   // Восьмиугольник
    figures.push_back(std::make_shared<Triangle<double>>());  // Треугольник
    figures.push_back(std::make_shared<Square<double>>());    // Квадрат

    // Вводим координаты вершин для каждой фигуры
    for (size_t i = 0; i < figures.get_size(); ++i) {
        std::cin >> *figures[i];
    }

    // Выводим информацию о каждой фигуре
    for (size_t i = 0; i < figures.get_size(); ++i) {
        printFigureInfo(*figures[i]);
    }

    // Выводим общую площадь всех фигур
    std::cout << "Total area: " << getTotalArea(figures) << std::endl;

    // Удаляем фигуру с индексом 1 (треугольник)
    figures.remove(1);

    // Выводим обновленную информацию после удаления
    std::cout << "After removing figure at index 1:" << std::endl;
    for (size_t i = 0; i < figures.get_size(); ++i) {
        printFigureInfo(*figures[i]);
    }

    // Демонстрация работы с массивом квадратов
    Array<Square<int>> squares;
    squares.push_back(Square<int>());  // Добавляем квадрат
    std::cin >> squares[0];  // Вводим его координаты
    std::cout << "Square info:" << std::endl;
    printFigureInfo(squares[0]);  // Выводим информацию о квадрате

    // Выводим площади оставшихся фигур по отдельности
    std::cout << "Individual areas:" << std::endl;
    for (size_t i = 0; i < figures.get_size(); ++i) {
        std::cout << "Figure " << i << " area: " << figures[i]->getArea() << std::endl;
    }

    return 0;
}