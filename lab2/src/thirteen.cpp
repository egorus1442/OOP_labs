#include "thirteen.h"
#include <stdexcept>
#include <algorithm>

// Конструкторы
// Конструктор по умолчанию - создает число "0"
Thirteen::Thirteen() : size(1) {
    digits = new unsigned char[1];  // выделяем память под одну цифру
    digits[0] = 0;                  // устанавливаем значение 0
}

// Конструктор с параметрами - создает число из n повторений цифры t
Thirteen::Thirteen(const size_t& n, unsigned char t) {
    validate_digit(t);              // проверяем корректность цифры
    size = n;                       // устанавливаем размер
    digits = new unsigned char[size];  // выделяем память
    std::fill(digits, digits + size, t);  // заполняем массив цифрой t
}

// Конструктор из списка инициализации
Thirteen::Thirteen(const std::initializer_list<unsigned char>& t) {
    size = t.size();               // получаем размер списка
    digits = new unsigned char[size];  // выделяем память
    size_t i = 0;
    for (auto digit : t) {         // копируем цифры из списка
        validate_digit(digit);      // проверяем каждую цифру
        digits[i++] = digit;
    }
    normalize();                    // удаляем ведущие нули
}

// Конструктор из строки (поддерживает цифры 0-9 и A-C для 10-12)
Thirteen::Thirteen(const std::string& t) {
    size = t.length();
    digits = new unsigned char[size];
    for (size_t i = 0; i < size; ++i) {
        // Преобразуем символы в цифры
        if (t[size - 1 - i] >= '0' && t[size - 1 - i] <= '9') {
            digits[i] = t[size - 1 - i] - '0';
        } else if (t[size - 1 - i] >= 'A' && t[size - 1 - i] <= 'C') {
            digits[i] = t[size - 1 - i] - 'A' + 10;
        } else {
            throw std::invalid_argument("Invalid thirteen digit");
        }
    }
    normalize();
}

// Конструктор копирования
// Создает новый объект как точную копию существующего
// Выделяет новую память и копирует все цифры
Thirteen::Thirteen(const Thirteen& other) {
    size = other.size;                                    // Копируем размер
    digits = new unsigned char[size];                     // Выделяем новую память
    std::copy(other.digits, other.digits + size, digits); // Копируем все цифры
}

// Конструктор перемещения
// Забирает ресурсы из другого объекта (который становится пустым)
// Не выделяет новую память, а перехватывает указатель
Thirteen::Thirteen(Thirteen&& other) noexcept {
    size = other.size;           // Забираем размер
    digits = other.digits;       // Забираем указатель на массив
    other.digits = nullptr;      // Обнуляем указатель у исходного объекта
    other.size = 0;             // Обнуляем размер у исходного объекта
}

// Деструктор
// Освобождает выделенную память при уничтожении объекта
Thirteen::~Thirteen() noexcept {
    delete[] digits;            // Освобождаем память
}

// Оператор присваивания копированием
// Копирует содержимое другого объекта, предварительно освободив свою память
Thirteen& Thirteen::operator=(const Thirteen& other) {
    if (this != &other) {       // Проверка на самоприсваивание
        delete[] digits;         // Освобождаем старую память
        size = other.size;       // Копируем размер
        digits = new unsigned char[size];  // Выделяем новую память
        std::copy(other.digits, other.digits + size, digits); // Копируем данные
    }
    return *this;               // Возвращаем ссылку на текущий объект
}

// Оператор присваивания перемещением
// Забирает ресурсы из другого объекта, предварительно освободив свои
Thirteen& Thirteen::operator=(Thirteen&& other) noexcept {
    if (this != &other) {       // Проверка на самоприсваивание
        delete[] digits;         // Освобождаем старую память
        size = other.size;       // Забираем размер
        digits = other.digits;   // Забираем указатель на массив
        other.digits = nullptr;  // Обнуляем указатель у исходного объекта
        other.size = 0;         // Обнуляем размер у исходного объекта
    }
    return *this;               // Возвращаем ссылку на текущий объект
}

// Арифметические операции
// Оператор сложения двух тринадцатеричных чисел
Thirteen Thirteen::operator+(const Thirteen& other) const {
    // Определяем максимальный размер результата
    size_t max_size = std::max(size, other.size);
    // Создаем результат с запасом на перенос в старший разряд
    Thirteen result(max_size + 1, 0);
    
    // Выполняем сложение с учетом переноса
    unsigned char carry = 0;  // перенос в следующий разряд
    for (size_t i = 0; i < max_size; ++i) {
        unsigned char sum = carry;
        // Добавляем цифру первого числа, если она есть
        if (i < size) sum += digits[i];
        // Добавляем цифру второго числа, если она есть
        if (i < other.size) sum += other.digits[i];
        
        // Записываем остаток от деления на 13 в текущий разряд
        result.digits[i] = sum % 13;
        // Вычисляем перенос в следующий разряд
        carry = sum / 13;
    }
    // Если остался перенос, записываем его в старший разряд
    if (carry) result.digits[max_size] = carry;
    
    // Удаляем ведущие нули
    result.normalize();
    return result;
}

// Оператор вычитания двух тринадцатеричных чисел
Thirteen Thirteen::operator-(const Thirteen& other) const {
    // Проверяем, что не вычитаем большее число из меньшего
    if (*this < other) {
        throw std::invalid_argument("Cannot subtract larger number from smaller");
    }
    
    // Создаем результат такого же размера, как уменьшаемое
    Thirteen result(size, 0);
    int borrow = 0;  // флаг заема из следующего разряда
    
    // Выполняем вычитание поразрядно
    for (size_t i = 0; i < size; ++i) {
        // Вычитаем заем из текущего разряда
        int diff = digits[i] - borrow;
        // Если есть цифра вычитаемого, вычитаем её
        if (i < other.size) diff -= other.digits[i];
        
        // Если результат отрицательный, занимаем из следующего разряда
        if (diff < 0) {
            diff += 13;  // добавляем основание системы счисления
            borrow = 1;  // устанавливаем флаг заема
        } else {
            borrow = 0;  // сбрасываем флаг заема
        }
        
        result.digits[i] = diff;  // записываем результат
    }
    
    // Удаляем ведущие нули
    result.normalize();
    return result;
}

// Операции сравнения
// Оператор "меньше"
bool Thirteen::operator<(const Thirteen& other) const {
    // Сначала сравниваем по количеству цифр
    if (size != other.size) {
        return size < other.size;
    }
    // Если размеры равны, сравниваем поразрядно, начиная со старшего разряда
    for (int i = size - 1; i >= 0; --i) {
        if (digits[i] != other.digits[i]) {
            return digits[i] < other.digits[i];
        }
    }
    // Если все цифры равны, возвращаем false
    return false;
}

// Оператор "больше" реализуется через оператор "меньше"
bool Thirteen::operator>(const Thirteen& other) const {
    return other < *this;
}

// Оператор "равно" сравнивает размеры и все цифры
bool Thirteen::operator==(const Thirteen& other) const {
    if (size != other.size) return false;
    // Используем стандартный алгоритм equal для сравнения массивов
    return std::equal(digits, digits + size, other.digits);
}

// Методы класса для арифметических операций с присваиванием
// Метод сложения с присваиванием
Thirteen& Thirteen::add(const Thirteen& other) {
    *this = *this + other;  // используем уже реализованный оператор сложения
    return *this;
}

// Метод вычитания с присваиванием
Thirteen& Thirteen::subtract(const Thirteen& other) {
    *this = *this - other;  // используем уже реализованный оператор вычитания
    return *this;
}

// Вспомогательные методы
// Проверка корректности цифры (должна быть меньше 13)
void Thirteen::validate_digit(unsigned char digit) const {
    if (digit >= 13) {
        throw std::invalid_argument("Digit must be less than 13");
    }
}

// Удаление ведущих нулей из числа
void Thirteen::normalize() {
    // Уменьшаем размер числа, пока есть ведущие нули
    // Оставляем как минимум одну цифру (даже если это ноль)
    while (size > 1 && digits[size - 1] == 0) {
        --size;
    }
}