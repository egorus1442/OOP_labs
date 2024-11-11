#pragma once
#include "figure.h"
#include <cmath>

class Octagon : public Figure {
private:
    Point vertices[8];

public:
    Octagon() = default;
    
    Point getCenter() const override;
    double getArea() const override;
    
    Octagon& operator=(const Octagon& other);
    Octagon& operator=(Octagon&& other) noexcept;
    Figure& operator=(const Figure& other) override;
    Figure& operator=(Figure&& other) noexcept override;
    bool operator==(const Figure& other) const override;
    
    friend std::istream& operator>>(std::istream& is, Octagon& octagon);
    friend std::ostream& operator<<(std::ostream& os, const Octagon& octagon);

    void print(std::ostream& os) const override;
};
