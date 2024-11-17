#pragma once
#include "figure.h"

// см octagon.h
template <Scalar T>
class Triangle : public Figure<T> {
public:
    Triangle() {
        this->vertices.resize(3);
        for (auto& vertex : this->vertices) {
            vertex = std::make_unique<Point<T>>();
        }
    }

    size_t getVerticesCount() const override { return 3; }
    Point<T> getGeometricCenter() const override;
    double getArea() const override;
}; 