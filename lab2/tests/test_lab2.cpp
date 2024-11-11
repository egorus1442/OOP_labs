#include <gtest/gtest.h>
#include "../include/thirteen.h"

// Тест конструктора по умолчанию
TEST(ThirteenTest, DefaultConstructor) {
    Thirteen t;
    EXPECT_EQ(t.toString(), "0");
}

// Тест конструктора от списка инициализации
TEST(ThirteenTest, InitializerListConstructor) {
    Thirteen t({1, 2, 3});
    EXPECT_EQ(t.toString(), "321");
}

// Тест конструктора от строки
TEST(ThirteenTest, StringConstructor) {
    Thirteen t("123");
    EXPECT_EQ(t.toString(), "123");
}

// Тест конструктора копирования
TEST(ThirteenTest, CopyConstructor) {
    Thirteen t1("456");
    Thirteen t2(t1);
    EXPECT_EQ(t2.toString(), "456");
}

// Тест конструктора перемещения
TEST(ThirteenTest, MoveConstructor) {
    Thirteen t1("789");
    Thirteen t2(std::move(t1));
    EXPECT_EQ(t2.toString(), "789");
    EXPECT_EQ(t1.toString(), "0");
}

// Тест сложения
TEST(ThirteenTest, Addition) {
    Thirteen t1("10");
    Thirteen t2("3");
    Thirteen result = t1 + t2;
    EXPECT_EQ(result.toString(), "13");
}

// Тест вычитания
TEST(ThirteenTest, Subtraction) {
    Thirteen t1("15");
    Thirteen t2("3");
    Thirteen result = t1 - t2;
    EXPECT_EQ(result.toString(), "12");
}

// Тест сложения с присваиванием
TEST(ThirteenTest, AdditionAssignment) {
    Thirteen t("10");
    t += Thirteen("3");
    EXPECT_EQ(t.toString(), "13");
}

// Тест вычитания с присваиванием
TEST(ThirteenTest, SubtractionAssignment) {
    Thirteen t("15");
    t -= Thirteen("3");
    EXPECT_EQ(t.toString(), "12");
}

// Тест операции сравнения равно
TEST(ThirteenTest, Equality) {
    Thirteen t1("123");
    Thirteen t2("123");
    EXPECT_TRUE(t1 == t2);
}

// Тест операции сравнения не равно
TEST(ThirteenTest, Inequality) {
    Thirteen t1("123");
    Thirteen t2("124");
    EXPECT_TRUE(t1 != t2);
}

// Тест операции сравнения меньше
TEST(ThirteenTest, LessThan) {
    Thirteen t1("123");
    Thirteen t2("124");
    EXPECT_TRUE(t1 < t2);
}

// Тест операции сравнения больше
TEST(ThirteenTest, GreaterThan) {
    Thirteen t1("125");
    Thirteen t2("124");
    EXPECT_TRUE(t1 > t2);
}

// Тест операции сравнения меньше или равно
TEST(ThirteenTest, LessThanOrEqual) {
    Thirteen t1("123");
    Thirteen t2("123");
    EXPECT_TRUE(t1 <= t2);
}

// Тест операции сравнения больше или равно
TEST(ThirteenTest, GreaterThanOrEqual) {
    Thirteen t1("125");
    Thirteen t2("123");
    EXPECT_TRUE(t1 >= t2);
}

// Тест генерации исключений в конструкторе от строки (неверные символы)
TEST(ThirteenTest, InvalidDigitInStringConstructor) {
    EXPECT_THROW(Thirteen("1A3"), std::invalid_argument);
}

// Тест генерации исключений при вычитании большего числа из меньшего
TEST(ThirteenTest, SubtractionUnderflow) {
    Thirteen t1("10");
    Thirteen t2("11");
    EXPECT_THROW(t1 - t2, std::underflow_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
