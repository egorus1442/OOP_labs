#include "dynamic_array.h"
#include "dynamic_memory_resource.h"
#include <iostream>

struct Complex {
    int x;
    double y;
    std::string str;
    
    Complex(int x = 0, double y = 0.0, std::string str = "")
        : x(x), y(y), str(str) {}
};

int main() {
    // Создаем наш memory resource
    DynamicMemoryResource memory_resource;
    
    // Тест с простым типом (int)
    {
        DynamicArray<int> array(&memory_resource);
        
        // Добавляем элементы
        for (int i = 0; i < 5; ++i) {
            array.push_back(i);
        }
        
        // Используем итератор для вывода
        std::cout << "Целые числа: ";
        for (const auto& item : array) {
            std::cout << item << " ";
        }
        std::cout << "\n";
    }
    
    // Тест со сложным типом (Complex)
    {
        DynamicArray<Complex> array(&memory_resource);
        
        array.push_back(Complex(1, 1.1, "one"));
        array.push_back(Complex(2, 2.2, "two"));
        array.push_back(Complex(3, 3.3, "three"));
        
        std::cout << "Сложные объекты:\n";
        for (const auto& item : array) {
            std::cout << "x: " << item.x << ", y: " << item.y 
                      << ", str: " << item.str << "\n";
        }
    }
    
    return 0;
} 