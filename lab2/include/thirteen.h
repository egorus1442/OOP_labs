// Защита от повторного включения заголовочного файла
#ifndef THIRTEEN_H
#define THIRTEEN_H

// Подключение необходимых стандартных библиотек
#include <initializer_list>  // для работы со списком инициализации
#include <string>            // для работы со строками

class Thirteen {
private:
    // Приватные поля класса
    unsigned char* digits;  // динамический массив для хранения цифр числа
    size_t size;           // размер числа (количество цифр)

public:
    // Конструкторы:
    Thirteen();  // создает число "0"
    Thirteen(const size_t& n, unsigned char t = 0);  // создает n-значное число из цифры t
    Thirteen(const std::initializer_list<unsigned char>& t);  // создает число из списка цифр
    Thirteen(const std::string& t);  // создает число из строкового представления
    Thirteen(const Thirteen& other);  // создает копию существующего числа
    Thirteen(Thirteen&& other) noexcept;  // перемещает существующее число
    
    // Деструктор для освобождения памяти
    virtual ~Thirteen() noexcept;

    // Операторы присваивания
    Thirteen& operator=(const Thirteen& other);  // копирующее присваивание
    Thirteen& operator=(Thirteen&& other) noexcept;  // перемещающее присваивание

    // Арифметические операции
    Thirteen operator+(const Thirteen& other) const;  // сложение двух чисел
    Thirteen operator-(const Thirteen& other) const;  // вычитание двух чисел
    
    // Операции сравнения
    bool operator<(const Thirteen& other) const;   // меньше
    bool operator>(const Thirteen& other) const;   // больше
    bool operator==(const Thirteen& other) const;  // равно

    // Методы для арифметических операций с присваиванием
    Thirteen& add(const Thirteen& other);      // прибавить к текущему числу
    Thirteen& subtract(const Thirteen& other); // вычесть из текущего числа

private:
    // Вспомогательные методы
    void validate_digit(unsigned char digit) const;  // проверяет, что цифра < 13
    void normalize();  // удаляет ведущие нули
};

#endif