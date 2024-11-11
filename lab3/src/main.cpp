#include <iostream>
#include <vector>
#include <memory>
#include "figure.h"
#include "triangle.h"
#include "square.h"
#include "octagon.h"

int main() {
    std::vector<std::unique_ptr<Figure>> figures;
    
    while (true) {
        std::cout << "\nМеню:\n";
        std::cout << "1. Добавить треугольник\n";
        std::cout << "2. Добавить квадрат\n";
        std::cout << "3. Добавить восьмиугольник\n";
        std::cout << "4. Вывести все фигуры\n";
        std::cout << "5. Удалить фигуру по индексу\n";
        std::cout << "6. Показать общую площадь\n";
        std::cout << "0. Выход\n";
        
        int choice;
        std::cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: {
                auto triangle = std::make_unique<Triangle>();
                std::cout << "Введите координаты 3 вершин (x y):\n";
                std::cin >> *triangle;
                figures.push_back(std::move(triangle));
                break;
            }
            case 2: {
                auto square = std::make_unique<Square>();
                std::cout << "Введите координаты 4 вершин (x y):\n";
                std::cin >> *square;
                figures.push_back(std::move(square));
                break;
            }
            case 3: {
                auto octagon = std::make_unique<Octagon>();
                std::cout << "Введите координаты 8 вершин (x y):\n";
                std::cin >> *octagon;
                figures.push_back(std::move(octagon));
                break;
            }
            case 4: {
                for (size_t i = 0; i < figures.size(); ++i) {
                    std::cout << "\nФигура " << i + 1 << ":\n";
                    std::cout << *figures[i];
                    auto center = figures[i]->getCenter();
                    std::cout << "Центр: (" << center.x << ", " << center.y << ")\n";
                    std::cout << "Площадь: " << static_cast<double>(*figures[i]) << "\n";
                }
                break;
            }
            case 5: {
                size_t index;
                std::cout << "Введите индекс фигуры для удаления: ";
                std::cin >> index;
                if (index < figures.size()) {
                    figures.erase(figures.begin() + index);
                    std::cout << "Фигура удалена\n";
                } else {
                    std::cout << "Неверный индекс\n";
                }
                break;
            }
            case 6: {
                double totalArea = 0;
                for (const auto& figure : figures) {
                    totalArea += static_cast<double>(*figure);
                }
                std::cout << "Общая площадь: " << totalArea << "\n";
                break;
            }
            default:
                std::cout << "Неверный выбор\n";
        }
    }
    
    return 0;
}
