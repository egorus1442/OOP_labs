#include <gtest/gtest.h>
#include "../include/point.h"
#include "../include/array.h"
#include "../include/octagon.h"
#include "../include/triangle.h"
#include "../include/square.h"
#include <cmath>

// Тесты для Point
TEST(PointTest, Constructor) {
    Point<int> p1;
    EXPECT_EQ(p1.x, 0);
    EXPECT_EQ(p1.y, 0);

    Point<double> p2(3.14, 2.71);
    EXPECT_DOUBLE_EQ(p2.x, 3.14);
    EXPECT_DOUBLE_EQ(p2.y, 2.71);
}

TEST(PointTest, IOOperators) {
    std::stringstream ss;
    Point<int> p1(5, 10);
    ss << p1;
    EXPECT_EQ(ss.str(), "(5, 10)");

    Point<int> p2;
    ss.clear();
    ss.str("3 4");
    ss >> p2;
    EXPECT_EQ(p2.x, 3);
    EXPECT_EQ(p2.y, 4);
}

// Тесты для Square
TEST(SquareTest, Area) {
    Square<double> square;
    std::stringstream ss;
    // Создаем квадрат 2x2 с центром в (0,0)
    ss << "1 1\n"
       << "1 -1\n"
       << "-1 -1\n"
       << "-1 1\n";
    ss >> square;
    
    EXPECT_DOUBLE_EQ(square.getArea(), 4.0);
}

TEST(SquareTest, GeometricCenter) {
    Square<double> square;
    std::stringstream ss;
    ss << "1 1\n"
       << "1 -1\n"
       << "-1 -1\n"
       << "-1 1\n";
    ss >> square;
    
    Point<double> center = square.getGeometricCenter();
    EXPECT_NEAR(center.x, 0.0, 1e-10);
    EXPECT_NEAR(center.y, 0.0, 1e-10);
}

// Тесты для Triangle
TEST(TriangleTest, Area) {
    Triangle<double> triangle;
    std::stringstream ss;
    // Создаем треугольник с основанием 6 и высотой 4
    ss << "0 4\n"    // вершина
       << "-3 0\n"   // левый нижний угол
       << "3 0\n";   // правый нижний угол
    ss >> triangle;
    
    // Площадь треугольника = (основание * высота) / 2
    // = (6 * 4) / 2 = 12
    EXPECT_NEAR(triangle.getArea(), 12.0, 1e-5);
}

TEST(TriangleTest, GeometricCenter) {
    Triangle<double> triangle;
    std::stringstream ss;
    ss << "0 0\n"
       << "3 0\n"
       << "0 3\n";
    ss >> triangle;
    
    Point<double> center = triangle.getGeometricCenter();
    EXPECT_NEAR(center.x, 1.0, 1e-10);
    EXPECT_NEAR(center.y, 1.0, 1e-10);
}

// Тесты для Octagon
TEST(OctagonTest, Area) {
    Octagon<double> octagon;
    std::stringstream ss;
    // Создаем правильный восьмиугольник с радиусом 2
    double r = 2.0;
    double angle = M_PI / 4.0;
    for (int i = 0; i < 8; ++i) {
        ss << r * cos(i * angle) << " " << r * sin(i * angle) << "\n";
    }
    ss >> octagon;
    
    // Площадь правильного восьмиугольника = 2 * a^2 * (1 + sqrt(2))
    // где a - длина стороны
    double side = 2 * r * sin(M_PI / 8.0);
    double expected_area = 2 * side * side * (1 + std::sqrt(2));
    EXPECT_NEAR(octagon.getArea(), expected_area, 1e-4);
}

// Тесты для Array
TEST(ArrayTest, Construction) {
    Array<int> arr;
    EXPECT_EQ(arr.get_size(), 0);
    EXPECT_EQ(arr.get_capacity(), 0);
}

TEST(ArrayTest, PushBack) {
    Array<int> arr;
    arr.push_back(1);
    EXPECT_EQ(arr.get_size(), 1);
    EXPECT_EQ(arr[0], 1);

    arr.push_back(2);
    EXPECT_EQ(arr.get_size(), 2);
    EXPECT_EQ(arr[1], 2);
}

TEST(ArrayTest, Remove) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    
    arr.remove(1);
    EXPECT_EQ(arr.get_size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
}

TEST(ArrayTest, IndexOperator) {
    Array<int> arr;
    arr.push_back(42);
    
    EXPECT_EQ(arr[0], 42);
    arr[0] = 24;
    EXPECT_EQ(arr[0], 24);
    
    EXPECT_THROW(arr[1], std::out_of_range);
}

// Тесты для работы с умными указателями
TEST(SmartPointerTest, SharedPtrArray) {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    auto square = std::make_shared<Square<double>>();
    std::stringstream ss;
    ss << "1 1\n1 -1\n-1 -1\n-1 1\n";
    ss >> *square;
    
    figures.push_back(square);
    EXPECT_EQ(figures.get_size(), 1);
    EXPECT_DOUBLE_EQ(figures[0]->getArea(), 4.0);
}

TEST(SmartPointerTest, UniquePtr) {
    Square<double> square;
    std::stringstream ss;
    ss << "1 1\n1 -1\n-1 -1\n-1 1\n";
    ss >> square;
    
    auto center = square.getGeometricCenter();
    EXPECT_NEAR(center.x, 0.0, 1e-10);
    EXPECT_NEAR(center.y, 0.0, 1e-10);
}

// Тест для проверки общей площади фигур
TEST(FiguresTest, TotalArea) {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    // Добавляем квадрат 2x2
    auto square = std::make_shared<Square<double>>();
    std::stringstream ss1;
    ss1 << "1 1\n1 -1\n-1 -1\n-1 1\n";
    ss1 >> *square;
    figures.push_back(square);
    
    // Добавляем равносторонний треугольник со стороной 2
    auto triangle = std::make_shared<Triangle<double>>();
    std::stringstream ss2;
    ss2 << "0 2\n-1.732051 -1\n1.732051 -1\n";
    ss2 >> *triangle;
    figures.push_back(triangle);
    
    double total_area = 0.0;
    for (size_t i = 0; i < figures.get_size(); ++i) {
        total_area += figures[i]->getArea();
    }
    
    // Площадь квадрата (4.0) + площадь треугольника (√3)
    // Для квадрата 2x2: area = 4.0
    // Для равностороннего треугольника со стороной 2√3: area = (2√3)^2 * √3/4 = 3√3
    EXPECT_NEAR(total_area, 4.0 + 3.0 * std::sqrt(3), 1e-5);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}