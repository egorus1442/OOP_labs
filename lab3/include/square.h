#pragma once
#include "figure.h"
#include <cmath>

class Square : public Figure {
private:
    Point vertices[4];

public:
    Square() = default;
    
    Point getCenter() const override;
    double getArea() const override;
    
    Square& operator=(const Square& other);
    Square& operator=(Square&& other) noexcept;
    Figure& operator=(const Figure& other) override;
    Figure& operator=(Figure&& other) noexcept override;
    bool operator==(const Figure& other) const override;
    
    friend std::istream& operator>>(std::istream& is, Square& square);
    friend std::ostream& operator<<(std::ostream& os, const Square& square);

    void print(std::ostream& os) const override;
};
