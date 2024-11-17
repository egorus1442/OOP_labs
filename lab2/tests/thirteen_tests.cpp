#include <gtest/gtest.h>
#include "thirteen.h"

// Тесты конструкторов
TEST(ThirteenConstructor, DefaultConstructor) {
    Thirteen num;
    EXPECT_EQ(num, Thirteen("0"));
}

TEST(ThirteenConstructor, SizeValueConstructor) {
    Thirteen num(3, 5);
    EXPECT_EQ(num, Thirteen("555"));
}

TEST(ThirteenConstructor, InitializerListConstructor) {
    Thirteen num{1, 2, 3};
    EXPECT_EQ(num, Thirteen("321"));
}

TEST(ThirteenConstructor, StringConstructor) {
    EXPECT_NO_THROW(Thirteen("123"));
    EXPECT_NO_THROW(Thirteen("ABC")); // 10,11,12 в тринадцатеричной
    EXPECT_THROW(Thirteen("G"), std::invalid_argument);
}

// Тесты операций сложения
TEST(ThirteenArithmetic, Addition) {
    Thirteen a("123");
    Thirteen b("456");
    Thirteen result = a + b;
    EXPECT_EQ(result, Thirteen("579"));
    
    // Тест с переносом
    Thirteen c("C"); // 12 в тринадцатеричной
    Thirteen d("1");
    EXPECT_EQ(c + d, Thirteen("10"));
}

TEST(ThirteenArithmetic, AdditionMethod) {
    Thirteen a("123");
    Thirteen b("456");
    a.add(b);
    EXPECT_EQ(a, Thirteen("579"));
}

// Тесты операций вычитания
TEST(ThirteenArithmetic, Subtraction) {
    Thirteen a("456");
    Thirteen b("123");
    Thirteen result = a - b;
    EXPECT_EQ(result, Thirteen("333"));
    
    // Проверка исключения при вычитании большего числа из меньшего
    EXPECT_THROW(b - a, std::invalid_argument);
}

TEST(ThirteenArithmetic, SubtractionMethod) {
    Thirteen a("456");
    Thirteen b("123");
    a.subtract(b);
    EXPECT_EQ(a, Thirteen("333"));
}

// Тесты операций сравнения
TEST(ThirteenComparison, EqualityOperator) {
    Thirteen a("123");
    Thirteen b("123");
    Thirteen c("456");
    
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST(ThirteenComparison, LessThanOperator) {
    Thirteen a("123");
    Thirteen b("456");
    
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(ThirteenComparison, GreaterThanOperator) {
    Thirteen a("456");
    Thirteen b("123");
    
    EXPECT_TRUE(a > b);
    EXPECT_FALSE(b > a);
}

// Тесты конструктора копирования и перемещения
TEST(ThirteenConstructor, CopyConstructor) {
    Thirteen original("123");
    Thirteen copy(original);
    EXPECT_EQ(original, copy);
}

TEST(ThirteenConstructor, MoveConstructor) {
    Thirteen original("123");
    Thirteen moved(std::move(original));
    EXPECT_EQ(moved, Thirteen("123"));
}

// Тесты операторов присваивания
TEST(ThirteenAssignment, CopyAssignment) {
    Thirteen a("123");
    Thirteen b;
    b = a;
    EXPECT_EQ(a, b);
}

TEST(ThirteenAssignment, MoveAssignment) {
    Thirteen a("123");
    Thirteen b;
    b = std::move(a);
    EXPECT_EQ(b, Thirteen("123"));
}

// Тесты на некорректные входные данные
TEST(ThirteenValidation, InvalidDigit) {
    EXPECT_THROW(Thirteen(1, 13), std::invalid_argument);
    
    // Создаем лямбда-функцию для теста со списком инициализации
    auto create_invalid = []() { Thirteen t{0, 13, 1}; };
    EXPECT_THROW(create_invalid(), std::invalid_argument);
}

TEST(ThirteenValidation, InvalidString) {
    auto create_invalid_string = []() { Thirteen t("1G3"); };
    EXPECT_THROW(create_invalid_string(), std::invalid_argument);
}

TEST(ThirteenValidation, ValidString) {
    EXPECT_NO_THROW({
        Thirteen t("ABC"); // допустимые цифры в 13-ричной системе
    });
} 