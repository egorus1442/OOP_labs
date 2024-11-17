#ifndef TEST_STRUCTS_H
#define TEST_STRUCTS_H

// Тестовая структура для проверки работы динамического массива
struct TestStruct {
    int x;          // Целочисленное поле
    double y;       // Поле с плавающей точкой
    
    // Конструктор с параметрами по умолчанию
    TestStruct(int x = 0, double y = 0.0) : x(x), y(y) {}
    
    // Оператор сравнения для тестирования
    bool operator==(const TestStruct& other) const {
        return x == other.x && y == other.y;
    }
};

#endif 