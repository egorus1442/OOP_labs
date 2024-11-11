#include <iostream>
#include <vector>
#include <stdexcept>
#include <initializer_list>
#include <string>

class Thirteen {
public:
    // Конструкторы
    Thirteen();  // Конструктор по умолчанию
    Thirteen(const std::initializer_list<unsigned char>& digits);  // Конструктор от списка инициализации
    Thirteen(const std::string& str);  // Конструктор от строки
    Thirteen(const Thirteen& other);  // Конструктор копирования
    Thirteen(Thirteen&& other) noexcept;  // Конструктор перемещения

    // Деструктор
    ~Thirteen() noexcept;

    // Операции присваивания
    Thirteen& operator=(const Thirteen& other);  // Присваивание копированием
    Thirteen& operator=(Thirteen&& other) noexcept;  // Присваивание перемещением

    // Арифметические операции
    Thirteen operator+(const Thirteen& other) const;  // Сложение
    Thirteen operator-(const Thirteen& other) const;  // Вычитание

    // Арифметические операции с присваиванием
    Thirteen& operator+=(const Thirteen& other);  // Сложение с присваиванием
    Thirteen& operator-=(const Thirteen& other);  // Вычитание с присваиванием

    // Операции сравнения
    bool operator==(const Thirteen& other) const;  // Равно
    bool operator!=(const Thirteen& other) const;  // Не равно
    bool operator<(const Thirteen& other) const;   // Меньше
    bool operator>(const Thirteen& other) const;   // Больше
    bool operator<=(const Thirteen& other) const;  // Меньше или равно
    bool operator>=(const Thirteen& other) const;  // Больше или равно

    // Вспомогательные методы
    std::string toString() const;

private:
    std::vector<unsigned char> digits;  // Вектор для хранения тринадцатиричных цифр

    // Вспомогательные функции для работы с арифметикой
    void trim();  // Удаляет ведущие нули
};
