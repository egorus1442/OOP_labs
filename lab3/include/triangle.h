#pragma once
#include "figure.h"
#include <cmath>

class Triangle : public Figure {
private:
    Point vertices[3];

public:
    Triangle() = default;
    
    Triangle& operator=(const Triangle& other);
    Triangle& operator=(Triangle&& other) noexcept;
    Figure& operator=(const Figure& other) override;
    Figure& operator=(Figure&& other) noexcept override;
    
    Point getCenter() const override;
    double getArea() const override;
    bool operator==(const Figure& other) const override;
    
    friend std::istream& operator>>(std::istream& is, Triangle& triangle);
    friend std::ostream& operator<<(std::ostream& os, const Triangle& triangle);

    void print(std::ostream& os) const override;
};
