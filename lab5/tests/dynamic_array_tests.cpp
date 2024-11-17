#include <gtest/gtest.h>
#include "dynamic_array.h"
#include "dynamic_memory_resource.h"
#include "test_structs.h"

class DynamicArrayTest : public ::testing::Test {
protected:
    DynamicMemoryResource memory_resource;
};

// Тесты для простых типов (int)
TEST_F(DynamicArrayTest, IntegerPushBackAndAccess) {
    DynamicArray<int> array(&memory_resource);
    
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);
    
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array[0], 1);
    EXPECT_EQ(array[1], 2);
    EXPECT_EQ(array[2], 3);
}

TEST_F(DynamicArrayTest, IntegerPopBack) {
    DynamicArray<int> array(&memory_resource);
    
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);
    
    array.pop_back();
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array[0], 1);
    EXPECT_EQ(array[1], 2);
}

TEST_F(DynamicArrayTest, IntegerIterator) {
    DynamicArray<int> array(&memory_resource);
    std::vector<int> expected = {1, 2, 3, 4, 5};
    
    for (int value : expected) {
        array.push_back(value);
    }
    
    std::vector<int> actual;
    for (auto it = array.begin(); it != array.end(); ++it) {
        actual.push_back(*it);
    }
    
    EXPECT_EQ(actual, expected);
}

// Тесты для сложных типов (TestStruct)
TEST_F(DynamicArrayTest, StructPushBackAndAccess) {
    DynamicArray<TestStruct> array(&memory_resource);
    
    array.push_back(TestStruct(1, 1.1));
    array.push_back(TestStruct(2, 2.2));
    
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array[0], TestStruct(1, 1.1));
    EXPECT_EQ(array[1], TestStruct(2, 2.2));
}

TEST_F(DynamicArrayTest, StructPopBack) {
    DynamicArray<TestStruct> array(&memory_resource);
    
    array.push_back(TestStruct(1, 1.1));
    array.push_back(TestStruct(2, 2.2));
    array.push_back(TestStruct(3, 3.3));
    
    array.pop_back();
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array[0], TestStruct(1, 1.1));
    EXPECT_EQ(array[1], TestStruct(2, 2.2));
}

// Тесты для memory resource
TEST_F(DynamicArrayTest, MemoryReuse) {
    DynamicArray<int> array(&memory_resource);
    
    // Первое выделение памяти
    array.push_back(1);
    array.push_back(2);
    
    // Освобождаем память
    array.pop_back();
    array.pop_back();
    
    // Повторное использование памяти
    array.push_back(3);
    EXPECT_EQ(array[0], 3);
}

// Тест на работу итератора
TEST_F(DynamicArrayTest, IteratorOperations) {
    DynamicArray<int> array(&memory_resource);
    array.push_back(1);
    array.push_back(2);
    
    auto it = array.begin();
    EXPECT_EQ(*it, 1);
    
    ++it;
    EXPECT_EQ(*it, 2);
    
    it++;
    EXPECT_EQ(it, array.end());
}

// Тест на пустой массив
TEST_F(DynamicArrayTest, EmptyArray) {
    DynamicArray<int> array(&memory_resource);
    
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.begin(), array.end());
}

// Тест на большое количество элементов (проверка реаллокации)
TEST_F(DynamicArrayTest, LargeNumberOfElements) {
    DynamicArray<int> array(&memory_resource);
    const int N = 1000;
    
    for (int i = 0; i < N; ++i) {
        array.push_back(i);
    }
    
    EXPECT_EQ(array.size(), N);
    for (int i = 0; i < N; ++i) {
        EXPECT_EQ(array[i], i);
    }
} 