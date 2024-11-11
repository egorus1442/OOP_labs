#include <gtest/gtest.h>
#include "../include/triangle.h"
#include "../include/square.h"
#include "../include/octagon.h"
#include <sstream>

// Тесты для Triangle
TEST(TriangleTest, CenterCalculation) {
    Triangle triangle;
    std::stringstream ss("0 0 3 0 0 4");
    ss >> triangle;
    
    auto center = triangle.getCenter();
    EXPECT_NEAR(center.x, 1.0, 0.0001);
    EXPECT_NEAR(center.y, 1.3333, 0.0001);
}

TEST(TriangleTest, AreaCalculation) {
    Triangle triangle;
    std::stringstream ss("0 0 3 0 0 4");
    ss >> triangle;
    
    double area = static_cast<double>(triangle);
    EXPECT_NEAR(area, 6.0, 0.0001);
}

TEST(TriangleTest, Equality) {
    Triangle t1, t2;
    std::stringstream ss1("0 0 3 0 0 4");
    std::stringstream ss2("0 0 3 0 0 4");
    ss1 >> t1;
    ss2 >> t2;
    
    EXPECT_TRUE(t1 == t2);
}

// Тесты для Square
TEST(SquareTest, CenterCalculation) {
    Square square;
    std::stringstream ss("0 0 2 0 2 2 0 2");
    ss >> square;
    
    auto center = square.getCenter();
    EXPECT_NEAR(center.x, 1.0, 0.0001);
    EXPECT_NEAR(center.y, 1.0, 0.0001);
}

TEST(SquareTest, AreaCalculation) {
    Square square;
    std::stringstream ss("0 0 2 0 2 2 0 2");
    ss >> square;
    
    double area = static_cast<double>(square);
    EXPECT_NEAR(area, 4.0, 0.0001);
}

TEST(SquareTest, Equality) {
    Square s1, s2;
    std::stringstream ss1("0 0 2 0 2 2 0 2");
    std::stringstream ss2("0 0 2 0 2 2 0 2");
    ss1 >> s1;
    ss2 >> s2;
    
    EXPECT_TRUE(s1 == s2);
}

// Тесты для Octagon
TEST(OctagonTest, CenterCalculation) {
    Octagon octagon;
    std::stringstream ss("0 0 1 0 2 1 2 2 1 3 0 3 -1 2 -1 1");
    ss >> octagon;
    
    auto center = octagon.getCenter();
    EXPECT_NEAR(center.x, 0.5, 0.0001);
    EXPECT_NEAR(center.y, 1.5, 0.0001);
}

TEST(OctagonTest, AreaCalculation) {
    Octagon octagon;
    std::stringstream ss("0 0 1 0 2 1 2 2 1 3 0 3 -1 2 -1 1");
    ss >> octagon;
    
    double area = static_cast<double>(octagon);
    EXPECT_NEAR(area, 7.0, 0.0001);
}

TEST(OctagonTest, Equality) {
    Octagon o1, o2;
    std::stringstream ss1("0 0 1 0 2 1 2 2 1 3 0 3 -1 2 -1 1");
    std::stringstream ss2("0 0 1 0 2 1 2 2 1 3 0 3 -1 2 -1 1");
    ss1 >> o1;
    ss2 >> o2;
    
    EXPECT_TRUE(o1 == o2);
}

// Тесты для операций копирования и перемещения
TEST(OperationsTest, CopyAssignment) {
    Triangle t1;
    std::stringstream ss("0 0 3 0 0 4");
    ss >> t1;
    
    Triangle t2;
    t2 = t1;
    EXPECT_TRUE(t1 == t2);
}

TEST(OperationsTest, MoveAssignment) {
    Triangle t1;
    std::stringstream ss("0 0 3 0 0 4");
    ss >> t1;
    
    Triangle t2;
    t2 = std::move(t1);
    
    Triangle expected;
    std::stringstream ss2("0 0 3 0 0 4");
    ss2 >> expected;
    EXPECT_TRUE(t2 == expected);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
