#include "../include/thirteen.h"

// Конструктор по умолчанию
Thirteen::Thirteen() : digits(1, 0) {}

// Конструктор от списка инициализации
Thirteen::Thirteen(const std::initializer_list<unsigned char>& init_digits) : digits(init_digits) {
    for (auto digit : digits) {
        if (digit >= 13) {
            throw std::invalid_argument("Digits must be less than 13");
        }
    }
    trim();
}

// Конструктор от строки
Thirteen::Thirteen(const std::string& str) {
    for (auto it = str.rbegin(); it != str.rend(); ++it) {
        unsigned char digit = *it - '0';
        if (digit >= 13) {
            throw std::invalid_argument("Digits must be less than 13");
        }
        digits.push_back(digit);
    }
    trim();
}

// Конструктор копирования
Thirteen::Thirteen(const Thirteen& other) : digits(other.digits) {}

// Конструктор перемещения
Thirteen::Thirteen(Thirteen&& other) noexcept : digits(std::move(other.digits)) {}

// Деструктор
Thirteen::~Thirteen() noexcept {}

// Присваивание копированием
Thirteen& Thirteen::operator=(const Thirteen& other) {
    if (this != &other) {
        digits = other.digits;
    }
    return *this;
}

// Присваивание перемещением
Thirteen& Thirteen::operator=(Thirteen&& other) noexcept {
    if (this != &other) {
        digits = std::move(other.digits);
    }
    return *this;
}

// Операция сложения
Thirteen Thirteen::operator+(const Thirteen& other) const {
    Thirteen result;
    result.digits.clear();
    unsigned char carry = 0;
    size_t max_size = std::max(digits.size(), other.digits.size());

    for (size_t i = 0; i < max_size || carry; ++i) {
        unsigned char sum = carry;
        if (i < digits.size()) sum += digits[i];
        if (i < other.digits.size()) sum += other.digits[i];
        result.digits.push_back(sum % 13);
        carry = sum / 13;
    }
    result.trim();
    return result;
}

// Операция вычитания
Thirteen Thirteen::operator-(const Thirteen& other) const {
    if (*this < other) {
        throw std::underflow_error("Result of subtraction is negative");
    }
    Thirteen result;
    result.digits.clear();
    unsigned char borrow = 0;

    for (size_t i = 0; i < digits.size(); ++i) {
        unsigned char sub = digits[i] - borrow - (i < other.digits.size() ? other.digits[i] : 0);
        borrow = 0;
        if (sub >= 13) {
            sub += 13;
            borrow = 1;
        }
        result.digits.push_back(sub);
    }
    result.trim();
    return result;
}

// Арифметические операции с присваиванием
Thirteen& Thirteen::operator+=(const Thirteen& other) {
    *this = *this + other;
    return *this;
}

Thirteen& Thirteen::operator-=(const Thirteen& other) {
    *this = *this - other;
    return *this;
}

// Операции сравнения
bool Thirteen::operator==(const Thirteen& other) const {
    return digits == other.digits;
}

bool Thirteen::operator!=(const Thirteen& other) const {
    return !(*this == other);
}

bool Thirteen::operator<(const Thirteen& other) const {
    if (digits.size() != other.digits.size()) {
        return digits.size() < other.digits.size();
    }
    for (size_t i = digits.size(); i-- > 0;) {
        if (digits[i] != other.digits[i]) {
            return digits[i] < other.digits[i];
        }
    }
    return false;
}

bool Thirteen::operator>(const Thirteen& other) const {
    return other < *this;
}

bool Thirteen::operator<=(const Thirteen& other) const {
    return !(other < *this);
}

bool Thirteen::operator>=(const Thirteen& other) const {
    return !(*this < other);
}

// Вспомогательные функции
void Thirteen::trim() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
}

std::string Thirteen::toString() const {
    std::string result;
    for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
        result += std::to_string(static_cast<int>(*it));
    }
    return result;
}
